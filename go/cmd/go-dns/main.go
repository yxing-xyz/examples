package main

import (
	"fmt"
	"github.com/rs/zerolog"
	"github.com/rs/zerolog/log"
	"net"
	"os"
)

func init() {
	zerolog.SetGlobalLevel(zerolog.InfoLevel)
	log.Logger = log.Output(zerolog.ConsoleWriter{Out: os.Stderr})
}

func main() {
	log.Info().Msg("shadow staring...")
	srv := NewDNSServerDefault()
	err := srv.ListenAndServe()
	if err != nil {
		log.Error().Msg(err.Error())
		panic(err.Error())
	}
}
func test() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s hostname\n", os.Args[0])
		fmt.Println("Usage: ", os.Args[0], "hostname")
		os.Exit(1)
	}
	name := os.Args[1]

	addr, err := net.ResolveIPAddr("ip", name)
	if err != nil {
		panic(err)
		fmt.Println("Resolution error", err.Error())
		os.Exit(1)
	}
	fmt.Println("Resolved address is ", addr.String())
	os.Exit(0)
}