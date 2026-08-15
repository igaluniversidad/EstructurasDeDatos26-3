#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

void ConsoleUI::PrintTitle(std::string texto)
{
    int ancho = texto.length() + 4;
    PrintTitle(texto, ancho);
}

void ConsoleUI::PrintTitle(std::string texto, int ancho)
{
    if (ancho < texto.length() + 4)
    {
        ancho = texto.length() + 4;
    }

    std::string borde(ancho, '=');

    int espaciosSobrantes = ancho - texto.length();
    int paddingIzq = espaciosSobrantes / 2;
    int paddingDer = espaciosSobrantes - paddingIzq;

    std::cout << borde << std::endl;

    for (int i = 0; i < paddingIzq; i++) std::cout << " ";
    std::cout << texto;
    for (int i = 0; i < paddingDer; i++) std::cout << " ";
    std::cout << std::endl;

    std::cout << borde << std::endl;
}

void ConsoleUI::PrintColor(std::string texto, int codigoColor)
{
    std::cout << "\033[" << codigoColor << "m" << texto << "\033[" << COLOR_RESET << "m" << std::endl;
}

void ConsoleUI::PrintSuccess(std::string texto)
{
    PrintColor(texto, COLOR_GREEN);
}

void ConsoleUI::PrintError(std::string texto)
{
    PrintColor(texto, COLOR_RED);
}

void ConsoleUI::PrintSeparator()
{
    std::cout << "--------------------------------------------------" << std::endl;
}

void ConsoleUI::PrintList(int* arreglo, int tamanio)
{
    std::cout << std::left << std::setw(10) << "Indice" << "| Valor" << std::endl;
    std::cout << "-------------------" << std::endl;

    for (int i = 0; i < tamanio; i++)
    {
        std::cout << std::left << std::setw(10) << i << "| " << arreglo[i] << std::endl;
    }
}

void ConsoleUI::Pause()
{
    std::cout << "\nPresiona Enter para continuar...";
    std::string temp;
    std::getline(std::cin, temp);
}

void ConsoleUI::ClearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

void ConsoleUI::PrintProgressBar(int actual, int total)
{
    if (total <= 0) return;

    int barWidth = 10;
    float progress = static_cast<float>(actual) / total;
    int percentage = static_cast<int>(progress * 100.0f);
    int filledWidth = static_cast<int>(progress * barWidth);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < filledWidth)
        {
            std::cout << "#";
        }
        else
        {
            std::cout << "-";
        }
    }

    std::cout << "] " << percentage << "%\r";
    std::cout.flush();

    if (actual == total)
    {
        std::cout << std::endl;
    }
}