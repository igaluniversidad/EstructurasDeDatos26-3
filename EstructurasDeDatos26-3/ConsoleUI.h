#pragma once
#include <string>

class ConsoleUI
{
public:
    // Códigos ANSI definidos como constantes para evitar hardcodearlos por todo el código
    static const int COLOR_RESET = 0;
    static const int COLOR_RED = 31;
    static const int COLOR_GREEN = 32;
    static const int COLOR_YELLOW = 33;
    static const int COLOR_BLUE = 34;
    static const int COLOR_MAGENTA = 35;
    static const int COLOR_CYAN = 36;
    static const int COLOR_WHITE = 37;

    // Métodos estáticos de comportamiento
    static void PrintTitle(std::string texto);
    static void PrintTitle(std::string texto, int ancho);
    static void PrintColor(std::string texto, int codigoColor);
    static void PrintSuccess(std::string texto);
    static void PrintError(std::string texto);
    static void PrintSeparator();
    static void PrintList(int* arreglo, int tamanio);
    static void Pause();
    static void ClearScreen();
    static void PrintProgressBar(int actual, int total);

};