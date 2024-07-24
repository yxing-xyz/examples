/*
是什么:
访问者模式是一种行为设计模式， 它能将算法与其所作用的对象隔离开来。

为什么:
假如你的团队开发了一款能够使用巨型图像中地理信息的应用程序。 图像中的每个节点既能代表复杂实体 （例如一座城市）， 也能代表更精细的对象 （例如工业区和旅游景点等）。 如果节点代表的真实对象之间存在公路， 那么这些节点就会相互连接。 在程序内部， 每个节点的类型都由其所属的类来表示， 每个特定的节点则是一个对象。
一段时间后， 你接到了实现将图像导出到 XML 文件中的任务。 这些工作最初看上去非常简单。 你计划为每个节点类添加导出函数， 然后递归执行图像中每个节点的导出函数。 解决方案简单且优雅： 使用多态机制可以让导出方法的调用代码不会和具体的节点类相耦合。
但你不太走运， 系统架构师拒绝批准对已有节点类进行修改。 他认为这些代码已经是产品了， 不想冒险对其进行修改， 因为修改可能会引入潜在的缺陷。
此外， 他还质疑在节点类中包含导出 XML 文件的代码是否有意义。 这些类的主要工作是处理地理数据。 导出 XML 文件的代码放在这里并不合适。
还有另一个原因， 那就是在此项任务完成后， 营销部门很有可能会要求程序提供导出其他类型文件的功能， 或者提出其他奇怪的要求。 这样你很可能会被迫再次修改这些重要但脆弱的类。

怎么做:
1. 在访问者接口中声明一组 “访问” 方法， 分别对应程序中的每个具体元素类。
2. 声明元素接口。 如果程序中已有元素类层次接口， 可在层次结构基类中添加抽象的 “接收” 方法。 该方法必须接受访问者对象作为参数。
3. 在所有具体元素类中实现接收方法。 这些方法必须将调用重定向到当前元素对应的访问者对象中的访问者方法上。
4. 元素类只能通过访问者接口与访问者进行交互。 不过访问者必须知晓所有的具体元素类， 因为这些类在访问者方法中都被作为参数类型引用。
5. 为每个无法在元素层次结构中实现的行为创建一个具体访问者类并实现所有的访问者方法。
你可能会遇到访问者需要访问元素类的部分私有成员变量的情况。 在这种情况下， 你要么将这些变量或方法设为公有， 这将破坏元素的封装； 要么将访问者类嵌入到元素类中。 后一种方式只有在支持嵌套类的编程语言中才可能实现。
6. 客户端必须创建访问者对象并通过 “接收” 方法将其传递给元素。

*/
#ifndef DESIGN_PATTERNS_VISITOR_H
#define DESIGN_PATTERNS_VISITOR_H

#include <string>
#include <array>
namespace visitor
{
  class ConcreteComponentA;
  class ConcreteComponentB;
  class Visitor
  {
  public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA *) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB *) const = 0;
  };

  class Component
  {
  public:
    virtual ~Component();
    virtual void Accept(Visitor *) const = 0;
  };

  class ConcreteComponentA : public Component
  {
  public:
    void Accept(Visitor *) const override;
    std::string ExclusiveMethodOfConcreteComponentA() const;
  };

  class ConcreteComponentB : public Component
  {
  public:
    void Accept(Visitor *) const override;
    std::string SpecialMethodOfConcreteComponentB() const;
  };

  class ConcreteVisitor1 : public Visitor
  {
  public:
    void VisitConcreteComponentA(const ConcreteComponentA *) const override;
    void VisitConcreteComponentB(const ConcreteComponentB *) const override;
  };

  class ConcreteVisitor2 : public Visitor
  {
  public:
    void VisitConcreteComponentA(const ConcreteComponentA *) const override;
    void VisitConcreteComponentB(const ConcreteComponentB *) const override;
  };
  void ClientCode(std::array<const Component *, 2>, Visitor *);
  void run();

} // namespace visitor

#endif //DESIGN_PATTERNS_VISITOR_H
