package strategy

type Cache struct {
	storage      map[string]string
	EvictionAlgo EvictionAlgo
	capacity     int
	maxCapacity  int
}

func InitCache(e EvictionAlgo) *Cache {
	return &Cache{
		storage:      make(map[string]string),
		EvictionAlgo: e,
		capacity:     0,
		maxCapacity:  2,
	}
}

func (c *Cache) SetEvictionAlgo(e EvictionAlgo) {
	c.EvictionAlgo = e
}

func (c *Cache) Add(key, val string) {
	if c.capacity == c.maxCapacity {
		c.Evict()
	}
	c.capacity++
	c.storage[key] = val
}

func (c *Cache) Evict() {
	c.EvictionAlgo.Evict(c)
	c.capacity--
}
