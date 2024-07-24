/*
是什么:
中介者模式是一种行为设计模式， 能让你减少对象之间混乱无序的依赖关系。 该模式会限制对象之间的直接交互， 迫使它们通过一个中介者对象进行合作。

为什么:
假如你有一个创建和修改客户资料的对话框， 它由各种控件组成， 例如文本框 （Text­Field）、 复选框 （Checkbox） 和按钮 （Button） 等。
某些表单元素可能会直接进行互动。 例如， 选中 “我有一只狗” 复选框后可能会显示一个隐藏文本框用于输入狗狗的名字。 另一个例子是提交按钮必须在保存数据前校验所有输入内容。
如果直接在表单元素代码中实现业务逻辑， 你将很难在程序其他表单中复用这些元素类。 例如， 由于复选框类与狗狗的文本框相耦合， 所以将无法在其他表单中使用它。 你要么使用渲染资料表单时用到的所有类， 要么一个都不用。

怎么做:
1. 找到一组当前紧密耦合， 且提供其独立性能带来更大好处的类 （例如更易于维护或更方便复用）。

2. 声明中介者接口并描述中介者和各种组件之间所需的交流接口。 在绝大多数情况下， 一个接收组件通知的方法就足够了。 如果你希望在不同情景下复用组件类， 那么该接口将非常重要。 
只要组件使用通用接口与其中介者合作， 你就能将该组件与不同实现中的中介者进行连接。

3. 实现具体中介者类。 该类可从自行保存其下所有组件的引用中受益。

4. 你可以更进一步， 让中介者负责组件对象的创建和销毁。 此后， 中介者可能会与工厂或外观类似。

5. 组件必须保存对于中介者对象的引用。 该连接通常在组件的构造函数中建立， 该函数会将中介者对象作为参数传递。

6. 修改组件代码， 使其可调用中介者的通知方法， 而非其他组件的方法。 然后将调用其他组件的代码抽取到中介者类中， 并在中介者接收到该组件通知时执行这些代码。
*/

#ifndef DESIGN_PATTERNS_MEDIATOR_H
#define DESIGN_PATTERNS_MEDIATOR_H
#include <string>
#include <iostream>
namespace mediator
{
  class BaseComponent;
  class Mediator
  {
  public:
    virtual void Notify(BaseComponent *, std::string) const = 0;
  };

  class BaseComponent
  {
  protected:
    Mediator *mediator_;

  public:
    BaseComponent(Mediator * = nullptr);
    void set_mediator(Mediator *);
  };

  class Component1 : public BaseComponent
  {
  public:
    void DoA();
    void DoB();
  };
  class Component2 : public BaseComponent
  {
  public:
    void DoC();
    void DoD();
  };

  class ConcreteMediator : public Mediator
  {
  private:
    Component1 *component1_;
    Component2 *component2_;

  public:
    ConcreteMediator(Component1 *, Component2 *);
    void Notify(BaseComponent *, std::string) const override;
  };

  void ClientCode();
  void run();
}

#endif //DESIGN_PATTERNS_MEDIATOR_H
