#pragma once
#include <iostream>

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
    // TODO: liberar todos los nodos
}

template <class T>
void LinkedList<T>::Add(Node* n)
{
    // TODO: enganchar 'n' al final de la lista
}

template <class T>
void LinkedList<T>::Add(T dato)
{
    // TODO: crear el nodo aqui adentro y mandarlo al Add privado
}

template <class T>
T LinkedList<T>::GetAt(int index)
{
    // TODO: validar el rango y recorrer hasta la posicion
    return T();
}

template <class T>
T& LinkedList<T>::operator[](int index)
{
    // TODO: igual que GetAt, pero regresando una REFERENCIA al dato
    // para que se pueda escribir: lista[0] = 99;
    //
    // PIENSALO: al regresar una referencia ya no puedes regresar -1
    // como codigo de error. Que haces si el indice no existe?
    return _basura;
}

template <class T>
int LinkedList<T>::GetSize()
{
    // TODO
    return 0;
}

template <class T>
void LinkedList<T>::Print()
{
    // TODO
}

template <class T>
void LinkedList<T>::PrintReverse()
{
    // TODO: arrancar la recursion desde _first
}

template <class T>
void LinkedList<T>::PrintReverseRec(Node* actual)
{
    // TODO: primero recurre hasta el final, y APENAS AL REGRESAR imprime.
    // Ese cambio de orden es todo el truco.
    //
    // Funciona porque la pila de llamadas esta guardando los nodos por
    // ti. O sea: ya estabas usando un Stack sin darte cuenta.
}

template <class T>
T LinkedList<T>::GetAtRecursivo(int index)
{
    // TODO
    return T();
}

template <class T>
T LinkedList<T>::GetAtRec(Node* actual, int index)
{
    // TODO
    return T();
}

template <class T>
int LinkedList<T>::CountRecursivo()
{
    // TODO
    return 0;
}

template <class T>
int LinkedList<T>::CountRec(Node* actual)
{
    // TODO: caso base cuando actual es nullptr
    return 0;
}

template <class T>
int LinkedList<T>::BuscarRecursivo(T valor)
{
    // TODO: regresa el indice donde esta el valor, o -1 si no existe
    return -1;
}

template <class T>
int LinkedList<T>::BuscarRec(Node* actual, T valor, int indiceActual)
{
    // TODO
    return -1;
}

template <class T>
void LinkedList<T>::SelectionSort()
{
    // TODO: ordenar INTERCAMBIANDO los datos entre nodos,
    //       no reconectando los punteros
}

template <class T>
void LinkedList<T>::InsertionSort()
{
    // TODO: ordenar INTERCAMBIANDO los datos entre nodos
}
