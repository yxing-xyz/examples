//
// Created by Jennica on 2016/12/29.
//

#include "proxy.h"
#include <iostream>

namespace proxy
{
  void RealSubject::Request() const
  {
    std::cout << "RealSubject: Handling request.\n";
  }
  bool Proxy::CheckAccess() const
  {
    // Some real checks should go here.
    std::cout << "Proxy: Checking access prior to firing a real request.\n";
    return true;
  }

  void Proxy::LogAccess() const
  {
    std::cout << "Proxy: Logging the time of request.\n";
  }

  Proxy::Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject))
  {
  }
  Proxy::~Proxy() {
    delete this->real_subject_;
  }
  void Proxy::Request() const
  {
    if (this->CheckAccess())
    {
      this->real_subject_->Request();
      this->LogAccess();
    }
  }

  void ClientCode(const Subject &subject)
  {
    // ...
    subject.Request();
    // ...
  }

  void run()
  {
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject *real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy *proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
  }
}