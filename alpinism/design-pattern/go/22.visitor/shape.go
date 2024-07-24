package visitor

type IShape interface {
	GetType() string
	Accept(IVisitor)
}
