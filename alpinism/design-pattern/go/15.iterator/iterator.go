package iterator

type IIterator interface {
	hasNext() bool
	GetNext() *User
}
