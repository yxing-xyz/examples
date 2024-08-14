package main

import (
	"bytes"
	"crypto/tls"
	"fmt"
	"log"
	"net"
	"net/http"
	"os"

	"github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{} // use default options
func ws(w http.ResponseWriter, r *http.Request) {
	c, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Print("upgrade:", err)
		return
	}
	defer c.Close()
	for {
		_, _, err := c.ReadMessage()
		if err != nil {
			log.Println(err.Error())
			return
		}
	}
}

func chunked(w http.ResponseWriter, r *http.Request) {
	w.Header().Add("Transfer-Encoding", "chunked")
	for i := 0; i < 1024; i++ {
		_, err := w.Write([]byte{0xFF})
		if err != nil {
			return
		}
	}
}

func main() {
	http.HandleFunc("/ws", ws)
	http.HandleFunc("/chunked", chunked)

	go HttpProxyServer()
	go HttpsProxyServe()
	proxylistener, err := net.Listen("tcp", ":58787")
	if err != nil {
		panic(err)
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

		var targetport string
		if IsHTTPRequest(buffer) {
			targetport = http_unix_path
		} else {
			targetport = https_unix_path
		}
		targetconn, err := net.Dial("unix", targetport)
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
func IsHTTPRequest(buffer []byte) bool {
	httpMethod := []string{"GET", "PUT", "HEAD", "POST", "DELETE", "PATCH", "OPTIONS", "CONNECT", "TRACE"}
	for cnt := 0; cnt < len(httpMethod); cnt++ {
		if bytes.HasPrefix(buffer, []byte(httpMethod[cnt])) {
			return true
		}
	}
	return false
}

var http_unix_path = "/tmp/localproxy-server.http"

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
func HttpProxyServer() {
	os.Remove(http_unix_path)
	httpUnix, err := net.Listen("unix", http_unix_path)
	if err != nil {
		panic(err)
	}
	server := http.Server{
		Handler: http.DefaultServeMux,
	}
	err = server.Serve(httpUnix)
	if err != nil {
		panic(err)
	}
	defer func() {
		os.Remove(http_unix_path)
	}()

}

var https_unix_path = "/tmp/localproxy-server.https"

func HttpsProxyServe() {
	cert, err := tls.X509KeyPair([]byte(CERT), []byte(KEY))
	if err != nil {
		panic(err)
	}

	tlsConfig := &tls.Config{
		Certificates: []tls.Certificate{cert},
	}
	os.Remove(https_unix_path)
	httpsUnix, err := tls.Listen("unix", https_unix_path, tlsConfig)
	if err != nil {
		panic(err)
	}
	server := http.Server{
		Handler: http.DefaultServeMux,
	}

	err = server.Serve(httpsUnix)
	if err != nil {
		panic(err)
	}
}

var CERT = `-----BEGIN CERTIFICATE-----
MIIEIjCCAoqgAwIBAgIRAJU8VQ/1Rja9KCLx8YIjWlkwDQYJKoZIhvcNAQELBQAw
azEeMBwGA1UEChMVbWtjZXJ0IGRldmVsb3BtZW50IENBMSAwHgYDVQQLDBd4QFNI
QVdOWVlVLU1CMCAo5L2Z5pifKTEnMCUGA1UEAwwebWtjZXJ0IHhAU0hBV05ZWVUt
TUIwICjkvZnmmJ8pMB4XDTI0MDgxMjA4MDg1M1oXDTI2MTExMjA4MDg1M1owSzEn
MCUGA1UEChMebWtjZXJ0IGRldmVsb3BtZW50IGNlcnRpZmljYXRlMSAwHgYDVQQL
DBd4QFNIQVdOWVlVLU1CMCAo5L2Z5pifKTCCASIwDQYJKoZIhvcNAQEBBQADggEP
ADCCAQoCggEBALLe9BdA2+SMSMPCGpCedeLg/voykZbbQ2fQ/LYPjeR3h0ITMxIt
Qh3V9Rsyy3vvVnR8P8xhN/Dfdqg111ZXzouTZpfjQmPwOsezrGDGs+Bv3Wo23jzm
NMNXEqRTA0OHr3q2nV0mc2HE9Ap165CZ42qlJ1VJXKzpoOanNQb6zGygG/WM3DNd
NXSe/mSLpeft5l1BE1j7r+fOi3hViiHtyHeIsah20//GvbS9k4A1ojVE1hiaHJoQ
b/RA3e7FRjMwbe0ZyL6JPaIFaFKQIndDP65c5joMjutFW4S4EJIdrViF6hZg2Ug4
ICdVU+hleLL/dimLy4phr2gh+zj0bt5YVSUCAwEAAaNhMF8wDgYDVR0PAQH/BAQD
AgWgMBMGA1UdJQQMMAoGCCsGAQUFBwMBMB8GA1UdIwQYMBaAFIg5tCJhKyWy9YR/
3NrgEraBY76VMBcGA1UdEQQQMA6CDHh4Lnl4aW5nLnh5ejANBgkqhkiG9w0BAQsF
AAOCAYEAVVithC9KiAqhuE8eCrfURzmQrMAARuifJUxkuLVNZ+ce8rjo++l1a7Ox
lv5WlylLJXsbAKvFclNiE2FUydz47TS/M4+AIxhzyE1bVvbY8zhx75oEyqpJGdBd
bgO7JDJRc3YbvqOA25sSJCop5wYXBuqlLvivloBQJCJqNvI04QnuU9WG3m4gZ/+C
P6lvqqBiqfrtYzIq7qRqjC9OCnXIUgaJ01me2hxV/pcwLWCq6LUp2aEpQ1KaW7xC
OsrnjvW9t2f0PflKeOfw0bjS0JxWHK4YYGYMOiSeADWpB1ERIU7zU13jDVIahKO+
ekeOf2VhdsChAjpLUWHyiqgG6VmJkXjfAcg/6EwjxdqXKLuUIDkQ6oxlBOYsDTac
NNAJyVF95d9n5l1cHsl3uqiUHgnZdCVp/sVefnx5mL2Yfq6c49bgUOIWPOXRtuvO
StAeaKLbALJsufOgB3DwiC9vBsBnfj9oNCPxUdeCzSJnH3U6/YLi2bLcXwq5uZXQ
9S9fgSv+
-----END CERTIFICATE-----
`
var KEY = `-----BEGIN PRIVATE KEY-----
MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQCy3vQXQNvkjEjD
whqQnnXi4P76MpGW20Nn0Py2D43kd4dCEzMSLUId1fUbMst771Z0fD/MYTfw33ao
NddWV86Lk2aX40Jj8DrHs6xgxrPgb91qNt485jTDVxKkUwNDh696tp1dJnNhxPQK
deuQmeNqpSdVSVys6aDmpzUG+sxsoBv1jNwzXTV0nv5ki6Xn7eZdQRNY+6/nzot4
VYoh7ch3iLGodtP/xr20vZOANaI1RNYYmhyaEG/0QN3uxUYzMG3tGci+iT2iBWhS
kCJ3Qz+uXOY6DI7rRVuEuBCSHa1YheoWYNlIOCAnVVPoZXiy/3Ypi8uKYa9oIfs4
9G7eWFUlAgMBAAECggEAKB4/avO+Hg2kyFtBsAwKbr9+EMnEw6wb+y3xcDge4A47
BQPfYYVLHfv+BIKpBvwQTQINIR7w+BJ2v5WL3a7GAaIm0YxEOLwJwv62e+I1N/J/
G7KAt/H+BY4C/V4tDjlhj0lkFB9qo5QUFECMfBs32ZR/NO7GXXXtA66fAxi/PuFu
FrfK/Cuz3lXn8QIhpmksqO7dpz/c6XknU6qfF6cepVVSlfhIw8NqmxNLg9EAsIH7
Od2FjrMxZkQKbFkozAU/b0x3tsg/PwAs83HzSf/zUcX9AP9OOBhxcoNtox4G89Bi
jzD/hIZPOv7CcQSrj7pySXduKEg9mYuo7EZRv4oChQKBgQDjvUf7RAp4VAbN3VNd
Nx+hAe5CTrd6mhdjs48rXsW24BKmewGL0zvYpRPa0Wim3z0fMLhbqneKd3GfTpE8
cqcGMvhIHEkfGMBAD2LqmUY7DXWlYaUWAEJyXChOz118Q3/Ic9AdNAggaggKfiZs
UaVSp43KmdkwZhmprvbSnf4/ywKBgQDJET3UjXegIPbS+FqZhufRtiylxsCgWtQj
qVzeCOeN2RXxWCW6xXzwIRkoNsJ0ICZ53WbXLChViPnMNlrtAycZumBbbbTk4mqE
COLxZvrIg0Xp+UxDuNvWPslm1sSLZ7FKcszyh7HFX2TpsyGElGGcJqZAD4tfMT4/
iChiT3BAzwKBgDwbS/E8Lws9GiKhZIw4rUdgbBLiFbjtDHlK/eFzfPlcQG/iDTFr
SeNPBmN9W4KXbtlZkX7YCf7osXtbUCfFFuIi97aIiKAFd1Aw/2ltlMSnM8K3d8vL
u73VJupN/p16bzJnpqjef7qWYZLrYpa6Ickj4d90JYeJmwJW5FwISP9rAoGAaEG2
a8ZG5xLwqQf6Am1/OrBZikP6katHII6rBr5bQqPzysbIGYZZeDHRV5a9UXVyPfJd
ZukQqPlzfT4Z+5eM6LxJRl8mUyBL1ta8xit9kgbvc5i+wMbTxs2bpOVr2FUWCuJn
/sH5nbwPGVa25IYD7vHjdogY3m0sN8kkF4XVUOUCgYB2L0TC51Gzk2UzqPHmJgTL
X2KVGcMpzUsifporSt+kg1Gl+JG6b/VSbGwdenFl+zy4pACFaz9HnvoX224tW3HN
fE4sV7VGMuKxTabj8GpBBmemUVOLZRVrtMClHRiWg8NTwYHA7koVFD6ml/T+kv+p
ASpCs86w4R3crQSD2CB1CQ==
-----END PRIVATE KEY-----
`
