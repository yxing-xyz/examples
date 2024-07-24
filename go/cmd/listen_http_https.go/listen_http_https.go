package main

import (
	"bytes"
	"crypto/tls"
	"crypto/x509"
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"net"
	"net/http"
	"os"

	"github.com/gorilla/mux"
)

var (
	port     int
	caroots  string
	keyfile  string
	signcert string
)

func init() {
	flag.IntVar(&port, "port", 8080, "The host port on which the REST server will listen")
	flag.StringVar(&caroots, "caroot", "", "Path to file containing PEM-encoded trusted certificate(s) for clients")
	flag.StringVar(&keyfile, "key", "", "Path to file containing PEM-encoded key file for service")
	flag.StringVar(&signcert, "signcert", "", "Path to file containing PEM-encoded sign certificate for service")
}

// Start a proxy server listen on listenport
// This proxy will forward all HTTP request to httpport, and all HTTPS request to httpsport
func proxyStart(listenport, httpport, httpsport int) {
	proxylistener, err := net.Listen("tcp", fmt.Sprintf(":%d", listenport))
	if err != nil {
		fmt.Printf("Unable to listen on: %d, error: %s\n", listenport, err.Error())
		os.Exit(1)
	}
	defer proxylistener.Close()

	for {
		proxyconn, err := proxylistener.Accept()
		if err != nil {
			fmt.Printf("Unable to accept a request, error: %s\n", err.Error())
			continue
		}

		// Read a header firstly in case you could have opportunity to check request
		// whether to decline or proceed the request
		buffer := make([]byte, 1024)
		n, err := proxyconn.Read(buffer)
		if err != nil {
			//fmt.Printf("Unable to read from input, error: %s\n", err.Error())
			continue
		}

		var targetport int
		if isHTTPRequest(buffer) {
			targetport = httpport
		} else {
			targetport = httpsport
		}

		targetconn, err := net.Dial("tcp", fmt.Sprintf("localhost:%d", targetport))
		if err != nil {
			fmt.Printf("Unable to connect to: %d, error: %s\n", targetport, err.Error())
			proxyconn.Close()
			continue
		}

		_, err = targetconn.Write(buffer[:n])
		if err != nil {
			fmt.Printf("Unable to write to output, error: %s\n", err.Error())
			proxyconn.Close()
			targetconn.Close()
			continue
		}

		go proxyRequest(proxyconn, targetconn)
		go proxyRequest(targetconn, proxyconn)
	}
}

// Forward all requests from r to w
func proxyRequest(r net.Conn, w net.Conn) {
	defer r.Close()
	defer w.Close()

	var buffer = make([]byte, 4096000)
	for {
		n, err := r.Read(buffer)
		if err != nil {
			//fmt.Printf("Unable to read from input, error: %s\n", err.Error())
			break
		}

		_, err = w.Write(buffer[:n])
		if err != nil {
			fmt.Printf("Unable to write to output, error: %s\n", err.Error())
			break
		}
	}
}

func isHTTPRequest(buffer []byte) bool {
	httpMethod := []string{"GET", "PUT", "HEAD", "POST", "DELETE", "PATCH", "OPTIONS", "CONNECT", "TRACE"}
	for cnt := 0; cnt < len(httpMethod); cnt++ {
		if bytes.HasPrefix(buffer, []byte(httpMethod[cnt])) {
			return true
		}
	}
	return false
}

func startHTTPSServer(address string, router *mux.Router, caroots string, keyfile string, signcert string) {
	pool := x509.NewCertPool()

	caCrt, err := os.ReadFile(caroots)
	if err != nil {
		log.Fatalln("ReadFile err:", err)
	}
	pool.AppendCertsFromPEM(caCrt)

	s := &http.Server{
		Addr:    address,
		Handler: router,
		TLSConfig: &tls.Config{
			MinVersion: tls.VersionTLS12,
			ClientCAs:  pool,
			ClientAuth: tls.RequireAndVerifyClientCert,
		},
	}
	err = s.ListenAndServeTLS(signcert, keyfile)
	if err != nil {
		log.Fatalln("ListenAndServeTLS err:", err)
	}
}

func startHTTPServer(address string, router *mux.Router) {
	err := http.ListenAndServe(address, router)
	if err != nil {
		log.Fatalln("ListenAndServe err:", err)
	}
}

func SayHello(w http.ResponseWriter, r *http.Request) {
	log.Println("Entry SayHello")
	res := map[string]string{"hello": "world"}

	b, err := json.Marshal(res)
	if err == nil {
		w.WriteHeader(http.StatusOK)
		w.Header().Set("Content-Type", "application/json")
		w.Write(b)
	}

	log.Println("Exit SayHello")
}

func main() {
	flag.Parse()
	fmt.Println("Server listen on", port)

	router := mux.NewRouter().StrictSlash(true)
	router.HandleFunc("/service/hello", SayHello).Methods("GET")

	listenport, httpport, httpsport := port, port+10, port+20
	go startHTTPServer(fmt.Sprintf("localhost:%d", httpport), router)
	go startHTTPSServer(fmt.Sprintf("localhost:%d", httpsport), router, caroots, keyfile, signcert)

	proxyStart(listenport, httpport, httpsport)

	fmt.Println("Exit main")
}
