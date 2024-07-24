/*
是什么:
迭代器模式是一种行为设计模式， 让你能在不暴露集合底层表现形式 （列表、 栈和树等） 的情况下遍历集合中所有的元素。

为什么:
集合是编程中最常使用的数据类型之一。 尽管如此， 集合只是一组对象的容器而已。
大部分集合使用简单列表存储元素。 但有些集合还会使用栈、 树、 图和其他复杂的数据结构。
无论集合的构成方式如何， 它都必须提供某种访问元素的方式， 便于其他代码使用其中的元素。 集合应提供一种能够遍历元素的方式， 且保证它不会周而复始地访问同一个元素。
如果你的集合基于列表， 那么这项工作听上去仿佛很简单。 但如何遍历复杂数据结构 （例如树） 中的元素呢？ 例如， 今天你需要使用深度优先算法来遍历树结构， 明天可能会需要广度优先算法； 下周则可能会需要其他方式 （比如随机存取树中的元素）。
不断向集合中添加遍历算法会模糊其 “高效存储数据” 的主要职责。 此外， 有些算法可能是根据特定应用订制的， 将其加入泛型集合类中会显得非常奇怪。
另一方面， 使用多种集合的客户端代码可能并不关心存储数据的方式。 不过由于集合提供不同的元素访问方式， 你的代码将不得不与特定集合类进行耦合。



怎么做:
1. 声明迭代器接口。 该接口必须提供至少一个方法来获取集合中的下个元素。 但为了使用方便， 你还可以添加一些其他方法， 例如获取前一个元素、 记录当前位置和判断迭代是否已结束。
2. 声明集合接口并描述一个获取迭代器的方法。 其返回值必须是迭代器接口。 如果你计划拥有多组不同的迭代器， 则可以声明多个类似的方法。
3. 为希望使用迭代器进行遍历的集合实现具体迭代器类。 迭代器对象必须与单个集合实体链接。 链接关系通常通过迭代器的构造函数建立。
4. 在你的集合类中实现集合接口。 其主要思想是针对特定集合为客户端代码提供创建迭代器的快捷方式。 集合对象必须将自身传递给迭代器的构造函数来创建两者之间的链接。
5. 检查客户端代码， 使用迭代器替代所有集合遍历代码。 每当客户端需要遍历集合元素时都会获取一个新的迭代器。
*/
#ifndef _INTERATOR_H_
#define _INTERATOR_H_
#include <vector>
namespace iterator
{
    template <typename T, typename U>
    class Iterator
    {

    public:
        typedef typename std::vector<T>::iterator iter_type;
        Iterator(U *p_data, bool = false) : m_p_data_(p_data)
        {
            m_it_ = m_p_data_->m_data_.begin();
        }
        void First();
        void Next();
        bool IsDone();
        iter_type Current()
        {
            return m_it_;
        }

    private:
        U *m_p_data_;
        iter_type m_it_;
    };

    template <class T>
    class Container
    {

        friend class Iterator<T, Container>;

    public:
        void Add(T a)
        {
            m_data_.push_back(a);
        }

        Iterator<T, Container> *CreateIterator()
        {
            return new Iterator<T, Container>(this);
        }

    private:
        std::vector<T> m_data_;
    };

    class Data
    {
    public:
        Data(int = 0);
        void set_data(int);
        int data();

    private:
        int m_data_;
    };

    void ClientCode();
    void run();
}
#endif
