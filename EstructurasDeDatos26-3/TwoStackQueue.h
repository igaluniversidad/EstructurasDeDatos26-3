#pragma once
#include "Stack.h"
#include "ConsoleUI.h"
#include <iostream>

// =====================================================================
//  TwoStackQueue<T>  -  Cola (FIFO) construida con DOS pilas (LIFO)
//
//  LA IDEA: una pila invierte el orden. Dos pilas lo invierten dos
//  veces, y volver a invertir es regresar al orden original.
//  Orden original = FIFO = cola.
//
//  COMO FUNCIONA:
//    Enqueue -> siempre empuja a _entrada.
//    Dequeue -> saca de _salida. Y SOLO si _salida esta vacia,
//               primero vuelca TODA _entrada dentro de _salida.
//
//  LA REGLA CRITICA: solo vuelcas cuando _salida esta VACIA.
//  Si vuelcas teniendo elementos ahi, los nuevos caen encima de los
//  viejos y salen antes. Ese es el error que casi todos cometen.
//
//  Fijate que esta clase NO maneja punteros ni memoria: reutiliza tu
//  Stack, que ya sabe hacerlo. Por eso tampoco necesita destructor
//  propio (los destructores de _entrada y _salida corren solos).
//
//  IMPORTANTE: tiene EXACTAMENTE la misma interfaz publica que
//  LinkedQueue. Un mismo main debe funcionar con las dos cambiando
//  una sola linea.
// =====================================================================

template <class T>
class TwoStackQueue
{
private:
    Stack<T> _entrada;
    Stack<T> _salida;

    void Volcar();   // pasa todo de _entrada a _salida (si hace falta)

public:
    TwoStackQueue();
    ~TwoStackQueue();

    void Enqueue(T value);
    T Dequeue();
    T Front();
    bool IsEmpty();
    int GetSize();
    void Clear();
    void Print();
};

template <class T>
TwoStackQueue<T>::TwoStackQueue()
{
}

template <class T>
TwoStackQueue<T>::~TwoStackQueue()
{
}

template <class T>
void TwoStackQueue<T>::Volcar()
{
    if (_salida.IsEmpty())
    {
        while (!_entrada.IsEmpty())
        {
            T v = _entrada.Pop();
            _salida.Push(v);
        }
    }
}

template <class T>
void TwoStackQueue<T>::Enqueue(T value)
{
    _entrada.Push(value);
}

template <class T>
T TwoStackQueue<T>::Dequeue()
{
    Volcar();
    if (_salida.IsEmpty())
    {
        ConsoleUI::PrintError("TwoStackQueue::Dequeue: cola vacia");
        return T();
    }
    return _salida.Pop();
}

template <class T>
T TwoStackQueue<T>::Front()
{
    Volcar();
    if (_salida.IsEmpty())
    {
        ConsoleUI::PrintError("TwoStackQueue::Front: cola vacia");
        return T();
    }
    return _salida.Top();
}

template <class T>
bool TwoStackQueue<T>::IsEmpty()
{
    return _entrada.IsEmpty() && _salida.IsEmpty();
}

template <class T>
int TwoStackQueue<T>::GetSize()
{
    return _entrada.GetSize() + _salida.GetSize();
}

template <class T>
void TwoStackQueue<T>::Clear()
{
    _entrada.Clear();
    _salida.Clear();
}

template <class T>
void TwoStackQueue<T>::Print()
{
    // Para imprimir en orden FIFO sin modificar la cola,
    // hacemos copias temporales y las vaciamos.
    // Orden: elementos de _salida (tope es frente) luego _entrada invertida.
    Stack<T> copiaSalida = _salida;
    Stack<T> copiaEntrada = _entrada;
    // _salida ya esta en orden correcto (tope = frente)
    // _entrada necesita invertirse: su fondo es el siguiente despues de _salida
    // Para obtener fondo->tope de entrada, vaciamos entrada a una pila auxiliar invertida
    Stack<T> entradaInvertida;
    // Vaciamos copiaEntrada a entradaInvertida de forma que el fondo quede arriba
    // copiaEntrada top es el mas nuevo, fondo es el mas viejo de entrada.
    // Si hacemos pop de copiaEntrada y push a entradaInvertida, invertimos.
    // Pero necesitamos que entradaInvertida top = fondo de entrada.
    // Ejemplo: entrada [3 top,2,1 bottom] -> al volcar pop 3 push, pop2 push, pop1 push => entradaInvertida [1 top,2,3]
    // Eso es correcto: 1 es el que debe salir primero despues de salida.
    Stack<T> tmp;
    while (!copiaEntrada.IsEmpty())
    {
        tmp.Push(copiaEntrada.Pop());
    }
    // tmp ahora tiene [1 top si entrada original era 3,2,1? Wait trace:
    // copiaEntrada [3 top,2,1] pop3 push tmp [3], pop2 push [2,3], pop1 push [1,2,3] => tmp top=1 fondo=3
    // Eso es el orden que necesitamos para imprimir despues de salida: 1 luego 2 luego 3.
    // Pero falta que al imprimir recorramos de frente a final: salida primero, luego tmp.
    std::cout << "[FRENTE] ";
    bool primero = true;
    // Imprimir salida
    while (!copiaSalida.IsEmpty())
    {
        if (!primero) std::cout << " -> ";
        std::cout << copiaSalida.Pop();
        primero = false;
    }
    while (!tmp.IsEmpty())
    {
        if (!primero) std::cout << " -> ";
        std::cout << tmp.Pop();
        primero = false;
    }
    std::cout << " [FINAL]" << std::endl;
}
