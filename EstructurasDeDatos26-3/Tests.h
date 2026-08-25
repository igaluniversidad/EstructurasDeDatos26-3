#pragma once

// Corre todas las pruebas de la libreria.
void CorrerTodasLasPruebas();

// Corre solo las pruebas de un grupo.
// Grupos disponibles: "Stack", "ReglaDeTres", "Queue",
//                     "LinkedList", "Recursividad", "Grid", "Memoria"
void CorrerPruebasDe(const char* nombreSuite);
