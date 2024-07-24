#include "chain_of_responsibility.h"
#include <iostream>
#include <vector>
namespace chain_of_responsibility
{
  AbstractHandler::AbstractHandler() : next_handler_(nullptr)
  {
  }
  Handler *AbstractHandler::SetNext(Handler *handle)
  {
    this->next_handler_ = handle;
    // Returning a handler from here will let us link handlers in a convenient
    // way like this:
    // $monkey->setNext($squirrel)->setNext($dog);
    return handle;
  }

  std::string AbstractHandler::Handle(std::string request)
  {
    if (this->next_handler_)
    {
      return this->next_handler_->Handle(request);
    }

    return {};
  }

  std::string MonkeyHandler::Handle(std::string request)
  {
    if (request == "Banana")
    {
      return "Monkey: I'll eat the " + request + ".\n";
    }
    else
    {
      return AbstractHandler::Handle(request);
    }
  }

  std::string SquirrelHandler::Handle(std::string request)
  {
    if (request == "Nut")
    {
      return "Squirrel: I'll eat the " + request + ".\n";
    }
    else
    {
      return AbstractHandler::Handle(request);
    }
  }
  std::string DogHandler::Handle(std::string request)
  {
    if (request == "MeatBall")
    {
      return "Dog: I'll eat the " + request + ".\n";
    }
    else
    {
      return AbstractHandler::Handle(request);
    }
  }
  void ClientCode(Handler &handler)
  {
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const std::string &f : food)
    {
      std::cout << "Client: Who wants a " << f << "?\n";
      const std::string result = handler.Handle(f);
      if (!result.empty())
      {
        std::cout << "  " << result;
      }
      else
      {
        std::cout << "  " << f << " was left untouched.\n";
      }
    }
  }
  void run()
  {
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    /**
   * The client should be able to send a request to any handler, not just the
   * first one in the chain.
   */
    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;
  }
}
