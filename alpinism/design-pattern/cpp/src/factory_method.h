/*
在父类种提供一个创建对象的接口以允许子类决定实例化对象的类型

是什么:
工厂方法模式是一种创建型设计模式， 其在父类中提供一个创建对象的方法， 允许子类决定实例化对象的类型。

为什么:
比如本身业务只有微信支付,突然增加支付宝支付,代码其余部分与现有类已经存在耦合关系
当你在编写代码的过程中， 如果无法预知对象确切类别及其依赖关系时， 可使用工厂方法。
如果你希望用户能扩展你软件库或框架的内部组件， 可使用工厂方法。

怎么做:
1. 让所有产品都遵循同一接口。 该接口必须声明对所有产品都有意义的方法。

2. 在创建类中添加一个空的工厂方法。 该方法的返回类型必须遵循通用的产品接口。

3. 在创建者代码中找到对于产品构造函数的所有引用。 将它们依次替换为对于工厂方法的调用， 同时将创建产品的代码移入工厂方法。 你可能需要在工厂方法中添加临时参数来控制返回的产品类型。

4. 为工厂方法中的每种产品编写一个创建者子类， 然后在子类中重写工厂方法， 并将基本方法中的相关创建代码移动到工厂方法中。

5. 如果应用中的产品类型太多， 那么为每个产品创建子类并无太大必要， 这时你也可以在子类中复用基类中的控制参数。
例如， 设想你有以下一些层次结构的类。 基类 邮件及其子类 航空邮件和 陆路邮件 ； ​ 运输及其子类 飞机, 卡车和 火车 。 ​ 航空邮件仅使用 飞机对象， 而 陆路邮件则会同时使用 卡车和 火车对象。 你可以编写一个新的子类 （例如 火车邮件 ） 来处理这两种情况， 但是还有其他可选的方案。 客户端代码可以给 陆路邮件类传递一个参数， 用于控制其希望获得的产品。

6. 如果代码经过上述移动后， 基础工厂方法中已经没有任何代码， 你可以将其转变为抽象类。 如果基础工厂方法中还有其他语句， 你可以将其设置为该方法的默认行为。
*/


#ifndef DESIGN_PATTERNS_FACTORY_METHOD_H
#define DESIGN_PATTERNS_FACTORY_METHOD_H

#include <string>
#include <iostream>
namespace facotry_method {
    class Product {
    public:
        virtual ~Product() {}
        virtual std::string Operation() const = 0;
    };

    class ConcreteProduct1: public Product {
    public:
        std::string Operation() const override;
    };

    class ConcreteProduct2: public Product {
    public:
        std::string Operation() const override;
    };

    class Creator {
    public:
        virtual ~Creator(){};
        virtual Product* FactoryMethod() const = 0;
        std::string SomeOperation() const ;
    };

    class ConcreteCreator1: public Creator {
    public:
        Product* FactoryMethod() const override;
    };

    class ConcreteCreator2: public Creator {
    public:
        Product* FactoryMethod() const override;
    };


    // 测试代码
    void run();
}


#endif //DESIGN_PATTERNS_FACTORY_METHOD_H
