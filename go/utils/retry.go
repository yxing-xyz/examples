package utils

import (
	"fmt"
	"net"
	"time"

	"github.com/avast/retry-go/v4"
)

// RetryConfig 定义了重试机制的配置项
type RetryConfig struct {
	Attempts         uint                    // 尝试次数
	Delay            time.Duration           // 每次尝试之间的延迟
	DelayTyepFunc    retry.DelayTypeFunc     // 延迟类型（固定、指数等）
	OnRetry          func(n uint, err error) // 出现错误时的回调函数
	LastCallRecovery bool                    // 是否在最后一次调用失败后进行恢复尝试
	retryIf          func(err error) bool    // 判断是否应该重试的函数
}

// DefaultRetryConfig 提供默认的重试配置
var DefaultRetryConfig = RetryConfig{
	Attempts:         5,
	Delay:            2 * time.Second,
	DelayTyepFunc:    retry.FixedDelay,
	OnRetry:          func(n uint, err error) { fmt.Printf("Attempt %d failed: %v\n", n+1, err) },
	LastCallRecovery: false,
}

var NetworkRetryConfig = RetryConfig{
	Attempts:      5,                // 默认重试5次
	Delay:         2 * time.Second,  // 每次间隔2秒
	DelayTyepFunc: retry.FixedDelay, // 固定延迟策略
	OnRetry: func(n uint, err error) { // 打印网络错误重试日志
		fmt.Printf("network retry attempt %d failed: %v\n", n+1, err)
	},
	LastCallRecovery: false, // 关闭最后一次强制恢复（仅用于网络临时故障）
}

func init() {
	NetworkRetryConfig.WithCustomOptions(WithNetworkRetryOnly())
}

// WithCustomOptions 允许用户覆盖默认设置
func (rc *RetryConfig) WithCustomOptions(options ...func(*RetryConfig)) *RetryConfig {
	for _, option := range options {
		option(rc)
	}
	return rc
}

// WithNetworkRetryOnly 设置只对网络错误进行重试
func WithNetworkRetryOnly() func(*RetryConfig) {
	return func(rc *RetryConfig) {
		rc.retryIf = isNetworkError
	}
}

// isNetworkError 判断错误是否为网络错误
func isNetworkError(err error) bool {
	// 基础网络错误类型检查
	if _, ok := err.(net.Error); ok {
		return true
	}

	// DNS 解析错误
	if _, ok := err.(*net.DNSError); ok {
		return true
	}
	return false
}

// Apply 应用配置到 retry.Do 方法中
func (rc *RetryConfig) Apply(operation func() error) error {
	retryOptions := []retry.Option{
		retry.Attempts(rc.Attempts),
		retry.Delay(rc.Delay),
		retry.DelayType(rc.DelayTyepFunc),
		retry.OnRetry(rc.OnRetry),
	}

	// 如果设置了网络错误判断函数，则添加到重试选项中
	if rc.retryIf != nil {
		retryOptions = append(retryOptions, retry.RetryIf(rc.retryIf))
	}
	return retry.Do(operation, retryOptions...)
}

// 自定义配置选项示例
func WithAttempts(attempts uint) func(*RetryConfig) {
	return func(rc *RetryConfig) {
		rc.Attempts = attempts
	}
}

func WithDelay(delay time.Duration) func(*RetryConfig) {
	return func(rc *RetryConfig) {
		rc.Delay = delay
	}
}

func WithDelayType(delayTypeFunc retry.DelayTypeFunc) func(*RetryConfig) {
	return func(rc *RetryConfig) {
		rc.DelayTyepFunc = delayTypeFunc
	}
}

func WithOnRetry(onRetry func(n uint, err error)) func(*RetryConfig) {
	return func(rc *RetryConfig) {
		rc.OnRetry = onRetry
	}
}

func WithLastCallRecovery(lastCallRecovery bool) func(*RetryConfig) {
	return func(rc *RetryConfig) {
		rc.LastCallRecovery = lastCallRecovery
	}
}
