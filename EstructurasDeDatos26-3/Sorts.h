#pragma once

// =====================================================================
//  Sorts.h  -  Ordenamientos de division (divide y venceras)
//
//  Estas son FUNCIONES LIBRES, no metodos de ninguna clase. No es un
//  capricho:
//
//  SelectionSort e InsertionSort SI viven dentro de LinkedList, porque
//  para funcionar necesitan caminar de nodo en nodo, o sea que necesitan
//  conocer las tripas de la lista.
//
//  MergeSort y QuickSort no necesitan nada de eso: solo necesitan una
//  secuencia de elementos que puedan comparar e intercambiar. Por eso el
//  mismo codigo, sin cambiar una linea, ordena enteros, caracteres o
//  cadenas, vengan de donde vengan.
//
//  La regla: si el algoritmo necesita saber como esta construida la
//  estructura por dentro, va adentro de la clase. Si solo necesita una
//  secuencia, va afuera como funcion libre.
//
//  Y de paso, ya sabes por que en la biblioteca estandar existe
//  std::sort como funcion libre y no vector::sort como metodo.
// =====================================================================


// ---------------------------------------------------------------------
//  MERGE SORT
//
//  1. Parte el arreglo a la mitad.
//  2. Ordena cada mitad (llamandose a si mismo).
//  3. Combina las dos mitades ordenadas en una sola.
//
//  Caso base: un arreglo de un solo elemento ya esta ordenado.
//  Todo el trabajo real esta en el paso 3.
// ---------------------------------------------------------------------

template <class T>
void Mezclar(T* arreglo, int inicio, int medio, int fin)
{
    int tamanio = fin - inicio + 1; // calculo cuantos elementos son en total
    T* temp = new T[tamanio]; // creo un arreglo temporal para ordenar

    int i = inicio; // indice para la mitad izquierda
    int j = medio + 1; // indice para la mitad derecha
    int k = 0; // indice para el arreglo temporal

    while (i <= medio && j <= fin) // mientras las dos mitades tengan datos
    {
        if (arreglo[i] <= arreglo[j]) // si el de la izquierda es mas chico
        {
            temp[k] = arreglo[i]; // lo copio al temporal
            i++; // avanzo en la izquierda
        }
        else // si el de la derecha es mas chico
        {
            temp[k] = arreglo[j]; // lo copio al temporal
            j++; // avanzo en la derecha
        }
        k++; // avanzo en el temporal
    }

    while (i <= medio) // si sobro algo de la izquierda
    {
        temp[k] = arreglo[i]; // lo copio
        i++; // avanzo en la izquierda
        k++; // avanzo en el temporal
    }

    while (j <= fin) // si sobro algo de la derecha
    {
        temp[k] = arreglo[j]; // lo copio
        j++; // avanzo en la derecha
        k++; // avanzo en el temporal
    }

    for (int m = 0; m < tamanio; m++) // recorro todo el temporal
    {
        arreglo[inicio + m] = temp[m]; // lo regreso al arreglo original
    }

    delete[] temp; // borro el temporal para no fugar memoria
}

template <class T>
void MergeRec(T* arreglo, int inicio, int fin)
{
    if (inicio >= fin) // si es un solo elemento o menos
    {
        return; // ya esta ordenado, me salgo
    }

    int medio = (inicio + fin) / 2; // saco la mitad
    MergeRec(arreglo, inicio, medio); // ordeno la mitad izquierda
    MergeRec(arreglo, medio + 1, fin); // ordeno la mitad derecha
    Mezclar(arreglo, inicio, medio, fin); // junto las dos mitades ordenadas
}

template <class T>
void MergeSort(T* arreglo, int tamanio)
{
    if (tamanio <= 1) // si esta vacio o tiene uno solo
    {
        return; // no hay nada que ordenar
    }

    MergeRec(arreglo, 0, tamanio - 1); // empiezo desde todo el arreglo
}


// ---------------------------------------------------------------------
//  QUICK SORT
//
//  1. Escoge un elemento como PIVOTE.
//  2. Acomoda el arreglo para que todo lo menor al pivote quede a su
//     izquierda y todo lo mayor a su derecha (particion).
//  3. Ordena cada lado (llamandose a si mismo).
//
//  Fijate en la diferencia con Merge Sort: aquel divide facil y trabaja
//  al combinar. Este trabaja al dividir, y ya no necesita combinar nada,
//  porque despues de la particion cada lado quedo en su lugar.
// ---------------------------------------------------------------------

template <class T>
int Particion(T* arreglo, int inicio, int fin)
{
    T pivote = arreglo[fin]; // agarro el ultimo como pivote
    int i = inicio - 1; // i marca donde van los chicos

    for (int j = inicio; j < fin; j++) // recorro desde inicio hasta antes del pivote
    {
        if (arreglo[j] <= pivote) // si este es menor o igual que el pivote
        {
            i++; // avanzo la frontera de los chicos
            T aux = arreglo[i]; // guardo el de la frontera
            arreglo[i] = arreglo[j]; // pongo el chico adelante
            arreglo[j] = aux; // pongo el otro atras
        }
    }

    T aux = arreglo[i + 1]; // guardo el que esta despues de los chicos
    arreglo[i + 1] = arreglo[fin]; // pongo el pivote en su lugar final
    arreglo[fin] = aux; // pongo el otro donde estaba el pivote

    return i + 1; // regreso donde quedo el pivote
}

template <class T>
void QuickRec(T* arreglo, int inicio, int fin)
{
    if (inicio < fin) // si hay mas de un elemento
    {
        int p = Particion(arreglo, inicio, fin); // acomodo y me da donde quedo el pivote
        QuickRec(arreglo, inicio, p - 1); // ordeno lo de la izquierda del pivote
        QuickRec(arreglo, p + 1, fin); // ordeno lo de la derecha del pivote
    }
}

template <class T>
void QuickSort(T* arreglo, int tamanio)
{
    if (tamanio <= 1) // si esta vacio o tiene uno solo
    {
        return; // no hay nada que ordenar
    }

    QuickRec(arreglo, 0, tamanio - 1); // empiezo desde todo el arreglo
}
