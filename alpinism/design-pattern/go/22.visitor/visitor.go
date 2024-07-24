package visitor

type IVisitor interface {
	VisitForSquare(*Square)
	VisitForCircle(*Circle)
	VisitForRectangle(*Rectangle)
}
