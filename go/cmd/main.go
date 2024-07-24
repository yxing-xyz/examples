package main

import (
	"context"
	"net"
	"net/http"

	"github.com/docker/docker/api/types/container"
	"github.com/moby/moby/client"
	"golang.org/x/crypto/ssh"
)

func main() {
	config := &ssh.ClientConfig{
		User:            "root",
		Auth:            []ssh.AuthMethod{ssh.Password("password")},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}
	sc, err := ssh.Dial("tcp", "9.135.90.17:36000", config)
	if err != nil {
		panic(err)
	}
	defer sc.Close()
	// 获取一个可作为转发通道的ssh connection

	dc, err := client.NewClientWithOpts(client.WithHTTPClient(&http.Client{
		Transport: &http.Transport{
			DialContext: func(ctx context.Context, network, addr string) (net.Conn, error) {
				return sc.Dial("unix", "/var/run/docker.sock")
			},
		},
	}),
		client.WithAPIVersionNegotiation(),
	)
	if err != nil {
		panic(err)
	}
	dc.ContainerRemove(context.Background(), "demo", container.RemoveOptions{
		Force: true,
	})
	c, err := dc.ContainerCreate(context.Background(), &container.Config{
		Image: "ccr.ccs.tencentyun.com/yxing-xyz/linux:ubuntu-devel",
	}, nil, nil, nil, "demo")
	if err != nil {
		panic(err)
	}
	err = dc.ContainerStart(context.Background(), c.ID, container.StartOptions{})
	if err != nil {
		panic(err)
	}
}
