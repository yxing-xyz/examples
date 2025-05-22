package utils

import (
	"fmt"

	"github.com/miekg/dns"
)

// 查询DNS服务器
func QueryDNS(dnsServer string, name string, tp dns.Type) (*dns.Msg, error) {
	// 创建一个新的消息结构体
	msg := new(dns.Msg)
	msg.SetQuestion(name, uint16(tp)) // 设置查询类型为A记录

	// 指定DNS服务器地址
	server := dnsServer

	// 创建UDP连接
	client := new(dns.Client)
	r, _, err := client.Exchange(msg, server+":53")
	if err != nil {
		return nil, fmt.Errorf("failed to query DNS: %v", err)
	}

	// 检查响应是否成功
	if r.Rcode != dns.RcodeSuccess {
		return nil, fmt.Errorf("DNS query failed with response code: %d", r.Rcode)
	}
	return r, nil
}
