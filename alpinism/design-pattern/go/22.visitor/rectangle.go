package visitor

type Rectangle struct {
	L int
	B int
}

func (r *Rectangle) GetType() string {
	return "Rectangle"
}

func (r *Rectangle) Accept(v IVisitor) {
	v.VisitForRectangle(r)
}
