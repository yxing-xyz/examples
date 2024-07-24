package util

import (
	"errors"
	"log"
	"net"
	"os"
	"strings"
	"syscall"

	"github.com/vishvananda/netlink"
)

// 只支持ipv4, 默认路由的网卡
func DefaultGatewayRouteInterface() (*net.Interface, error) {
	routes, err := netlink.RouteList(nil, 2)
	if err != nil {
		return nil, err
	}
	for _, v := range routes {
		if v.Gw != nil {
			// 默认路由
			return net.InterfaceByIndex(v.LinkIndex)
		}
	}

	return nil, errors.New("not found default route interface")
}

// 只支持ipv4
/*
func DefaultGateway() (*route.RouteMessage, error) {
	// 2 => ipv4, 30 => ipv6
	byts, err := route.FetchRIB(2, route.RIBTypeRoute, 0)
	if err != nil {
		return nil, err
	}
	messages, err := route.ParseRIB(route.RIBTypeRoute, byts)
	if err != nil {
		return nil, err
	}
	for _, value := range messages {
		r := value.(*route.RouteMessage)
		dest := r.Addrs[0].(*route.Inet4Addr)
		if dest.IP == [4]byte{0, 0, 0, 0} {
			return r, nil
		}
	}
	return nil, nil
}
*/

func DefaultGatewayInterface(index int) (*net.Interface, error) {
	return net.InterfaceByIndex(index)
}

func FindInterfaceByIP(ip string) (*net.Interface, error) {
	interfs, err := net.Interfaces()
	if err != nil {
		return nil, err
	}
	for _, v := range interfs {
		addrs, err := v.Addrs()
		if err != nil {
			return nil, err
		}
		for _, vv := range addrs {
			s := strings.Split(vv.String(), "/")
			if s[0] == ip {
				return &v, nil
			}
		}
	}
	return nil, nil
}

func isCaredNetError(err error) bool {
	netErr, ok := err.(net.Error)
	if !ok {
		return false
	}

	if netErr.Timeout() {
		log.Println("timeout")
		return true
	}

	opErr, ok := netErr.(*net.OpError)
	if !ok {
		return false
	}

	switch t := opErr.Err.(type) {
	case *net.DNSError:
		log.Printf("net.DNSError:%+v", t)
		return true
	case *os.SyscallError:
		log.Printf("os.SyscallError:%+v", t)
		if errno, ok := t.Err.(syscall.Errno); ok {
			switch errno {
			case syscall.ECONNREFUSED:
				log.Println("connect refused")
				return true
			case syscall.ETIMEDOUT:
				log.Println("timeout")
				return true
			}
		}
	}

	return false
}
