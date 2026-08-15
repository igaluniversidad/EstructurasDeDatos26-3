#pragma once
#include "Nodo.h"
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    void Add(int dato);
    int GetAt(int index);
    int GetSize();
    void Print();
    void SelectionSort();
    void InsertionSort();

private:
    Nodo* _first;
    Nodo* _last;  
    int _size;    
};