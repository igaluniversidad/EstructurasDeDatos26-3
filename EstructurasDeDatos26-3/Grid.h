#pragma once
#include <iostream>

// =====================================================================
//  Grid<T>  -  Rejilla generica (arreglo 2D dinamico encapsulado)
//
//  Esta es la version bien hecha de la matriz que ya programaste antes
//  con punteros sueltos: ahora la memoria vive encapsulada dentro de
//  una clase que se encarga de reservarla y liberarla.
//
//  Y no es un ejercicio de escuela: esta rejilla es literalmente el
//  tablero de tu Match-3.
//
//  FLOOD FILL: dada una celda inicial, encuentra todas las celdas
//  CONECTADAS que tengan el mismo valor, y regresa cuantas son.
//  Es recursivo y tiene tres casos base:
//     1. te saliste de los limites
//     2. la celda tiene un valor distinto al que buscas
//     3. ya habias visitado esa celda
//  Y cuatro llamadas recursivas: arriba, abajo, izquierda, derecha.
//  Las diagonales NO cuentan como vecinas.
// =====================================================================

template <class T>
class Grid
{
private:
    T** _celdas;
    bool** _visitadas;
    int _filas;
    int _columnas;

    int FloodRecursivo(int fila, int columna, T objetivo);

public:
    Grid(int filas, int columnas);
    ~Grid();

    void Set(int fila, int columna, T valor);
    T Get(int fila, int columna);
    int GetFilas();
    int GetColumnas();
    int FloodFill(int fila, int columna);
    void Print();
};

template <class T>
Grid<T>::Grid(int filas, int columnas)
{
    // Los punteros arrancan en nullptr para que nada truene antes de
    // que reserves la memoria. NO borres estas dos lineas.
    _celdas = nullptr;
    _visitadas = nullptr;
    _filas = filas;
    _columnas = columnas;

    // TODO: reservar la memoria de _celdas y _visitadas.
    // Acuerdate: primero un arreglo de punteros, y luego dentro de un
    // ciclo, un arreglo por cada renglon.
}

template <class T>
Grid<T>::~Grid()
{
    // TODO: liberar en el orden INVERSO al que reservaste:
    //       primero cada renglon, y al final el arreglo de punteros.
}

template <class T>
void Grid<T>::Set(int fila, int columna, T valor)
{
    // TODO: validar que la coordenada exista antes de escribir
}

template <class T>
T Grid<T>::Get(int fila, int columna)
{
    // TODO: validar que la coordenada exista antes de leer
    return T();
}

template <class T>
int Grid<T>::GetFilas()
{
    return _filas;
}

template <class T>
int Grid<T>::GetColumnas()
{
    return _columnas;
}

template <class T>
int Grid<T>::FloodFill(int fila, int columna)
{
    // TODO: 1) validar la coordenada
    //       2) REINICIAR todas las celdas visitadas a false
    //          (si no lo haces, la segunda vez que corras FloodFill
    //           te va a regresar 0)
    //       3) llamar a FloodRecursivo con el valor de esa celda
    return 0;
}

template <class T>
int Grid<T>::FloodRecursivo(int fila, int columna, T objetivo)
{
    // TODO: tres casos base, luego marcar como visitada,
    //       y sumar 1 + las cuatro llamadas recursivas
    return 0;
}

template <class T>
void Grid<T>::Print()
{
    // TODO: imprimir la rejilla en formato tabular
}
