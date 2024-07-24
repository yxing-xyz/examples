package visitor

type Circle struct {
	Radius int
}

func (c *Circle) GetType() string {
	return "Cirecl"
}

func (c *Circle) Accept(v IVisitor) {
	v.VisitForCircle(c)
}
