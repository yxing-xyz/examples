/*
是什么:
备忘录模式(快照Snapshot)是一种行为设计模式， 允许在不暴露对象实现细节的情况下保存和恢复对象之前的状态。

为什么:
程序在执行操作前保存所有对象的状态快照， 稍后可通过快照将对象恢复到之前的状态, 比如文本编辑器的回退功能
很可能你会需要遍历对象的所有成员变量并将其数值复制保存。 但只有当对象对其内容没有严格访问权限限制的情况下， 你才能使用该方式。 不过很遗憾， 绝大部分对象会使用私有成员变量来存储重要数据， 这样别人就无法轻易查看其中的内容。


怎么做:
1. 确定担任原发器角色的类。 重要的是明确程序使用的一个原发器中心对象， 还是多个较小的对象。

2. 创建备忘录类。 逐一声明对应每个原发器成员变量的备忘录成员变量。

3. 将备忘录类设为不可变。 备忘录只能通过构造函数一次性接收数据。 该类中不能包含设置器。

4. 如果你所使用的编程语言支持嵌套类， 则可将备忘录嵌套在原发器中； 如果不支持， 那么你可从备忘录类中抽取一个空接口， 然后让其他所有对象通过接口来引用备忘录。 你可在该接口中添加一些元数据操作， 但不能暴露原发器的状态。

5. 在原发器中添加一个创建备忘录的方法。 原发器必须通过备忘录构造函数的一个或多个实际参数来将自身状态传递给备忘录。
该方法返回结果的类型必须是你在上一步中抽取的接口 （如果你已经抽取了）。 实际上， 创建备忘录的方法必须直接与备忘录类进行交互。

6. 在原发器类中添加一个用于恢复自身状态的方法。 该方法接受备忘录对象作为参数。 如果你在之前的步骤中抽取了接口， 那么可将接口作为参数的类型。 在这种情况下， 你需要将输入对象强制转换为备忘录， 因为原发器需要拥有对该对象的完全访问权限。

7. 无论负责人是命令对象、 历史记录或其他完全不同的东西， 它都必须要知道何时向原发器请求新的备忘录、 如何存储备忘录以及何时使用特定备忘录来对原发器进行恢复。

8. 负责人与原发器之间的连接可以移动到备忘录类中。 在本例中， 每个备忘录都必须与创建自己的原发器相连接。 恢复方法也可以移动到备忘录类中， 但只有当备忘录类嵌套在原发器中， 或者原发器类提供了足够多的设置器并可对其状态进行重写时， 这种方式才能实现。
*/

#ifndef DESIGN_PATTERNS_MEMENTO_H
#define DESIGN_PATTERNS_MEMENTO_H

#include <string>
#include <vector>

namespace memento
{
  class Memento
  {
  public:
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
  };
  class ConcreteMemento : public Memento
  {
  private:
    std::string state_;
    std::string date_;

  public:
    ConcreteMemento(std::string);
    std::string GetName() const override;
    std::string date() const override;
    std::string state() const override;
  };

  class Originator
  {
  private:
    std::string state_;
    std::string GenerateRandomString(int = 10);

  public:
    Originator(std::string state);
    void DoSomething();
    Memento *Save();
    void Restore(Memento *);
  };

  class Caretaker
  {
  private:
    std::vector<Memento *> mementos_;
    Originator *originator_;

  public:
    Caretaker(Originator *);
    void Backup();
    void Undo();
    void ShowHistory() const;
  };

  void ClientCode();

  void run();
}
#endif //DESIGN_PATTERNS_MEMENTO_H
