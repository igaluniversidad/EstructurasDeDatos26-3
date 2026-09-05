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

    // TODO: reservar el arreglo de buckets y dejar CADA UNO en nullptr.
    // Un bucket en nullptr significa "esta vacio".
}

template <class V>
HashTable<V>::~HashTable()
{
    // TODO: por cada bucket, recorrer su cadena liberando cada Entry.
    //       Al final, liberar el arreglo de buckets.
}

template <class V>
int HashTable<V>::Hash(std::string key)
{
    // TODO: convertir la llave en un numero entre 0 y _capacidad-1.
    //
    // Recorre los caracteres de la llave y combinalos en un acumulador.
    // Al final aplica el modulo para que quepa en el rango de buckets.
    //
    // OJO: si solo SUMAS los caracteres, "abc" y "cba" te van a dar el
    // mismo numero, porque la suma no distingue el orden. Hay una prueba
    // que verifica justo eso. Busca "funcion hash para cadenas" y ve
    // como se resuelve.
    return 0;
}

template <class V>
void HashTable<V>::Insert(std::string key, V value)
{
    // TODO: 1) calcular el bucket con Hash()
    //       2) si la llave YA existe en ese bucket, reemplazar su valor
    //          (no crear una entrada duplicada, y no subir _size)
    //       3) si no existe, crear la Entry y engancharla en la cadena
}

template <class V>
V HashTable<V>::Get(std::string key)
{
    // TODO: buscar en la cadena del bucket correspondiente.
    //       Si no existe, avisar con ConsoleUI::PrintError y regresar V().
    return V();
}

template <class V>
bool HashTable<V>::Contains(std::string key)
{
    // TODO
    return false;
}

template <class V>
bool HashTable<V>::Remove(std::string key)
{
    // TODO: quitar la entrada de la cadena y liberarla.
    //       Regresa true si la quito, false si la llave no existia.
    //
    // CUIDADO: quitar la PRIMERA de la cadena no es igual que quitar
    // una de en medio. Vas a necesitar recordar la entrada anterior.
    return false;
}

template <class V>
int HashTable<V>::GetSize()
{
    // TODO
    return 0;
}

template <class V>
int HashTable<V>::GetCapacidad()
{
    return _capacidad;
}

template <class V>
void HashTable<V>::Print()
{
    // TODO: imprimir bucket por bucket, mostrando las llaves de cada
    // cadena. Asi puedes VER las colisiones con tus propios ojos.
}
