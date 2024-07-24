package proxy

type server interface {
	handRequest(string, string) (int, string)
}
