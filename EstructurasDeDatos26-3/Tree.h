#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "LinkedQueue.h"
#include "ConsoleUI.h"

// =====================================================================
//  Tree<T>  -  Arbol binario de busqueda (BST)
//
//  La regla del BST: todo lo MENOR que un nodo vive a su izquierda,
//  todo lo MAYOR vive a su derecha. Gracias a esa regla, buscar no
//  recorre todo: en cada nodo descartas la mitad del arbol.
//
//  LOS RECORRIDOS no imprimen: LLENAN una LinkedList<T> que se les
//  pasa por referencia. Asi el recorrido queda separado de como se
//  muestra, y ademas se puede verificar automaticamente.
//
//  Los tres recorridos DFS recursivos son LAS MISMAS TRES LINEAS con
//  la linea de "agregar al resultado" en distinto lugar:
//      Pre-orden:   nodo,        izquierda,   derecha
//      In-orden:    izquierda,   nodo,        derecha    <- sale ORDENADO
//      Post-orden:  izquierda,   derecha,     nodo
//  Escribe uno, y los otros dos son mover una linea.
// =====================================================================

template <class T>
class Tree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
    };

    Node* _root;
    int _size;

    // Auxiliares recursivas. Reciben el nodo actual porque la recursion
    // necesita "bajar", y desde afuera nadie ve los nodos.
    void DestruirRec(Node* n);
    void InsertRec(Node*& n, T valor);
    bool ContainsRec(Node* n, T valor);
    int  AlturaRec(Node* n);

    void PreRec(Node* n, LinkedList<T>& resultado);
    void InRec(Node* n, LinkedList<T>& resultado);
    void PostRec(Node* n, LinkedList<T>& resultado);
    void NivelRec(Node* n, int nivel, LinkedList<T>& resultado);

public:
    Tree();
    ~Tree();

    void Insert(T valor);
    bool Contains(T valor);
    int GetSize();
    int GetAltura();
    void Print();

    // --- DFS recursivos ---
    void PreOrden(LinkedList<T>& resultado);
    void InOrden(LinkedList<T>& resultado);
    void PostOrden(LinkedList<T>& resultado);

    // --- DFS iterativo (usa TU Stack) ---
    void InOrdenIterativo(LinkedList<T>& resultado);

    // --- BFS ---
    void PorNiveles(LinkedList<T>& resultado);            // usa TU LinkedQueue
    void PorNivelesRecursivo(LinkedList<T>& resultado);   // sin cola
};

template <class T>
Tree<T>::Tree()
{
    _root = nullptr;
    _size = 0;
}

template <class T>
Tree<T>::~Tree()
{
    // TODO: llamar a DestruirRec desde la raiz
}

template <class T>
void Tree<T>::DestruirRec(Node* n)
{
    // TODO: destruir primero los hijos y HASTA EL FINAL el nodo actual.
    // Si borras el nodo antes que sus hijos, pierdes la forma de llegar
    // a ellos. Fijate que ese orden es exactamente el POST-ORDEN.
}

template <class T>
void Tree<T>::Insert(T valor)
{
    // TODO: arrancar la recursion desde la raiz
}

template <class T>
void Tree<T>::InsertRec(Node*& n, T valor)
{
    // TODO: si n es nullptr, aqui va el nodo nuevo (y sube _size).
    //       Si el valor es menor, baja a la izquierda.
    //       Si es mayor, baja a la derecha.
    //       Si es igual, no hagas nada: no se permiten duplicados.
    //
    // OJO con la firma: 'Node*& n' es una REFERENCIA a puntero. Eso es
    // lo que te permite asignarle el nodo nuevo y que el cambio se vea
    // en el padre. Con 'Node* n' a secas, modificarias una copia del
    // puntero y el arbol se quedaria vacio.
}

template <class T>
bool Tree<T>::Contains(T valor)
{
    // TODO
    return false;
}

template <class T>
bool Tree<T>::ContainsRec(Node* n, T valor)
{
    // TODO: caso base cuando n es nullptr (no esta).
    //       Si no, compara y baja por el lado que corresponde.
    return false;
}

template <class T>
int Tree<T>::GetSize()
{
    // TODO
    return 0;
}

template <class T>
int Tree<T>::GetAltura()
{
    // TODO
    return 0;
}

template <class T>
int Tree<T>::AlturaRec(Node* n)
{
    // TODO: un arbol vacio mide 0. Si no, mide 1 mas que el MAS ALTO
    //       de sus dos subarboles.
    return 0;
}

template <class T>
void Tree<T>::PreOrden(LinkedList<T>& resultado)
{
    // TODO: arrancar PreRec desde la raiz
}

template <class T>
void Tree<T>::PreRec(Node* n, LinkedList<T>& resultado)
{
    // TODO: nodo, izquierda, derecha
}

template <class T>
void Tree<T>::InOrden(LinkedList<T>& resultado)
{
    // TODO
}

template <class T>
void Tree<T>::InRec(Node* n, LinkedList<T>& resultado)
{
    // TODO: izquierda, nodo, derecha
}

template <class T>
void Tree<T>::PostOrden(LinkedList<T>& resultado)
{
    // TODO
}

template <class T>
void Tree<T>::PostRec(Node* n, LinkedList<T>& resultado)
{
    // TODO: izquierda, derecha, nodo
}

template <class T>
void Tree<T>::InOrdenIterativo(LinkedList<T>& resultado)
{
    // TODO: el mismo in-orden, pero SIN recursion, usando TU Stack<Node*>.
    //
    // La idea: baja lo mas a la izquierda que puedas, apilando cada nodo
    // por el que pasas. Cuando ya no puedas bajar mas, saca uno de la
    // pila, agregalo al resultado, y muevete a SU hijo derecho.
    // Repite mientras queden nodos o la pila no este vacia.
    //
    // Aqui esta la leccion: la pila que el compilador manejaba solo en
    // la version recursiva, ahora la manejas tu a mano. Son la misma
    // cosa con distinta ropa.
}

template <class T>
void Tree<T>::PorNiveles(LinkedList<T>& resultado)
{
    // TODO: BFS con TU LinkedQueue<Node*>.
    //
    // Mete la raiz a la cola. Mientras la cola no este vacia:
    // saca uno, agregalo al resultado, y encola a sus hijos
    // (primero el izquierdo, luego el derecho).
    //
    // Fijate: es el MISMO algoritmo que el de arriba, pero cambiando
    // la pila por una cola. Eso solito convierte un DFS en un BFS.
}

template <class T>
void Tree<T>::PorNivelesRecursivo(LinkedList<T>& resultado)
{
    // TODO: el mismo resultado que PorNiveles, pero SIN cola.
    //
    // Estrategia: pide la altura del arbol, y luego, para cada nivel
    // del 1 hasta la altura, baja recursivamente y agrega solo los
    // nodos de ESE nivel.
    //
    // Va a ser mas lento que la version con cola: los nodos de arriba
    // se vuelven a recorrer una vez por cada nivel que hay debajo.
    // Compara las dos versiones y piensa por que.
}

template <class T>
void Tree<T>::NivelRec(Node* n, int nivel, LinkedList<T>& resultado)
{
    // TODO: si nivel == 1, este nodo es de los que van al resultado.
    //       Si no, baja a los dos hijos pidiendo el nivel de abajo.
}

template <class T>
void Tree<T>::Print()
{
    // TODO: usa el recorrido in-orden y ConsoleUI para mostrar el arbol.
    // Casi todo el trabajo ya lo hiciste: aqui solo lo conectas.
}
