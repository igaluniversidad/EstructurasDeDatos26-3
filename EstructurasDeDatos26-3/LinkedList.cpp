#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
    _first = nullptr;
    _last = nullptr;
    _size = 0;
}

LinkedList::~LinkedList()
{
    Nodo* current = _first;

    while (current != nullptr)
    {
        Nodo* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }

    _first = nullptr;
    _last = nullptr;
    _size = 0;
}

void LinkedList::Add(int dato)
{
    Nodo* newNode = new Nodo(dato, nullptr, _size);

    if (_first == nullptr)
    {
        _first = newNode;
        _last = newNode;
    }
    else
    {
        _last->setNext(newNode);
        _last = newNode;
    }
    _size++;
}

int LinkedList::GetAt(int index)
{
    if (index < 0 || index >= _size || _first == nullptr)
    {
        std::cout << "Error: Indice no encontrado o fuera de rango." << std::endl;
        return -1;
    }

    Nodo* current = _first;
    for (int i = 0; i < index; i++)
    {
        current = current->getNext();
    }

    return current->GetDato();
}

int LinkedList::GetSize()
{
    return _size;
}

void LinkedList::Print()
{
    Nodo* current = _first;
    while (current != nullptr)
    {
        std::cout << "ID: " << current->GetId() << " | Dato: " << current->GetDato() << std::endl;
        current = current->getNext();
    }
}

void LinkedList::SelectionSort()
{
    if (_first == nullptr || _first->getNext() == nullptr)
        return;

    for (Nodo* i = _first; i != nullptr; i = i->getNext())
    {
        Nodo* minNode = i;

        for (Nodo* j = i->getNext(); j != nullptr; j = j->getNext())
        {
            if (j->GetDato() < minNode->GetDato())
            {
                minNode = j;
            }
        }

        if (minNode != i)
        {
            int temp = i->GetDato();
            i->setDato(minNode->GetDato());
            minNode->setDato(temp);
        }
    }
}

void LinkedList::InsertionSort()
{
    if (_first == nullptr || _first->getNext() == nullptr)
        return;

    Nodo* i = _first->getNext();

    while (i != nullptr)
    {
        int key = i->GetDato();
        Nodo* j = _first;

        while (j != i && j->GetDato() <= key)
        {
            j = j->getNext();
        }

        if (j != i)
        {
            int valAInsertar = key;
            Nodo* k = j;

            while (k != i->getNext())
            {
                int temp = k->GetDato();
                k->setDato(valAInsertar);
                valAInsertar = temp;
                k = k->getNext();
            }
        }
        i = i->getNext();
    }
}