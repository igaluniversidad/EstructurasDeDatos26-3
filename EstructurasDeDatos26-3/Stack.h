#pragma once
#include "TNode.h"

template <class T>
class Stack
{
private:
    
    int _size;
    TNode<T>* _bottom;
    TNode<T>* _top;
    
public:
    Stack();
    void Push(TNode<T>* n);
    void Push(T value);
    T Pop();
    ~Stack();
};

template <class T>
Stack<T>::Stack()
{
    _size = 0;
    _bottom = nullptr;
    _top = nullptr;
}

template <class T>
void Stack<T>::Push(TNode<T>* n)
{
    //Stack ya trae algo
    if (_bottom != nullptr)
    {
        TNode<T>* temp = _bottom;
        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
        }
        temp->setNext(n);
        (temp->getNext())->setId(temp->getId() + 1); //Tnode del next ponle el id de el actual +1 
        _size++;
    }
    else //Stack Vacío
    {
        _bottom = n;
        _size = 1;
        n->setId(0);
    }
    
}

template <class T>
void Stack<T>::Push(T value)
{
    //Stack ya trae algo
    if (_bottom != nullptr)
    {
        TNode<T>* Nodo = new TNode<T>(value, 0);
        TNode<T>* temp = _bottom;
        while (temp->getNext() != nullptr)
        {
            temp = temp->getNext();
        }
        temp->setNext(Nodo);
        (temp->getNext())->setId(temp->getId() + 1); //Tnode del next ponle el id de el actual +1 
        _size++;
    }
    else //Stack Vacío
    {
        TNode<T>* Nodo = new TNode<T>(value,0);
        _bottom = Nodo;
        _size = 1;
        Nodo->setId(0);
    }

}

template <class T>
T Stack<T>::Pop()
{
    
}

template <class T>
Stack<T>::~Stack()
{
    
}