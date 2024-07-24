/*
是什么:
观察者模式是一种行为设计模式， 允许你定义一种订阅机制， 可在对象事件发生时通知多个 “观察” 该对象的其他对象。

为什么
假如你有两种类型的对象： ​ 顾客和 商店 。 顾客对某个特定品牌的产品非常感兴趣 （例如最新型号的 iPhone 手机）， 而该产品很快将会在商店里出售。
顾客可以每天来商店看看产品是否到货。 但如果商品尚未到货时， 绝大多数来到商店的顾客都会空手而归。
另一方面， 每次新产品到货时， 商店可以向所有顾客发送邮件 （可能会被视为垃圾邮件）。 这样， 部分顾客就无需反复前往商店了， 但也可能会惹恼对新产品没有兴趣的其他顾客。
我们似乎遇到了一个矛盾： 要么让顾客浪费时间检查产品是否到货， 要么让商店浪费资源去通知没有需求的顾客。

怎么做:
1. 仔细检查你的业务逻辑， 试着将其拆分为两个部分： 独立于其他代码的核心功能将作为发布者； 其他代码则将转化为一组订阅类。

2. 声明订阅者接口。 该接口至少应声明一个 update方法。

3. 声明发布者接口并定义一些接口来在列表中添加和删除订阅对象。 记住发布者必须仅通过订阅者接口与它们进行交互。

4. 确定存放实际订阅列表的位置并实现订阅方法。 通常所有类型的发布者代码看上去都一样， 因此将列表放置在直接扩展自发布者接口的抽象类中是显而易见的。 具体发布者会扩展该类从而继承所有的订阅行为。
但是， 如果你需要在现有的类层次结构中应用该模式， 则可以考虑使用组合的方式： 将订阅逻辑放入一个独立的对象， 然后让所有实际订阅者使用该对象。

5. 创建具体发布者类。 每次发布者发生了重要事件时都必须通知所有的订阅者。

6. 在具体订阅者类中实现通知更新的方法。 绝大部分订阅者需要一些与事件相关的上下文数据。 这些数据可作为通知方法的参数来传递。
但还有另一种选择。 订阅者接收到通知后直接从通知中获取所有数据。 在这种情况下， 发布者必须通过更新方法将自身传递出去。 另一种不太灵活的方式是通过构造函数将发布者与订阅者永久性地连接起来。

7. 客户端必须生成所需的全部订阅者， 并在相应的发布者处完成注册工作。


*/

#ifndef DESIGN_PATTERNS_OBSERVER_H
#define DESIGN_PATTERNS_OBSERVER_H

#include <string>
#include <list>
namespace observer
{
    class IObserver
    {
    public:
        virtual ~IObserver();
        virtual void Update(const std::string &) = 0;
    };

    class ISubject
    {
    public:
        virtual ~ISubject(){};
        virtual void Attach(IObserver *) = 0;
        virtual void Detach(IObserver *) = 0;
        virtual void Notify() = 0;
    };

    class Subject : public ISubject
    {
    public:
        virtual ~Subject();
        void Attach(IObserver *) override;
        void Detach(IObserver *) override;
        void Notify() override;

        void CreateMessage(std::string = "Empty");
        void HowManyObserver();
        void SomeBusinessLogic();

    private:
        std::list<IObserver *> list_observer_;
        std::string message_;
    };

    class Observer : public IObserver
    {
    public:
        Observer(Subject &);
        virtual ~Observer();
        void Update(const std::string &) override;
        void RemoveMeFromTheList();
        void PrintInfo();

    private:
        std::string message_from_subject_;
        Subject &subject_;
        static int static_number_;
        int number_;
    };

    void ClientCode();
    void Run();
}

#endif
