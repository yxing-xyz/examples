/*
是什么:
模板方法模式是一种行为设计模式， 它在超类中定义了一个算法的框架， 允许子类在不修改结构的情况下重写算法的特定步骤。

为什么:
假如你正在开发一款分析公司文档的数据挖掘程序。 用户需要向程序输入各种格式 （PDF、 DOC 或 CSV） 的文档， 程序则会试图从这些文件中抽取有意义的数据， 并以统一的格式将其返回给用户。
该程序的首个版本仅支持 DOC 文件。 在接下来的一个版本中， 程序能够支持 CSV 文件。 一个月后， 你 “教会” 了程序从 PDF 文件中抽取数据。
一段时间后， 你发现这三个类中包含许多相似代码。 尽管这些类处理不同数据格式的代码完全不同， 但数据处理和分析的代码却几乎完全一样。 如果能在保持算法结构完整的情况下去除重复代码， 这难道不是一件很棒的事情吗？
还有另一个与使用这些类的客户端代码相关的问题： 客户端代码中包含许多条件语句， 以根据不同的处理对象类型选择合适的处理过程。 如果所有处理数据的类都拥有相同的接口或基类， 那么你就可以去除客户端代码中的条件语句， 转而使用多态机制来在处理对象上调用函数。

怎么做:
1. 分析目标算法， 确定能否将其分解为多个步骤。 从所有子类的角度出发， 考虑哪些步骤能够通用， 哪些步骤各不相同。
2. 创建抽象基类并声明一个模板方法和代表算法步骤的一系列抽象方法。 在模板方法中根据算法结构依次调用相应步骤。 可用 final最终修饰模板方法以防止子类对其进行重写。
3. 虽然可将所有步骤全都设为抽象类型， 但默认实现可能会给部分步骤带来好处， 因为子类无需实现那些方法。
4. 可考虑在算法的关键步骤之间添加钩子。

*/

#ifndef DESIGN_PATTERNS_TEMPLATE_METHOD_H
#define DESIGN_PATTERNS_TEMPLATE_METHOD_H

namespace template_method
{
  class AbstracClass
  {
  public:
    void TemplateMethod() const;

  protected:
    void BaseOperation1() const;
    void BaseOperation2() const;
    void BaseOperation3() const;

    virtual void RequiredOperations1() const = 0;
    virtual void RequiredOperation2() const = 0;
    virtual void Hook1() const;
    virtual void Hook2() const;
  };

  class ConcreteClass1 : public AbstracClass
  {
  protected:
    void RequiredOperations1() const override;
    void RequiredOperation2() const override;
  };

  class ConcreteClass2 : public AbstracClass
  {
  protected:
    void RequiredOperations1() const override;
    void RequiredOperation2() const override;
    void Hook1() const override;
  };

  void ClientCode(AbstracClass *);
  void run();
}

#endif //DESIGN_PATTERNS_TEMPLATE_METHOD_H
