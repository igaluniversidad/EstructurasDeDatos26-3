// EstructurasDeDatos26-3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>  
#include "LinkedList.h"
#include "ConsoleUI.h"
#include "Nodo.h"

int main()
{
    srand(time(NULL)); // Semilla para números aleatorios

    LinkedList listaSelection;
    LinkedList listaInsertion;

    // Llenamos ambas listas con los mismos valores aleatorios para poder comparar
    for (int i = 0; i < 5; i++) {
        int randomValue = rand() % 100;
        listaSelection.Add(randomValue);
        listaInsertion.Add(randomValue);
    }

    ConsoleUI::ClearScreen();
    ConsoleUI::PrintTitle("Prueba de Ordenamientos");

    // ==========================================
    // PRUEBA 1: SELECTION SORT
    // ==========================================
    ConsoleUI::PrintColor("Lista Original (Desordenada):", ConsoleUI::COLOR_YELLOW);
    listaSelection.Print();
    ConsoleUI::PrintSeparator();

    ConsoleUI::PrintColor("Ordenando con Selection Sort...", ConsoleUI::COLOR_CYAN);
    listaSelection.SelectionSort();

    ConsoleUI::PrintSuccess("Lista Ordenada Correctamente (Selection):");
    listaSelection.Print();
    ConsoleUI::PrintSeparator();

    // ==========================================
    // PRUEBA 2: INSERTION SORT
    // ==========================================
    ConsoleUI::PrintColor("Ordenando con Insertion Sort la misma lista...", ConsoleUI::COLOR_CYAN);
    listaInsertion.InsertionSort();

    ConsoleUI::PrintSuccess("Lista Ordenada Correctamente (Insertion):");
    listaInsertion.Print();

    ConsoleUI::Pause();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file