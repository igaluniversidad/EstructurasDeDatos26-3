#pragma once
#include "TNode.h"

// =====================================================================
//  LinkedQueue<T>  -  Cola generica (FIFO) sobre nodos enlazados
//
//  Se opera por los DOS extremos: se encola por atras (_last) y se
//  desencola por adelante (_first). Por eso necesita los dos punteros:
//  sin _last, cada Enqueue tendria que recorrer toda la cola.
//
//  CUIDADO con el bug clasico: cuando sacas el ULTIMO elemento,
//  _first queda en nullptr pero _last se queda apuntando a un nodo
//  que ya liberaste. El siguiente Enqueue escribe sobre memoria muerta.
// =====================================================================

template <class T>
class LinkedQueue
{
private:
    TNode<T>* _first;
    TNode<T>* _last;
    int _size;

public:
    LinkedQueue();
    ~LinkedQueue();

    void Enqueue(T value);
    T Dequeue();
    T Front();
    bool IsEmpty();
    int GetSize();
    void Clear();
    void Print();
};

template <class T>
LinkedQueue<T>::LinkedQueue()
{
    _first = nullptr;
    _last = nullptr;
    _size = 0;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
    // TODO: liberar todos los nodos
}

template <class T>
void LinkedQueue<T>::Enqueue(T value)
{
    // TODO: agregar al final. Ojo con el caso de la cola vacia.
}

template <class T>
T LinkedQueue<T>::Dequeue()
{
    // TODO: quitar el del frente, regresar su dato y LIBERAR el nodo.
    //       Si la cola queda vacia, no olvides dejar _last en nullptr.
    return T();
}

template <class T>
T LinkedQueue<T>::Front()
{
    // TODO: regresar el dato del frente SIN quitarlo
    return T();
}

template <class T>
bool LinkedQueue<T>::IsEmpty()
{
    // TODO
    return true;
}

template <class T>
int LinkedQueue<T>::GetSize()
{
    // TODO
    return 0;
}

template <class T>
void LinkedQueue<T>::Clear()
{
    // TODO
}

template <class T>
void LinkedQueue<T>::Print()
{
    // TODO: imprimir del frente hacia atras
}
