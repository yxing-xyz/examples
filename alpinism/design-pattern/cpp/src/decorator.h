/*
允许你通过将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为

是什么:
装饰模式是一种结构型设计模式， 允许你通过将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为。

为什么:
假设你正在开发一个提供通知功能的库， 其他程序可使用它向用户发送关于重要事件的通知。
库的最初版本基于 通知器Notifier类， 其中只有很少的几个成员变量， 一个构造函数和一个 send发送方法。 该方法可以接收来自客户端的消息参数， 并将该消息发送给一系列的邮箱， 邮箱列表则是通过构造函数传递给通知器的。 作为客户端的第三方程序仅会创建和配置通知器对象一次， 然后在有重要事件发生时对其进行调用。
此后某个时刻， 你会发现库的用户希望使用除邮件通知之外的功能。 许多用户会希望接收关于紧急事件的手机短信， 还有些用户希望在微信上接收消息， 而公司用户则希望在 QQ 上接收消息。
这有什么难的呢？ 首先扩展 通知器类， 然后在新的子类中加入额外的通知方法。 现在客户端要对所需通知形式的对应类进行初始化， 然后使用该类发送后续所有的通知消息。
但是很快有人会问： ​ “为什么不同时使用多种通知形式呢？ 如果房子着火了， 你大概会想在所有渠道中都收到相同的消息吧。”
你可以尝试创建一个特殊子类来将多种通知方法组合在一起以解决该问题。 但这种方式会使得代码量迅速膨胀， 不仅仅是程序库代码， 客户端代码也会如此。
你必须找到其他方法来规划通知类的结构， 否则它们的数量会在不经意之间打破吉尼斯纪录。


怎么做:
1. 确保业务逻辑可用一个基本组件及多个额外可选层次表示。
2. 找出基本组件和可选层次的通用方法。 创建一个组件接口并在其中声明这些方法。
3. 创建一个具体组件类， 并定义其基础行为。
4. 创建装饰基类， 使用一个成员变量存储指向被封装对象的引用。 该成员变量必须被声明为组件接口类型， 从而能在运行时连接具体组件和装饰。 装饰基类必须将所有工作委派给被封装的对象。
5. 确保所有类实现组件接口。
6. 将装饰基类扩展为具体装饰。 具体装饰必须在调用父类方法 （总是委派给被封装对象） 之前或之后执行自身的行为。
7. 客户端代码负责创建装饰并将其组合成客户端所需的形式。
 */

#ifndef DESIGN_PATTERNS_DECORATOR_H
#define DESIGN_PATTERNS_DECORATOR_H
#include "string"

namespace decorator
{
    class Component
    {
    public:
        virtual ~Component();
        virtual std::string Operation() const = 0;
    };

    class ConcreteComponent : public Component
    {
    public:
        std::string Operation() const override;
    };

    class Decorator : public Component
    {
    protected:
        Component *component_;

    public:
        Decorator(Component *);
        std::string Operation() const override;
    };
    class ConcreteDecoratorA : public Decorator
    {
    private:
        /* data */
    public:
        ConcreteDecoratorA(Component *);
        virtual ~ConcreteDecoratorA();

        std::string Operation() const override;
    };

    class ConcreteDecoratorB : public Decorator
    {
    private:
        /* data */
    public:
        ConcreteDecoratorB(Component *);
        virtual ~ConcreteDecoratorB();

        std::string Operation() const override;
    };

    void ClientCode(Component *);
    void run();
}

#endif //DESIGN_PATTERNS_DECORATOR_H
