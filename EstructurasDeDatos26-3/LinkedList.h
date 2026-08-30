#pragma once
#include <iostream>
#include "ConsoleUI.h"

// =====================================================================
//  LinkedList<T>  -  Lista ligada simple, ahora generica
//
//  Es la misma lista que ya programaste, pero con templates: en lugar
//  de servir solo para int, ahora sirve para cualquier tipo.
//
//  NUEVO EN ESTA VERSION:
//    - operator[] que regresa REFERENCIA (T&), para poder escribir:
//         lista[0] = 99;
//    - versiones RECURSIVAS de operaciones que ya tenias iterativas
//    - PrintReverse, que imprime la lista al reves
// =====================================================================

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        int id;
    };

    Node* _first;
    int _size;
    T _basura;   // valor de respaldo para operator[] fuera de rango

    // Privada: desde afuera solo se puede usar Add(T dato).
    void Add(Node* n);

    // Auxiliares recursivas. Reciben el nodo actual porque la
    // recursion necesita "avanzar", y desde afuera nadie ve los nodos.
    T GetAtRec(Node* actual, int index);
    int CountRec(Node* actual);
    int BuscarRec(Node* actual, T valor, int indiceActual);
    void PrintReverseRec(Node* actual);

public:
    LinkedList();
    ~LinkedList();

    void Add(T dato);
    T GetAt(int index);
    T& operator[](int index);
    int GetSize();
    void Print();

    void PrintReverse();
    T GetAtRecursivo(int index);
    int CountRecursivo();
    int BuscarRecursivo(T valor);

    void SelectionSort();
    void InsertionSort();
};

template <class T>
LinkedList<T>::LinkedList()
{
    _first = nullptr;
    _size = 0;
    _basura = T();
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node* cur = _first;
    while (cur != nullptr)
    {
        Node* tmp = cur;
        cur = cur->next;
        delete tmp;
    }
    _first = nullptr;
    _size = 0;
}

template <class T>
void LinkedList<T>::Add(Node* n)
{
    if (n == nullptr) return;
    n->next = nullptr;
    if (_first == nullptr)
    {
        _first = n;
    }
    else
    {
        Node* cur = _first;
        while (cur->next != nullptr)
            cur = cur->next;
        cur->next = n;
    }
    _size++;
}

template <class T>
void LinkedList<T>::Add(T dato)
{
    Node* n = new Node();
    n->data = dato;
    n->next = nullptr;
    n->id = _size;
    Add(n);
}

template <class T>
T LinkedList<T>::GetAt(int index)
{
    if (index < 0 || index >= _size)
    {
        ConsoleUI::PrintError("LinkedList::GetAt: indice fuera de rango");
        return T();
    }
    Node* cur = _first;
    for (int i = 0; i < index; ++i)
        cur = cur->next;
    return cur->data;
}

template <class T>
T& LinkedList<T>::operator[](int index)
{
    if (index < 0 || index >= _size)
    {
        ConsoleUI::PrintError("LinkedList::operator[]: indice fuera de rango");
        return _basura;
    }
    Node* cur = _first;
    for (int i = 0; i < index; ++i)
        cur = cur->next;
    return cur->data;
}

template <class T>
int LinkedList<T>::GetSize()
{
    return _size;
}

template <class T>
void LinkedList<T>::Print()
{
    Node* cur = _first;
    std::cout << "[ ";
    while (cur != nullptr)
    {
        std::cout << cur->data;
        if (cur->next != nullptr) std::cout << " -> ";
        cur = cur->next;
    }
    std::cout << " ]" << std::endl;
}

template <class T>
void LinkedList<T>::PrintReverse()
{
    PrintReverseRec(_first);
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::PrintReverseRec(Node* actual)
{
    if (actual == nullptr) return;
    PrintReverseRec(actual->next);
    std::cout << actual->data << " ";
}

template <class T>
T LinkedList<T>::GetAtRecursivo(int index)
{
    if (index < 0 || index >= _size)
    {
        ConsoleUI::PrintError("LinkedList::GetAtRecursivo: indice fuera de rango");
        return T();
    }
    return GetAtRec(_first, index);
}

template <class T>
T LinkedList<T>::GetAtRec(Node* actual, int index)
{
    if (actual == nullptr)
    {
        ConsoleUI::PrintError("LinkedList::GetAtRec: nodo nulo");
        return T();
    }
    if (index == 0) return actual->data;
    return GetAtRec(actual->next, index - 1);
}

template <class T>
int LinkedList<T>::CountRecursivo()
{
    return CountRec(_first);
}

template <class T>
int LinkedList<T>::CountRec(Node* actual)
{
    if (actual == nullptr) return 0;
    return 1 + CountRec(actual->next);
}

template <class T>
int LinkedList<T>::BuscarRecursivo(T valor)
{
    return BuscarRec(_first, valor, 0);
}

template <class T>
int LinkedList<T>::BuscarRec(Node* actual, T valor, int indiceActual)
{
    if (actual == nullptr) return -1;
    if (actual->data == valor) return indiceActual;
    return BuscarRec(actual->next, valor, indiceActual + 1);
}

template <class T>
void LinkedList<T>::SelectionSort()
{
    for (Node* i = _first; i != nullptr; i = i->next)
    {
        Node* min = i;
        for (Node* j = i->next; j != nullptr; j = j->next)
        {
            if (j->data < min->data)
                min = j;
        }
        if (min != i)
        {
            T tmp = i->data;
            i->data = min->data;
            min->data = tmp;
        }
    }
}

template <class T>
void LinkedList<T>::InsertionSort()
{
    if (_first == nullptr || _first->next == nullptr) return;

    // Insertion sort por datos: tratamos la lista como arreglo logico
    // Usamos helper para obtener nodo por indice
    auto getNodeAt = [&](int idx) -> Node* {
        Node* cur = _first;
        for (int i = 0; i < idx && cur != nullptr; ++i)
            cur = cur->next;
        return cur;
    };

    for (int i = 1; i < _size; ++i)
    {
        Node* currNode = getNodeAt(i);
        T key = currNode->data;
        int j = i - 1;
        while (j >= 0 && getNodeAt(j)->data > key)
        {
            getNodeAt(j + 1)->data = getNodeAt(j)->data;
            j--;
        }
        getNodeAt(j + 1)->data = key;
    }
}
