#include "iterator.h"
#include <iostream>
namespace iterator
{
    template <typename T, typename U>
    void Iterator<T, U>::First()
    {
        m_it_ = m_p_data_->m_data_.begin();
    }

    template <typename T, typename U>
    void Iterator<T, U>::Next()
    {
        m_it_++;
    }

    template <typename T, typename U>
    bool Iterator<T, U>::IsDone()
    {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    Data::Data(int a) : m_data_(a)
    {
    }

    void Data::set_data(int a)
    {
        m_data_ = a;
    }

    int Data::data()
    {
        return m_data_;
    }
    void ClientCode()
    {
        std::cout << "________________Iterator with int______________________________________" << std::endl;
        Container<int> cont;

        for (int i = 0; i < 10; i++)
        {
            cont.Add(i);
        }

        Iterator<int, Container<int>> *it = cont.CreateIterator();
        for (it->First(); !it->IsDone(); it->Next())
        {
            std::cout << *it->Current() << std::endl;
        }

        Container<Data> cont2;
        Data a(100), b(1000), c(10000);
        cont2.Add(a);
        cont2.Add(b);
        cont2.Add(c);

        std::cout << "________________Iterator with custom Class______________________________" << std::endl;
        Iterator<Data, Container<Data>> *it2 = cont2.CreateIterator();
        for (it2->First(); !it2->IsDone(); it2->Next())
        {
            std::cout << it2->Current()->data() << std::endl;
        }
        delete it;
        delete it2;
    }

    void run()
    {
        ClientCode();
    }
}