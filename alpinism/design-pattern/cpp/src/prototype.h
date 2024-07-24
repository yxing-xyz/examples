/* 
让你能给复制已有对象, 而又无需使代码依赖他们所属的类.

是什么: 原型模式是一种创建型设计模式， 使你能够复制已有对象， 而又无需使代码依赖它们所属的类。

为什么: 某些对象拥有私有成员变量对象外不可见, 必须知道所属的类才能赋值,也就是代码必须依赖类, 面向接口编程的时候,你并不知道具体的类

怎么做: 原型模式将克隆过程委派给被克隆的实际对象。 模式为所有支持克隆的对象声明了一个通用接口， 该接口让你能够克隆对象， 同时又无需将代码和对象所属类耦合。 通常情况下， 这样的接口中仅包含一个 克隆方法。
*/

#ifndef DESIGN_PATTERNS_PROTOTYPE_H
#define DESIGN_PATTERNS_PROTOTYPE_H

#include <iostream>
#include <string>
#include <unordered_map>

// C++ 的 Cloneable  （克隆） 接口就是立即可用的原型模式。
namespace prototype
{
    using namespace std;

    enum Type
    {
        PROTOTYPE_1 = 0,
        PROTOTYPE_2
    };
    class Prototype
    {
    protected:
        std::string prototype_name_;
        float prototype_field_;

    public:
        Prototype();
        Prototype(std::string prototype_name) : prototype_name_(prototype_name)
        {
        }
        virtual ~Prototype();
        virtual Prototype *Clone() const = 0;
        virtual void Method(float);
    };

    class ConcretePrototype1 : public Prototype
    {
    private:
        float concrete_prototype_field1_;

    public:
        ConcretePrototype1(string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field)
        {
        }
        Prototype *Clone() const override;
    };

    class ConcretePrototype2 : public Prototype
    {
    private:
        float concrete_prototype_field2_;

    public:
        ConcretePrototype2(string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field)
        {
        }

        Prototype *Clone() const override;
    };

    class PrototypeFactory
    {
    private:
        std::unordered_map<Type, Prototype *, std::hash<int>> prototypes_;

    public:
        PrototypeFactory();
        ~PrototypeFactory();

        Prototype *CreatePrototype(Type);
    };

    void Client(PrototypeFactory &);
    void run();
}

#endif //DESIGN_PATTERNS_PROTOTYPE_H
