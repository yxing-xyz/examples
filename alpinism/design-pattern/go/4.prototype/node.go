package prototype

type INode interface {
	Print(string)
	Clone() INode
}
