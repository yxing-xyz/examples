package proxy

type nginx struct {
	application       *application
	maxAllowedRequest int
	rateLimiter       map[string]int
}

func newNginxServer() *nginx {
	return &nginx{
		application:       &application{},
		maxAllowedRequest: 2,
		rateLimiter:       make(map[string]int),
	}
}

func (this *nginx) handleRequest(url, method string) (int, string) {
	allowed := this.checkRateLimiting(url)
	if !allowed {
		return 403, "Not Allowed"
	}
	return this.application.handleRequest(url, method)

}

func (this *nginx) checkRateLimiting(url string) bool {
	if this.rateLimiter[url] == 0 {
		this.rateLimiter[url] = 1
	}
	if this.rateLimiter[url] > this.maxAllowedRequest {
		return false
	}
	this.rateLimiter[url] = this.rateLimiter[url] + 1
	return true

}
