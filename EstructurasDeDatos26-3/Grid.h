#pragma once
#include <iostream>
#include "ConsoleUI.h"

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
    _celdas = nullptr;
    _visitadas = nullptr;
    _filas = filas;
    _columnas = columnas;

    _celdas = new T*[_filas];
    _visitadas = new bool*[_filas];
    for (int i = 0; i < _filas; ++i)
    {
        _celdas[i] = new T[_columnas];
        _visitadas[i] = new bool[_columnas];
        for (int j = 0; j < _columnas; ++j)
        {
            _celdas[i][j] = T();
            _visitadas[i][j] = false;
        }
    }
}

template <class T>
Grid<T>::~Grid()
{
    if (_celdas != nullptr)
    {
        for (int i = 0; i < _filas; ++i)
            delete[] _celdas[i];
        delete[] _celdas;
        _celdas = nullptr;
    }
    if (_visitadas != nullptr)
    {
        for (int i = 0; i < _filas; ++i)
            delete[] _visitadas[i];
        delete[] _visitadas;
        _visitadas = nullptr;
    }
}

template <class T>
void Grid<T>::Set(int fila, int columna, T valor)
{
    if (fila < 0 || fila >= _filas || columna < 0 || columna >= _columnas)
    {
        ConsoleUI::PrintError("Grid::Set: coordenada fuera de rango");
        return;
    }
    _celdas[fila][columna] = valor;
}

template <class T>
T Grid<T>::Get(int fila, int columna)
{
    if (fila < 0 || fila >= _filas || columna < 0 || columna >= _columnas)
    {
        ConsoleUI::PrintError("Grid::Get: coordenada fuera de rango");
        return T();
    }
    return _celdas[fila][columna];
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
    if (fila < 0 || fila >= _filas || columna < 0 || columna >= _columnas)
    {
        ConsoleUI::PrintError("Grid::FloodFill: coordenada fuera de rango");
        return 0;
    }
    for (int i = 0; i < _filas; ++i)
        for (int j = 0; j < _columnas; ++j)
            _visitadas[i][j] = false;

    T objetivo = _celdas[fila][columna];
    return FloodRecursivo(fila, columna, objetivo);
}

template <class T>
int Grid<T>::FloodRecursivo(int fila, int columna, T objetivo)
{
    if (fila < 0 || fila >= _filas || columna < 0 || columna >= _columnas)
        return 0;
    if (_visitadas[fila][columna])
        return 0;
    if (_celdas[fila][columna] != objetivo)
        return 0;

    _visitadas[fila][columna] = true;

    int count = 1;
    count += FloodRecursivo(fila + 1, columna, objetivo);
    count += FloodRecursivo(fila - 1, columna, objetivo);
    count += FloodRecursivo(fila, columna + 1, objetivo);
    count += FloodRecursivo(fila, columna - 1, objetivo);
    return count;
}

template <class T>
void Grid<T>::Print()
{
    std::cout << "    ";
    for (int c = 0; c < _columnas; ++c)
        std::cout << c << "\t";
    std::cout << std::endl;
    for (int f = 0; f < _filas; ++f)
    {
        std::cout << f << " | ";
        for (int c = 0; c < _columnas; ++c)
        {
            std::cout << _celdas[f][c] << "\t";
        }
        std::cout << std::endl;
    }
}
