#include "strategy.h"
#include <iostream>
#include <bits/stl_algo.h>

namespace strategy
{
  Strategy::~Strategy()
  {
  }

  Context::Context(Strategy *strategy) : strategy_(strategy)
  {
  }
  Context::~Context()
  {
    delete this->strategy_;
  }
  void Context::set_strategy(Strategy *strategy)
  {
    // 重复释放nullptr没问题
    delete this->strategy_;
    this->strategy_ = strategy;
  }
  void Context::DoSomeBusinessLogic() const
  {
    std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
    std::string result = this->strategy_->DoAlgorithm(std::vector<std::string>{"a", "e", "c", "b", "d"});
    std::cout << result << "\n";
  }

  std::string ConcreteStrategyA::DoAlgorithm(const std::vector<std::string> &data) const
  {
    std::string result;
    std::for_each(std::begin(data), std::end(data), [&result](const std::string &letter)
                  { result += letter; });
    std::sort(std::begin(result), std::end(result));
    return result;
  }

  std::string ConcreteStrategyB::DoAlgorithm(const std::vector<std::string> &data) const
  {
    std::string result;
    std::for_each(std::begin(data), std::end(data), [&result](const std::string &letter)
                  { result += letter; });
    std::sort(std::begin(result), std::end(result));
    for (int i = 0; i < result.size() / 2; i++)
    {
      std::swap(result[i], result[result.size() - i - 1]);
    }

    return result;
  }
  void ClientCode()
  {
    Context *context = new Context(new ConcreteStrategyA);
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context->DoSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context->set_strategy(new ConcreteStrategyB);
    context->DoSomeBusinessLogic();
    delete context;
  }
  void run()
  {
    ClientCode();
  }

};