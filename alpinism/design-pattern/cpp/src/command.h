/*
是什么:
命令模式是一种行为设计模式， 它可将请求转换为一个包含与请求相关的所有信息的独立对象。 该转换让你能根据不同的请求将方法参数化、 延迟请求执行或将其放入队列中， 且能实现可撤销操作。

为什么:
假如你正在开发一款新的文字编辑器， 当前的任务是创建一个包含多个按钮的工具栏， 并让每个按钮对应编辑器的不同操作。 你创建了一个非常简洁的 按钮类， 它不仅可用于生成工具栏上的按钮， 还可用于生成各种对话框的通用按钮。
尽管所有按钮看上去都很相似， 但它们可以完成不同的操作 （打开、 保存、 打印和应用等）。 你会在哪里放置这些按钮的点击处理代码呢？ 最简单的解决方案是在使用按钮的每个地方都创建大量的子类。 这些子类中包含按钮点击后必须执行的代码。
你很快就意识到这种方式有严重缺陷。 首先， 你创建了大量的子类， 当每次修改基类 按钮时， 你都有可能需要修改所有子类的代码。 简单来说， GUI 代码以一种拙劣的方式依赖于业务逻辑中的不稳定代码。
还有一个部分最难办。 复制/粘贴文字等操作可能会在多个地方被调用。 例如用户可以点击工具栏上小小的 “复制” 按钮， 或者通过上下文菜单复制一些内容， 又或者直接使用键盘上的 Ctrl+C 。
我们的程序最初只有工具栏， 因此可以使用按钮子类来实现各种不同操作。 换句话来说， ​ 复制按钮Copy­Button子类包含复制文字的代码是可行的。 在实现了上下文菜单、 快捷方式和其他功能后， 你要么需要将操作代码复制进许多个类中， 要么需要让菜单依赖于按钮， 而后者是更糟糕的选择。

1. 如果你需要通过操作来参数化对象， 可使用命令模式。
命令模式可将特定的方法调用转化为独立对象。 这一改变也带来了许多有趣的应用： 你可以将命令作为方法的参数进行传递、 将命令保存在其他对象中， 或者在运行时切换已连接的命令等。
举个例子： 你正在开发一个 GUI 组件 （例如上下文菜单）， 你希望用户能够配置菜单项， 并在点击菜单项时触发操作。
2. 如果你想要将操作放入队列中、 操作的执行或者远程执行操作， 可使用命令模式。
同其他对象一样， 命令也可以实现序列化 （序列化的意思是转化为字符串）， 从而能方便地写入文件或数据库中。 一段时间后， 该字符串可被恢复成为最初的命令对象。 因此， 你可以延迟或计划命令的执行。 但其功能远不止如此！ 使用同样的方式， 你还可以将命令放入队列、 记录命令或者通过网络发送命令。
3. 如果你想要实现操作回滚功能， 可使用命令模式。
尽管有很多方法可以实现撤销和恢复功能， 但命令模式可能是其中最常用的一种。
为了能够回滚操作， 你需要实现已执行操作的历史记录功能。 命令历史记录是一种包含所有已执行命令对象及其相关程序状态备份的栈结构。
这种方法有两个缺点。 首先， 程序状态的保存功能并不容易实现， 因为部分状态可能是私有的。 你可以使用备忘录模式来在一定程度上解决这个问题。
其次， 备份状态可能会占用大量内存。 因此， 有时你需要借助另一种实现方式： 命令无需恢复原始状态， 而是执行反向操作。 反向操作也有代价： 它可能会很难甚至是无法实现。(emacs的撤销就是执行反向操作)

怎么做:
1. 声明仅有一个执行方法的命令接口。
2. 抽取请求并使之成为实现命令接口的具体命令类。 每个类都必须有一组成员变量来保存请求参数和对于实际接收者对象的引用。 所有这些变量的数值都必须通过命令构造函数进行初始化。
3. 找到担任发送者职责的类。 在这些类中添加保存命令的成员变量。 发送者只能通过命令接口与其命令进行交互。 发送者自身通常并不创建命令对象， 而是通过客户端代码获取。
4. 修改发送者使其执行命令， 而非直接将请求发送给接收者。
5. 客户端必须按照以下顺序来初始化对象：
创建接收者。
创建命令， 如有需要可将其关联至接收者。
创建发送者并将其与特定命令关联。

*/

#ifndef DESIGN_PATTERNS_COMMAND_H
#define DESIGN_PATTERNS_COMMAND_H
#include <string>
namespace command
{
  class Command
  {
  public:
    virtual ~Command();
    virtual void Execute() const = 0;
  };

  class SimpleCommand : public Command
  {
  private:
    std::string pay_load_;

  public:
    explicit SimpleCommand(std::string);
    void Execute() const override;
  };

  class Receiver
  {
  public:
    void DoSomething(const std::string &);
    void DoSomethingElse(const std::string &);
  };

  class ComplexCommand : public Command
  {
  private:
    Receiver *receiver_;
    /**
   * Context data, required for launching the receiver's methods.
   */
    std::string a_;
    std::string b_;

  public:
    ComplexCommand(Receiver *, std::string, std::string);
    void Execute() const override;
  };

  class Invoker
  {
  private:
    Command *on_start_;
    Command *on_finish_;

  public:
    ~Invoker();
    void SetOnStart(Command *);
    void SetOnFinish(Command *);
    void DoSomethingImportant();
  };

  void run();
}

#endif //DESIGN_PATTERNS_COMMAND_H
