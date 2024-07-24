package visitor

type Square struct {
	Side int
}

func (s *Square) GetType() string {
	return "Square"
}

func (s *Square) Accept(v IVisitor) {
	v.VisitForSquare(s)
}