//
// Created by Jennica on 2016/12/26.
//

#include "factory_method.h"
#include <iostream>
#include <string>

namespace facotry_method
{
    std::string ConcreteProduct1::Operation() const
    {
        return "{Result of the ConcreteProduct1}";
    }

    std::string ConcreteProduct2::Operation() const
    {
        return "{Result of the ConcreteProduct2}";
    }

    std::string Creator::SomeOperation() const
    {
        Product *product = this->FactoryMethod();
        std::string result = product->Operation();
        delete product;
        return result;
    }

    Product *ConcreteCreator1::FactoryMethod() const
    {
        return new ConcreteProduct1();
    }

    Product *ConcreteCreator2::FactoryMethod() const
    {
        return new ConcreteProduct2();
    }

    void run()
    {
        Creator *creator = new ConcreteCreator1();
        Product *product = creator->FactoryMethod();
        std::cout << product->Operation() << std::endl;
        delete creator;
        delete product;

        creator = new ConcreteCreator2();
        product = creator->FactoryMethod();
        std::cout << product->Operation() << std::endl;
        delete creator;
        delete product;
    }
}
