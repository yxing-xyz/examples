package utils

import (
	"fmt"
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
}

// DefaultRetryConfig 提供默认的重试配置
var DefaultRetryConfig = RetryConfig{
	Attempts:         3,
	Delay:            2 * time.Second,
	DelayTyepFunc:    retry.FixedDelay,
	OnRetry:          func(n uint, err error) { fmt.Printf("Attempt %d failed: %v\n", n+1, err) },
	LastCallRecovery: false,
}

// WithCustomOptions 允许用户覆盖默认设置
func (rc *RetryConfig) WithCustomOptions(options ...func(*RetryConfig)) *RetryConfig {
	for _, option := range options {
		option(rc)
	}
	return rc
}

// Apply 应用配置到 retry.Do 方法中
func (rc *RetryConfig) Apply(operation func() error) error {
	return retry.Do(operation,
		retry.Attempts(rc.Attempts),
		retry.Delay(rc.Delay),
		retry.DelayType(rc.DelayTyepFunc),
		retry.OnRetry(rc.OnRetry),
	)
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
