#include "abstract_factory.h"
#include "factory_method.h"
#include <iostream>
#include <string>

namespace abstract_factory
{
    std::string ConcreteProductA1::UsefulFunctionA() const
    {
        return "The result of the product A1.";
    }
    std::string ConcreteProductA2::UsefulFunctionA() const
    {
        return "The result of the product A2.";
    }
    std::string ConcreteProductB1::UsefulFunctionB() const
    {
        return "The result of the product B1.";
    }
    std::string ConcreteProductB1::AnotherUsefulFunctionB(const AbstractProductA &collaborator) const
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + result + " )";
    }
    std::string ConcreteProductB2::UsefulFunctionB() const
    {
        return "The result of the product B2.";
    }
    std::string ConcreteProductB2::AnotherUsefulFunctionB(const AbstractProductA &collaborator) const
    {
        const std::string result = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + result + " )";
    }

    AbstractProductA *ConcreteFactory1::CreateProductA() const
    {
        return new ConcreteProductA1();
    }
    AbstractProductB *ConcreteFactory1::CreateProductB() const
    {
        return new ConcreteProductB1();
    }
    AbstractProductA *ConcreteFactory2::CreateProductA() const
    {
        return new ConcreteProductA2();
    }
    AbstractProductB *ConcreteFactory2::CreateProductB() const
    {
        return new ConcreteProductB2();
    }

    void ClientCode(AbstractFactory &f)
    {
        // 剥离掉了工厂模式创建的风格（泛化），保留产品的职责，使职责更加单一函数更加清晰
        const AbstractProductA *productA = f.CreateProductA();
        const AbstractProductB *productB = f.CreateProductB();
        std::cout << productB->UsefulFunctionB() << std::endl;
        std::cout << productB->AnotherUsefulFunctionB(*productA) << std::endl;
        delete productA;
        delete productB;
    }
    void run()
    {
        ConcreteFactory1 *f1 = new ConcreteFactory1();
        ClientCode(*f1);
        delete f1;
        ConcreteFactory2 *f2 = new ConcreteFactory2();
        ClientCode(*f2);
        delete f2;
    }
}
