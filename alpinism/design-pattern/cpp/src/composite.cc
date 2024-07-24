//
// Created by Jennica on 2016/12/30.
//

#include "composite.h"
#include <iostream>
#include <list>

namespace composite
{
    Component::~Component() {}
    void Component::SetParent(Component *component)
    {
        this->parent_ = component;
    }
    void Component::Add(Component *component) {}
    void Component::Remove(Component *component) {}
    bool Component::IsComposite() const
    {
        return false;
    }

    std::string Leaf::Operation() const
    {
        return "Leaf";
    }
    void Composite::Add(Component *component)
    {
        this->children_.push_back(component);
        component->SetParent(this);
    }
    void Composite::Remove(Component *component)
    {
        this->children_.remove(component);
        component->SetParent(nullptr);
    }

    std::string Composite::Operation() const
    {
        std::string result;
        for (const Component *c : children_)
        {
            if (c == children_.back())
            {
                result += c->Operation();
            }
            else
            {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }

    void ClientCode(const Component *component)
    {
        std::cout << "RESULT: " << component->Operation();
    }
    void ClientCode2(Component *component1, Component *component2)
    {
        // ...
        if (component1->IsComposite())
        {
            component1->Add(component2);
        }
        std::cout << "RESULT: " << component1->Operation();
        // ...
    }
    void run()
    {
        Component *simple = new Leaf;
        std::cout << "Client: I've got a simple component:\n";
        ClientCode(simple);
        std::cout << "\n\n";
        /**
         * ...as well as the complex composites.
         */

        Component *tree = new Composite;
        Component *branch1 = new Composite;

        Component *leaf_1 = new Leaf;

        Component *leaf_2 = new Leaf;
        Component *leaf_3 = new Leaf;
        branch1->Add(leaf_1);
        branch1->Add(leaf_2);
        Component *branch2 = new Composite;
        branch2->Add(leaf_3);
        tree->Add(branch1);
        tree->Add(branch2);
        std::cout << "Client: Now I've got a composite tree:\n";
        ClientCode(tree);
        std::cout << "\n\n";

        std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
        ClientCode2(tree, simple);
        std::cout << "\n";

        delete simple;
        delete tree;
        delete branch1;
        delete branch2;
        delete leaf_1;
        delete leaf_2;
        delete leaf_3;
    }
}
