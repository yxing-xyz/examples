/*
可将一个大类或一系列紧密相关的类拆分为抽象和实现两个独立的结构层次, 从而能在开发的时候分别使用.

是什么:
桥接模式是一种结构型设计模式， 可将一个大类或一系列紧密相关的类拆分为抽象和实现两个独立的层次结构， 从而能在开发时分别使用。
桥接模式通常会于开发前期进行设计， 使你能够将程序的各个部分独立开来以便开发。 另一方面， 适配器模式通常在已有程序中使用， 让相互不兼容的类能很好地合作。

为什么:
你有一个基类形状(Shape),它有两个派生类圆形(Circle)和方形(Square), 你需要对这样的类层次结构拓展使它们包含颜色,所以你打算创建红色(Red)和蓝色(Blue)的形状子类,因为已经有圆形和方形了你需要拓展就会产生红色圆形和红色方形, 蓝色圆形和蓝色方形, 每增加一种颜色或者形状都会导致产生Shape的子类.如此以往,情况会越来月糟糕.

怎么做:
1. 明确类中独立的维度。 独立的概念可能是： 抽象/平台， 域/基础设施， 前端/后端或接口/实现。
2. 了解客户端的业务需求， 并在抽象基类中定义它们。
3. 确定在所有平台上都可执行的业务。 并在通用实现接口中声明抽象部分所需的业务。
4. 为你域内的所有平台创建实现类， 但需确保它们遵循实现部分的接口。
5. 在抽象类中添加指向实现类型的引用成员变量。 抽象部分会将大部分工作委派给该成员变量所指向的实现对象。
6. 如果你的高层逻辑有多个变体， 则可通过扩展抽象基类为每个变体创建一个精确抽象。
7. 客户端代码必须将实现对象传递给抽象部分的构造函数才能使其能够相互关联。 此后， 客户端只需与抽象对象进行交互， 无需和实现对象打交道。

心得:
抽象层: 抽象类依赖接口,虚函数可以提供一个默认的功能实现

实现层: 具体派生类实现接口, 抽象类可以覆盖抽象类的功能函数且接收实现接口

依赖导致原则: 派生类实现接口(细节依赖抽象),客户端代码依赖抽象接口(高层模块依赖抽象)
*/

#ifndef DESIGN_PATTERNS_BRIDGE_H
#define DESIGN_PATTERNS_BRIDGE_H
#include <string>
namespace bridge
{
  class Implementation
  {
  public:
    virtual ~Implementation();
    virtual std::string OperationImplementation() const = 0;
  };

  class ConcreteImplementationA : public Implementation
  {
  public:
    std::string OperationImplementation() const override;
  };

  class ConcreteImplementationB : public Implementation
  {
  public:
    std::string OperationImplementation() const override;
  };

  class Abstraction
  {
  protected:
    Implementation *implementation_;

  public:
    Abstraction(Implementation *);
    virtual ~Abstraction();
    virtual std::string Operation() const;
  };

  class ExtendedAbstraction : public Abstraction
  {
  public:
    ExtendedAbstraction(Implementation *);
    std::string Operation() const override;
  };

  void ClientCode(const Abstraction &);
  void run();
}
#endif //DESIGN_PATTERNS_BRIDGE_H
