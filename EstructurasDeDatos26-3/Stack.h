#pragma once
#include "TNode.h"
#include "ConsoleUI.h"
#include <iostream>
#include <vector>

// =====================================================================
//  Stack<T>  -  Pila generica (LIFO)
//
//  El tope es la CABEZA de la lista: cada nodo apunta hacia ABAJO.
//  Gracias a eso, Push y Pop son O(1): nunca hay que recorrer nada.
//
//  TODO: implementa todo lo que dice TODO.
// =====================================================================

template <class T>
class Stack
{
private:
    TNode<T>* _top;
    int _size;

    // Privada a proposito: si alguien de afuera pudiera pasar un nodo,
    // no quedaria claro quien es dueño de esa memoria ni quien la libera.
    // Desde afuera solo se puede usar Push(T value).
    void Push(TNode<T>* n);

public:
    Stack();
    Stack(const Stack<T>& otro);              // constructor de copia
    Stack<T>& operator=(const Stack<T>& otro); // operador de asignacion
    ~Stack();

    void Push(T value);
    T Pop();
    T Top();
    bool IsEmpty();
    int GetSize();
    void Clear();
    void Print();
};

template <class T>
Stack<T>::Stack()
{
    _top = nullptr;
    _size = 0;
}

template <class T>
Stack<T>::Stack(const Stack<T>& otro)
{
    _top = nullptr;
    _size = 0;
    // Copia profunda preservando orden
    // Recolectar valores de arriba hacia abajo
    std::vector<T> vals;
    TNode<T>* cur = otro._top;
    while (cur != nullptr)
    {
        vals.push_back(cur->getDato());
        cur = cur->getNext();
    }
    // vals[0] = tope, vals.back() = fondo
    // Push en orden inverso para conservar orden
    for (int i = (int)vals.size() - 1; i >= 0; --i)
    {
        Push(vals[i]);
    }
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& otro)
{
    if (this == &otro)
        return *this;
    Clear();
    std::vector<T> vals;
    TNode<T>* cur = otro._top;
    while (cur != nullptr)
    {
        vals.push_back(cur->getDato());
        cur = cur->getNext();
    }
    for (int i = (int)vals.size() - 1; i >= 0; --i)
    {
        Push(vals[i]);
    }
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    Clear();
}

template <class T>
void Stack<T>::Push(TNode<T>* n)
{
    if (n == nullptr) return;
    n->setNext(_top);
    _top = n;
    _size++;
}

template <class T>
void Stack<T>::Push(T value)
{
    TNode<T>* n = new TNode<T>(value, _size);
    Push(n);
}

template <class T>
T Stack<T>::Pop()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintError("Stack::Pop: pila vacia");
        return T();
    }
    TNode<T>* nodo = _top;
    T dato = nodo->getDato();
    _top = nodo->getNext();
    delete nodo;
    _size--;
    return dato;
}

template <class T>
T Stack<T>::Top()
{
    if (IsEmpty())
    {
        ConsoleUI::PrintError("Stack::Top: pila vacia");
        return T();
    }
    return _top->getDato();
}

template <class T>
bool Stack<T>::IsEmpty()
{
    return _top == nullptr;
}

template <class T>
int Stack<T>::GetSize()
{
    return _size;
}

template <class T>
void Stack<T>::Clear()
{
    while (!IsEmpty())
    {
        TNode<T>* tmp = _top;
        _top = _top->getNext();
        delete tmp;
        _size--;
    }
    _top = nullptr;
    _size = 0;
}

template <class T>
void Stack<T>::Print()
{
    TNode<T>* cur = _top;
    std::cout << "[TOPE] ";
    while (cur != nullptr)
    {
        std::cout << cur->getDato();
        if (cur->getNext() != nullptr) std::cout << " -> ";
        cur = cur->getNext();
    }
    std::cout << " [FONDO]" << std::endl;
}
