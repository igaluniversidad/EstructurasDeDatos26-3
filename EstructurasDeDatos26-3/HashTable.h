#pragma once
#include <string>
#include <iostream>
#include "ConsoleUI.h"

// =====================================================================
//  HashTable<V>  -  Tabla asociativa (llave string, valor generico)
//
//  Las llaves SIEMPRE son std::string. El valor es lo que sea (V).
//
//  COMO FUNCIONA:
//  Una tabla hash convierte la llave en un NUMERO (el hash), y usa ese
//  numero como indice del arreglo de buckets. Por eso buscar es O(1)
//  en promedio: no recorre nada, calcula directo donde deberia estar.
//
//  COLISIONES: dos llaves distintas pueden dar el mismo hash. Cuando
//  pasa, ambas tienen que caber en el mismo bucket. La solucion que
//  vas a implementar se llama ENCADENAMIENTO: cada bucket no guarda
//  una entrada, guarda una lista ligada de entradas.
// =====================================================================

template <class V>
class HashTable
{
private:
    struct Entry
    {
        std::string key;
        V value;
        Entry* next;
    };

    Entry** _buckets;
    int _capacidad;
    int _size;

public:
    HashTable(int capacidad);
    ~HashTable();

    int Hash(std::string key);
    void Insert(std::string key, V value);
    V Get(std::string key);
    bool Contains(std::string key);
    bool Remove(std::string key);
    int GetSize();
    int GetCapacidad();
    void Print();
};

template <class V>
HashTable<V>::HashTable(int capacidad)
{
    // Arrancan en nullptr para que nada truene antes de reservar.
    // NO borres estas lineas.
    _buckets = nullptr;
    _capacidad = capacidad;
    _size = 0;

    if (_capacidad > 0)
    {
        _buckets = new Entry*[_capacidad];
        for (int bucketIndex = 0; bucketIndex < _capacidad; bucketIndex++)
        {
            _buckets[bucketIndex] = nullptr;
        }
    }
}

template <class V>
HashTable<V>::~HashTable()
{
    if (_buckets != nullptr)
    {
        for (int bucketIndex = 0; bucketIndex < _capacidad; bucketIndex++)
        {
            Entry* currentEntry = _buckets[bucketIndex];
            while (currentEntry != nullptr)
            {
                Entry* entryToDelete = currentEntry;
                currentEntry = currentEntry->next;
                delete entryToDelete;
            }
        }
        delete[] _buckets;
        _buckets = nullptr;
    }
    _capacidad = 0;
    _size = 0;
}

template <class V>
int HashTable<V>::Hash(std::string key)
{
    if (_capacidad <= 0) return 0;

    // Algoritmo djb2 para cadenas:
    // Multiplica por 33 y suma el caracter.
    // Preserva el orden de los caracteres (distingue "abc" y "cba").
    unsigned long hash = 5381;
    for (char currentCharacter : key)
    {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(currentCharacter);
    }

    return static_cast<int>(hash % static_cast<unsigned long>(_capacidad));
}

template <class V>
void HashTable<V>::Insert(std::string key, V value)
{
    if (_capacidad <= 0 || _buckets == nullptr) return;

    int index = Hash(key);
    Entry* currentEntry = _buckets[index];

    // Buscar si la llave ya existe
    while (currentEntry != nullptr)
    {
        if (currentEntry->key == key)
        {
            currentEntry->value = value;
            return;
        }
        currentEntry = currentEntry->next;
    }

    // Si no existe, crear la nueva entrada y agregarla al inicio del bucket
    Entry* newEntry = new Entry();
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = _buckets[index];
    _buckets[index] = newEntry;
    _size++;
}

template <class V>
V HashTable<V>::Get(std::string key)
{
    if (_capacidad <= 0 || _buckets == nullptr)
    {
        ConsoleUI::PrintError("HashTable::Get: tabla vacia o invalida");
        return V();
    }

    int index = Hash(key);
    Entry* currentEntry = _buckets[index];

    while (currentEntry != nullptr)
    {
        if (currentEntry->key == key)
        {
            return currentEntry->value;
        }
        currentEntry = currentEntry->next;
    }

    ConsoleUI::PrintError("HashTable::Get: llave no encontrada");
    return V();
}

template <class V>
bool HashTable<V>::Contains(std::string key)
{
    if (_capacidad <= 0 || _buckets == nullptr) return false;

    int index = Hash(key);
    Entry* currentEntry = _buckets[index];

    while (currentEntry != nullptr)
    {
        if (currentEntry->key == key)
        {
            return true;
        }
        currentEntry = currentEntry->next;
    }

    return false;
}

template <class V>
bool HashTable<V>::Remove(std::string key)
{
    if (_capacidad <= 0 || _buckets == nullptr) return false;

    int index = Hash(key);
    Entry* currentEntry = _buckets[index];
    Entry* previousEntry = nullptr;

    while (currentEntry != nullptr)
    {
        if (currentEntry->key == key)
        {
            if (previousEntry == nullptr)
            {
                _buckets[index] = currentEntry->next;
            }
            else
            {
                previousEntry->next = currentEntry->next;
            }
            delete currentEntry;
            _size--;
            return true;
        }
        previousEntry = currentEntry;
        currentEntry = currentEntry->next;
    }

    return false;
}

template <class V>
int HashTable<V>::GetSize()
{
    return _size;
}

template <class V>
int HashTable<V>::GetCapacidad()
{
    return _capacidad;
}

template <class V>
void HashTable<V>::Print()
{
    if (_buckets == nullptr) return;

    for (int bucketIndex = 0; bucketIndex < _capacidad; bucketIndex++)
    {
        std::cout << "Bucket " << bucketIndex << ": ";
        Entry* currentEntry = _buckets[bucketIndex];
        if (currentEntry == nullptr)
        {
            std::cout << "(vacio)";
        }
        while (currentEntry != nullptr)
        {
            std::cout << "[" << currentEntry->key << ": " << currentEntry->value << "]";
            if (currentEntry->next != nullptr)
            {
                std::cout << " -> ";
            }
            currentEntry = currentEntry->next;
        }
        std::cout << std::endl;
    }
}
