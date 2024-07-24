
/* 
使你能给分步骤创建复杂对象. 该模式允许你使用相同的创建代码生成不同类型和形式的对象.

是什么： 生成器模式是一种创建型设计模式， 使你能够分布创建复杂对象。 该模式允许你使用相同的创建代码生成不同类型和形式的对象。

为什么： 构建复杂对象房屋， 最简单的方法是扩展房屋基类， 然后创建一系列涵盖所有参数组合的子类。 但最终你将面对相当数量的子类。 任何新增的参数 （例如门廊类型） 都会让这个层次结构更加复杂。另一种方法则无需生成子类。 你可以在 房屋基类中创建一个包括所有可能参数的超级构造函数， 并用它来控制房屋对象。 这种方法确实可以避免生成子类， 但它却会造成另外一个问题。绝大多数参数没有用到，对构造参数的调用十分不简洁。

怎么做: 生成器模式建议将对象构造代码从产品类中抽取出来， 并将其放在一个名为生成器的独立对象中。
*/
#ifndef DESIGN_PATTERNS_BUILDER_H
#define DESIGN_PATTERNS_BUILDER_H
#include <string>
#include <vector>
namespace builder
{
    class Product1
    {
    public:
        std::vector<std::string> parts_;
        void ListParts() const;
    };
    class Builder
    {
    public:
        virtual ~Builder() {}
        virtual void ProducePartA() const = 0;
        virtual void ProducePartB() const = 0;
        virtual void ProducePartC() const = 0;
    };
    class ConcreteBuilder1 : public Builder
    {
    private:
        Product1 *product1;

    public:
        ConcreteBuilder1();
        ~ConcreteBuilder1();
        void Reset();
        void ProducePartA() const override;
        void ProducePartB() const override;
        void ProducePartC() const override;
        Product1 *GetProduct();
    };

    class Director
    {
    private:
        Builder *builder;

    public:
        void SetBuilder(Builder *);

        void BuildMinimalViableProduct() const;

        void BuildFullFeaturedProduct() const;
    };

    void ClientCode(Director &);
    void run();
}
#endif //DESIGN_PATTERNS_BUILDER_H
