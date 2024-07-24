package strategy

import "fmt"

type Lfu struct {
}

func (l *Lfu) Evict(c *Cache) {
	fmt.Println("evicting by lfu strtegy")
}
