/*
是什么:
  责任链模式是一种行为设计模式， 允许你将请求沿着处理者链进行发送。 收到请求后， 每个处理者均可对请求进行处理， 或将其传递给链上的下个处理者。

为什么:
假如你正在开发一个在线订购系统。 你希望对系统访问进行限制， 只允许认证用户创建订单。 此外， 拥有管理权限的用户也拥有所有订单的完全访问权限。
简单规划后， 你会意识到这些检查必须依次进行。 只要接收到包含用户凭据的请求， 应用程序就可尝试对进入系统的用户进行认证。 但如果由于用户凭据不正确而导致认证失败， 那就没有必要进行后续检查了。
在接下来的几个月里， 你实现了后续的几个检查步骤。
一位同事认为直接将原始数据传递给订购系统存在安全隐患。 因此你新增了额外的验证步骤来清理请求中的数据。
过了一段时间， 有人注意到系统无法抵御暴力密码破解方式的攻击。 为了防范这种情况， 你立刻添加了一个检查步骤来过滤来自同一 IP 地址的重复错误请求。
又有人提议你可以对包含同样数据的重复请求返回缓存中的结果， 从而提高系统响应速度。 因此， 你新增了一个检查步骤， 确保只有没有满足条件的缓存结果时请求才能通过并被发送给系统。
检查代码本来就已经混乱不堪， 而每次新增功能都会使其更加臃肿。 修改某个检查步骤有时会影响其他的检查步骤。 最糟糕的是， 当你希望复用这些检查步骤来保护其他系统组件时， 你只能复制部分代码， 因为这些组件只需部分而非全部的检查步骤。
系统会变得让人非常费解， 而且其维护成本也会激增。 你在艰难地和这些代码共处一段时间后， 有一天终于决定对整个系统进行重构。

怎么做:
1. 声明处理者接口并描述请求处理方法的签名。
确定客户端如何将请求数据传递给方法。 最灵活的方式是将请求转换为对象， 然后将其以参数的形式传递给处理函数。
2. 为了在具体处理者中消除重复的样本代码， 你可以根据处理者接口创建抽象处理者基类。
该类需要有一个成员变量来存储指向链上下个处理者的引用。 你可以将其设置为不可变类。 但如果你打算在运行时对链进行改变， 则需要定义一个设定方法来修改引用成员变量的值。
为了使用方便， 你还可以实现处理方法的默认行为。 如果还有剩余对象， 该方法会将请求传递给下个对象。 具体处理者还能够通过调用父对象的方法来使用这一行为。
3. 依次创建具体处理者子类并实现其处理方法。 每个处理者在接收到请求后都必须做出两个决定：
依次创建具体处理者子类并实现其处理方法。 每个处理者在接收到请求后都必须做出两个决定：
是否将该请求沿着链进行传递。
4. 客户端可以自行组装链， 或者从其他对象处获得预先组装好的链。 在后一种情况下， 你必须实现工厂类以根据配置或环境设置来创建链。
5. 客户端可以触发链中的任意处理者， 而不仅仅是第一个。 请求将通过链进行传递， 直至某个处理者拒绝继续传递， 或者请求到达链尾。
6. 由于链的动态性， 客户端需要准备好处理以下情况：
链中可能只有单个链接。
部分请求可能无法到达链尾。
其他请求可能直到链尾都未被处理。

心得:
其实也可以不通过关联下一个handler, 通过使用链表串联, 客户端代码通过遍历链表来调用过滤链.
*/
#ifndef DESIGN_PATTERNS_CHAIN_OF_RESPONSIBILITY_H
#define DESIGN_PATTERNS_CHAIN_OF_RESPONSIBILITY_H
#include <string>

namespace chain_of_responsibility
{
  class Handler
  {
  public:
    virtual Handler *SetNext(Handler *) = 0;
    virtual std::string Handle(std::string) = 0;
  };
  class AbstractHandler : public Handler
  {
  private:
    Handler *next_handler_;

  public:
    AbstractHandler();
    Handler *SetNext(Handler *) override;
    std::string Handle(std::string) override;
  };

  class MonkeyHandler : public AbstractHandler
  {
  public:
    std::string Handle(std::string) override;
  };

  class SquirrelHandler : public AbstractHandler
  {
  public:
    std::string Handle(std::string) override;
  };

  class DogHandler : public AbstractHandler
  {
  public:
    std::string Handle(std::string) override;
  };

  void ClientCode(Handler &);
  void run();
};

#endif //DESIGN_PATTERNS_CHAIN_OF_RESPONSIBILITY_H
