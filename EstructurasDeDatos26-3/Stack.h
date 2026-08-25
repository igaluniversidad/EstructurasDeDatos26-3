#pragma once
#include "TNode.h"

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
    // TODO: copia PROFUNDA. Hay que crear nodos NUEVOS con los mismos
    // valores y en el mismo orden, no apuntar a los nodos de 'otro'.
    _top = nullptr;
    _size = 0;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& otro)
{
    // TODO: 1) cuidado con la autoasignacion (a = a)
    //       2) libera lo que ya tenias
    //       3) copia profunda de 'otro'
    return *this;
}

template <class T>
Stack<T>::~Stack()
{
    // TODO: liberar todos los nodos
}

template <class T>
void Stack<T>::Push(TNode<T>* n)
{
    // TODO: colocar 'n' como nuevo tope
}

template <class T>
void Stack<T>::Push(T value)
{
    // TODO: crear el nodo aqui adentro y mandarlo al Push privado
}

template <class T>
T Stack<T>::Pop()
{
    // TODO: quitar el tope, regresar su dato y LIBERAR el nodo
    return T();
}

template <class T>
T Stack<T>::Top()
{
    // TODO: regresar el dato del tope SIN quitarlo
    return T();
}

template <class T>
bool Stack<T>::IsEmpty()
{
    // TODO
    return true;
}

template <class T>
int Stack<T>::GetSize()
{
    // TODO
    return 0;
}

template <class T>
void Stack<T>::Clear()
{
    // TODO: vaciar la pila liberando todos los nodos
}

template <class T>
void Stack<T>::Print()
{
    // TODO: imprimir del tope hacia abajo
}
