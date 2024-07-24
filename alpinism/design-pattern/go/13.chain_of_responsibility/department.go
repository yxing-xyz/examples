package chain_of_responsibility

// 处理者接口
type IDepartMent interface {
	Execute(*Patient)
	SetNext(IDepartMent)
}
