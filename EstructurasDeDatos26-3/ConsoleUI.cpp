#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

// Implementación de PrintTitle con ancho automático
void ConsoleUI::PrintTitle(std::string texto)
{
    // Calculamos un ancho automático dándole un margen de 2 espacios a cada lado
    int ancho = texto.length() + 4;
    PrintTitle(texto, ancho);
}

// Implementación de PrintTitle con ancho específico
void ConsoleUI::PrintTitle(std::string texto, int ancho)
{
    // Decisión de diseño: Si el texto es más largo que el ancho, 
    // lo adaptamos para que no se vea feo ni se corte el texto.
    if (ancho < texto.length() + 4)
    {
        ancho = texto.length() + 4;
    }

    std::string borde(ancho, '=');

    // Calcular relleno (padding) para centrar el texto
    int espaciosSobrantes = ancho - texto.length();
    int paddingIzq = espaciosSobrantes / 2;
    int paddingDer = espaciosSobrantes - paddingIzq;

    std::cout << borde << std::endl;

    // Imprimir relleno izquierdo, el texto, y relleno derecho
    for (int i = 0; i < paddingIzq; i++) std::cout << " ";
    std::cout << texto;
    for (int i = 0; i < paddingDer; i++) std::cout << " ";
    std::cout << std::endl;

    std::cout << borde << std::endl;
}

// Método base para imprimir con color y resetear después
void ConsoleUI::PrintColor(std::string texto, int codigoColor)
{
    std::cout << "\033[" << codigoColor << "m" << texto << "\033[" << COLOR_RESET << "m" << std::endl;
}

// Reutilización estricta de PrintColor para éxito y error
void ConsoleUI::PrintSuccess(std::string texto)
{
    PrintColor(texto, COLOR_GREEN);
}

void ConsoleUI::PrintError(std::string texto)
{
    PrintColor(texto, COLOR_RED);
}

// Imprime una línea divisoria estándar
void ConsoleUI::PrintSeparator()
{
    std::cout << "--------------------------------------------------" << std::endl;
}

// Imprime un arreglo primitivo tabularmente
void ConsoleUI::PrintList(int* arreglo, int tamanio)
{
    // Usamos std::setw() de <iomanip> para forzar un ancho de columna parejo
    std::cout << std::left << std::setw(10) << "Indice" << "| Valor" << std::endl;
    std::cout << "-------------------" << std::endl;

    for (int i = 0; i < tamanio; i++)
    {
        std::cout << std::left << std::setw(10) << i << "| " << arreglo[i] << std::endl;
    }
}

// Detiene la consola
void ConsoleUI::Pause()
{
    std::cout << "\nPresiona Enter para continuar...";
    std::string temp;
    std::getline(std::cin, temp);
}

// Limpia la consola
void ConsoleUI::ClearScreen()
{
    // Código ANSI para limpiar la pantalla sin hacer llamadas costosas a system("cls/clear")
    // \033[2J limpia la pantalla entera
    // \033[1;1H mueve el cursor a la fila 1, columna 1 (arriba a la izquierda)
    std::cout << "\033[2J\033[1;1H";
}