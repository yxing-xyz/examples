package proxy

type application struct{}

func (this *application) handleRequest(url, method string) (int, string) {
	if url == "/app/status" && method == "GET" {
		return 200, "ok"
	}

	if url == "/create/user" && method == "GET" {
		return 201, "User Created"
	}
	return 404, "Not Ok"
}
