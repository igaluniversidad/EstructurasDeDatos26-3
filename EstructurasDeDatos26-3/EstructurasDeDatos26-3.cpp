#include <iostream>
#include <cstdlib>
#include <ctime>  
#include <thread>
#include <chrono>
#include "LinkedList.h"
#include "ConsoleUI.h"
#include "Nodo.h"

int main()
{
    srand(time(NULL));

    LinkedList listaSelection;
    LinkedList listaInsertion;

    ConsoleUI::ClearScreen();
    ConsoleUI::PrintTitle("Prueba de Ordenamientos");

    ConsoleUI::PrintColor("Generando datos aleatorios...", ConsoleUI::COLOR_CYAN);

    int elementos = 5;
    for (int i = 1; i <= elementos; i++) {
        int randomValue = rand() % 100;
        listaSelection.Add(randomValue);
        listaInsertion.Add(randomValue);

        ConsoleUI::PrintProgressBar(i, elementos);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    ConsoleUI::PrintSeparator();

    ConsoleUI::PrintColor("Lista Original (Desordenada):", ConsoleUI::COLOR_YELLOW);
    listaSelection.Print();
    ConsoleUI::PrintSeparator();

    ConsoleUI::PrintColor("Ordenando con Selection Sort...", ConsoleUI::COLOR_CYAN);
    listaSelection.SelectionSort();

    ConsoleUI::PrintSuccess("Lista Ordenada Correctamente (Selection):");
    listaSelection.Print();
    ConsoleUI::PrintSeparator();

    ConsoleUI::PrintColor("Ordenando con Insertion Sort la misma lista...", ConsoleUI::COLOR_CYAN);
    listaInsertion.InsertionSort();

    ConsoleUI::PrintSuccess("Lista Ordenada Correctamente (Insertion):");
    listaInsertion.Print();

    ConsoleUI::Pause();
    return 0;
}