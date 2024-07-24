/*
你可以使用它将对象组合成树状结构, 并且能像使用独立对象一样使用他们.

是什么:
组合模式是一种结构型设计模式， 你可以使用它将对象组合成树状结构， 并且能像使用独立对象一样使用它们。

为什么:
订单包含套餐和商品, 套餐嵌套商品.
例如， 你有两类对象： ​ 产品和 盒子 。 一个盒子中可以包含多个 产品或者几个较小的 盒子 。 这些小 盒子中同样可以包含一些 产品或更小的 盒子 ， 以此类推。
假设你希望在这些类的基础上开发一个定购系统。 订单中可以包含无包装的简单产品， 也可以包含装满产品的盒子……以及其他盒子。 此时你会如何计算每张订单的总价格呢？

怎么做:
1. 确保应用的核心模型能够以树状结构表示。 尝试将其分解为简单元素和容器。 记住， 容器必须能够同时包含简单元素和其他容器。
2. 声明组件接口及其一系列方法， 这些方法对简单和复杂元素都有意义。
3. 创建一个叶节点类表示简单元素。 程序中可以有多个不同的叶节点类。
4. 创建一个容器类表示复杂元素。 在该类中， 创建一个数组成员变量来存储对于其子元素的引用。 该数组必须能够同时保存叶节点和容器， 因此请确保将其声明为组合接口类型。
实现组件接口方法时， 记住容器应该将大部分工作交给其子元素来完成。
5. 最后， 在容器中定义添加和删除子元素的方法。
记住， 这些操作可在组件接口中声明。 这将会违反_接口隔离原则_， 因为叶节点类中的这些方法为空。 但是， 这可以让客户端无差别地访问所有元素， 即使是组成树状结构的元素。
 */

#ifndef DESIGN_PATTERNS_COMPOSITE_H
#define DESIGN_PATTERNS_COMPOSITE_H
#include <string>
#include <list>
namespace composite
{
    class Component
    {
    protected:
        Component *parent_;

    public:
        virtual ~Component();
        void SetParent(Component *);
        Component *GetParent();
        virtual void Add(Component *);
        virtual void Remove(Component *);
        virtual bool IsComposite() const;
        virtual std::string Operation() const = 0;
    };

    class Leaf : public Component
    {
    public:
        std::string Operation() const;
    };

    class Composite : public Component
    {
    protected:
        std::list<Component *> children_;

    public:
        void Add(Component *) override;
        void Remove(Component *) override;
        std::string Operation() const override;
    };

    void ClientCode(const Component *);
    void ClientCode2(Component *, Component *);
    void run();
}

#endif //DESIGN_PATTERNS_COMPOSITE_H
