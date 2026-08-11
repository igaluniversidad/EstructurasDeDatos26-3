#pragma once

template <class T>
class TNode
{
private:
    T _dato;
    TNode* _next;
    int _id;
    
public:
    void setDato(T d);
    T getDato();

    void setId(int id);
    int getId();

    void setNext(TNode* n);
    TNode* getNext();

    TNode();
    TNode(T dato, int id);
    TNode(T dato, TNode* nodo, int id);
};

template <class T>
void TNode<T>::setDato(T d)
{
    _dato = d;
}

template <class T>
T TNode<T>::getDato()
{
    return _dato;
}

template <class T>
void TNode<T>::setId(int id)
{
    _id = id;
}

template <class T>
int TNode<T>::getId()
{
    return _id;
}

template <class T>
void TNode<T>::setNext(TNode* n)
{
    _next = n;
}

template <class T>
TNode<T>* TNode<T>::getNext()
{
    return _next;
}

template <class T>
TNode<T>::TNode()
{
    _dato = nullptr;
    _next = nullptr;
    _id = 0;
}

template <class T>
TNode<T>::TNode(T dato, TNode* nodo, int id)
{
    _dato = dato;
    _next = nodo;
    _id = id;
}

template <class T>
TNode<T>::TNode(T dato, int id)
{
    _dato = dato;
    _id = id;
    _next = nullptr;
}