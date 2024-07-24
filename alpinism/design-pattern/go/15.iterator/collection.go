package iterator

type ICollection interface {
	CreateIterator() IIterator
}
