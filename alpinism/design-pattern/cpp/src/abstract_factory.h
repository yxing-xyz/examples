/*
让你能创建一系列相关的对象,而无需指定其具体类.

是什么:
抽象工厂模式是一种创建型设计模式， 它能创建一系列相关的对象， 而无需指定其具体类。


为什么:
假设你正在开发一款家具商店模拟器。 你的代码中包括一些类， 用于表示：
1. 一系列相关产品， 例如 椅子Chair 、 ​ 沙发Sofa和 咖啡桌Coffee­Table 。
2. 系列产品的不同变体。 例如， 你可以使用 现代Modern 、 ​ 维多利亚Victorian 、 ​ 装饰风艺术Art­Deco等风格生成 椅子 、 ​ 沙发和 咖啡桌 。
你需要设法单独生成每件家具对象， 这样才能确保其风格一致。 如果顾客收到的家具风格不一样， 他们可不会开心。
此外， 你也不希望在添加新产品或新风格时修改已有代码。 家具供应商对于产品目录的更新非常频繁， 你不会想在每次更新时都去修改核心代码的。


怎么做:
1. 以不同的产品类型与产品变体为维度绘制矩阵。
2. 为所有产品声明抽象产品接口。 然后让所有具体产品类实现这些接口。
3. 声明抽象工厂接口， 并且在接口中为所有抽象产品提供一组构建方法。
4. 为每种产品变体实现一个具体工厂类。
5. 在应用程序中开发初始化代码。 该代码根据应用程序配置或当前环境， 对特定具体工厂类进行初始化。 然后将该工厂对象传递给所有需要创建产品的类。
6.找出代码中所有对产品构造函数的直接调用， 将其替换为对工厂对象中相应构建方法的调用。
 */
#ifndef DESIGN_PATTERNS_ABSTRACT_FACTORY_H
#define DESIGN_PATTERNS_ABSTRACT_FACTORY_H

#include "factory_method.h"
#include <string>

namespace abstract_factory
{
    class AbstractProductA
    {
    public:
        virtual ~AbstractProductA(){};
        virtual std::string UsefulFunctionA() const = 0;
    };
    class ConcreteProductA1 : public AbstractProductA
    {
    public:
        std::string UsefulFunctionA() const override;
    };
    class ConcreteProductA2 : public AbstractProductA
    {
    public:
        std::string UsefulFunctionA() const override;
    };

    class AbstractProductB
    {
    public:
        virtual ~AbstractProductB(){};
        virtual std::string UsefulFunctionB() const = 0;
        virtual std::string
        AnotherUsefulFunctionB(const AbstractProductA &) const = 0;
    };
    class ConcreteProductB1 : public AbstractProductB
    {
    public:
        virtual std::string UsefulFunctionB() const override;
        std::string
        AnotherUsefulFunctionB(const AbstractProductA &) const override;
    };
    class ConcreteProductB2 : public AbstractProductB
    {
    public:
        virtual std::string UsefulFunctionB() const override;
        std::string
        AnotherUsefulFunctionB(const AbstractProductA &) const override;
    };

    class AbstractFactory
    {
    public:
        virtual AbstractProductA *CreateProductA() const = 0;
        virtual AbstractProductB *CreateProductB() const = 0;
    };
    class ConcreteFactory1 : public AbstractFactory
    {
    public:
        AbstractProductA *CreateProductA() const override;
        AbstractProductB *CreateProductB() const override;
    };
    class ConcreteFactory2 : public AbstractFactory
    {
    public:
        AbstractProductA *CreateProductA() const override;
        AbstractProductB *CreateProductB() const override;
    };

    // 测试代码
    void ClientCode(AbstractFactory &);
    void run();
}

#endif //DESIGN_PATTERNS_ABSTRACT_FACTORY_H
