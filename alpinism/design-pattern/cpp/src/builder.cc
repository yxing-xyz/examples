#include "builder.h"
#include <cstddef>
#include <iostream>
#include <ostream>

namespace builder
{
    using namespace std;
    void Product1::ListParts() const
    {
        cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++)
        {
            if (parts_[i] == parts_.back())
            {
                cout << parts_[i];
            }
            else
            {
                cout << parts_[i] << ", ";
            }
        }
        cout << endl;
    }

    ConcreteBuilder1::ConcreteBuilder1()
    {
        this->Reset();
    }
    ConcreteBuilder1::~ConcreteBuilder1()
    {
        delete this->product1;
    }
    void ConcreteBuilder1::Reset()
    {
        this->product1 = new Product1();
    }
    void ConcreteBuilder1::ProducePartA() const
    {
        this->product1->parts_.push_back("PartA1");
    }
    void ConcreteBuilder1::ProducePartB() const
    {
        this->product1->parts_.push_back("PartB1");
    }
    void ConcreteBuilder1::ProducePartC() const
    {
        this->product1->parts_.push_back("PartC1");
    }
    Product1 *ConcreteBuilder1::GetProduct()
    {
        Product1 *result = this->product1;
        this->Reset();
        return result;
    }

    void Director::SetBuilder(Builder *builder)
    {
        this->builder = builder;
    }
    void Director::BuildMinimalViableProduct() const
    {
        this->builder->ProducePartA();
    }

    void Director::BuildFullFeaturedProduct() const
    {
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }


    // 测试代码
    void ClientCode(Director &director)
    {
        ConcreteBuilder1 *builder = new ConcreteBuilder1();
        director.SetBuilder(builder);
        std::cout << "Standard basic product:\n";
        director.BuildMinimalViableProduct();
        Product1 *p = builder->GetProduct();
        p->ListParts();
        delete p;

        std::cout << "Standard full featured product:\n";
        director.BuildFullFeaturedProduct();

        p = builder->GetProduct();
        p->ListParts();
        delete p;

        // Remember, the Builder pattern can be used without a Director class.
        std::cout << "Custom product:\n";
        builder->ProducePartA();
        builder->ProducePartC();
        p = builder->GetProduct();
        p->ListParts();
        delete p;

        delete builder;
    }
    void run()
    {
        Director *director = new Director();
        ClientCode(*director);
        delete director;
    }
}
