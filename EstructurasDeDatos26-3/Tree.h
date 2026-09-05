#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "LinkedQueue.h"
#include "ConsoleUI.h"

// =====================================================================
//  Tree<T>  -  Arbol binario de busqueda (BST)
//
//  La regla del BST: todo lo MENOR que un nodo vive a su leftHeightuierda,
//  todo lo MAYOR vive a su rightHeightecha. Gracias a esa regla, buscar no
//  recorre todo: en cada nodo descartas la mitad del arbol.
//
//  LOS RECORRIDOS no imprimen: LLENAN una LinkedList<T> que se les
//  pasa por referencia. Asi el recorrido queda separado de como se
//  muestra, y ademas se puede verificar automaticamente.
//
//  Los tres recorridos DFS recursivos son LAS MISMAS TRES LINEAS con
//  la linea de "agregar al resultado" en distinto lugar:
//      Pre-orden:   nodo,        leftHeightuierda,   rightHeightecha
//      In-orden:    leftHeightuierda,   nodo,        rightHeightecha    <- sale ORDENADO
//      Post-orden:  leftHeightuierda,   rightHeightecha,     nodo
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
    void DestruirRec(Node* currentNode);
    void InsertRec(Node*& currentNode, T valor);
    bool ContainsRec(Node* currentNode, T valor);
    int  AlturaRec(Node* currentNode);

    void PreRec(Node* currentNode, LinkedList<T>& resultado);
    void InRec(Node* currentNode, LinkedList<T>& resultado);
    void PostRec(Node* currentNode, LinkedList<T>& resultado);
    void NivelRec(Node* currentNode, int nivel, LinkedList<T>& resultado);

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
    DestruirRec(_root);
    _root = nullptr;
    _size = 0;
}

template <class T>
void Tree<T>::DestruirRec(Node* currentNode)
{
    // Post-orden: primero los hijos, al final el nodo actual.
    if (currentNode == nullptr) return;
    DestruirRec(currentNode->left);
    DestruirRec(currentNode->right);
    delete currentNode;
}

template <class T>
void Tree<T>::Insert(T valor)
{
    InsertRec(_root, valor);
}

template <class T>
void Tree<T>::InsertRec(Node*& currentNode, T valor)
{
    // Si llegamos a un hueco, aqui va el nodo nuevo.
    // Gracias a que currentNode es referencia a puntero, el padre queda enlazado.
    if (currentNode == nullptr)
    {
        currentNode = new Node();
        currentNode->data = valor;
        currentNode->left = nullptr;
        currentNode->right = nullptr;
        _size++;
        return;
    }
    if (valor < currentNode->data)
    {
        InsertRec(currentNode->left, valor);
    }
    else if (valor > currentNode->data)
    {
        InsertRec(currentNode->right, valor);
    }
    // Si es igual, no se hace nada: no se permiten duplicados.
}

template <class T>
bool Tree<T>::Contains(T valor)
{
    return ContainsRec(_root, valor);
}

template <class T>
bool Tree<T>::ContainsRec(Node* currentNode, T valor)
{
    if (currentNode == nullptr) return false;
    if (valor == currentNode->data) return true;
    if (valor < currentNode->data) return ContainsRec(currentNode->left, valor);
    return ContainsRec(currentNode->right, valor);
}

template <class T>
int Tree<T>::GetSize()
{
    return _size;
}

template <class T>
int Tree<T>::GetAltura()
{
    return AlturaRec(_root);
}

template <class T>
int Tree<T>::AlturaRec(Node* currentNode)
{
    if (currentNode == nullptr) return 0;
    int leftHeight = AlturaRec(currentNode->left);
    int rightHeight = AlturaRec(currentNode->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <class T>
void Tree<T>::PreOrden(LinkedList<T>& resultado)
{
    PreRec(_root, resultado);
}

template <class T>
void Tree<T>::PreRec(Node* currentNode, LinkedList<T>& resultado)
{
    if (currentNode == nullptr) return;
    resultado.Add(currentNode->data);
    PreRec(currentNode->left, resultado);
    PreRec(currentNode->right, resultado);
}

template <class T>
void Tree<T>::InOrden(LinkedList<T>& resultado)
{
    InRec(_root, resultado);
}

template <class T>
void Tree<T>::InRec(Node* currentNode, LinkedList<T>& resultado)
{
    if (currentNode == nullptr) return;
    InRec(currentNode->left, resultado);
    resultado.Add(currentNode->data);
    InRec(currentNode->right, resultado);
}

template <class T>
void Tree<T>::PostOrden(LinkedList<T>& resultado)
{
    PostRec(_root, resultado);
}

template <class T>
void Tree<T>::PostRec(Node* currentNode, LinkedList<T>& resultado)
{
    if (currentNode == nullptr) return;
    PostRec(currentNode->left, resultado);
    PostRec(currentNode->right, resultado);
    resultado.Add(currentNode->data);
}

template <class T>
void Tree<T>::InOrdenIterativo(LinkedList<T>& resultado)
{
    // In-orden sin recursion: nodeStack guarda los nodos pendientes.
    // Es el mismo trabajo que hacia la pila de llamadas del compilador.
    Stack<Node*> nodeStack;
    Node* currentNode = _root;

    while (currentNode != nullptr || !nodeStack.IsEmpty())
    {
        // Bajar lo mas a la leftHeightuierda posible, apilando el camino.
        while (currentNode != nullptr)
        {
            nodeStack.Push(currentNode);
            currentNode = currentNode->left;
        }
        // Ya no se puede bajar: sacar uno, procesarlo, ir a su rightHeightecha.
        currentNode = nodeStack.Pop();
        resultado.Add(currentNode->data);
        currentNode = currentNode->right;
    }
}

template <class T>
void Tree<T>::PorNiveles(LinkedList<T>& resultado)
{
    // BFS con cola: mismo esquema que el DFS iterativo,
    // pero la cola produce orden por niveles.
    if (_root == nullptr) return;

    LinkedQueue<Node*> nodeQueue;
    nodeQueue.Enqueue(_root);

    while (!nodeQueue.IsEmpty())
    {
        Node* currentNode = nodeQueue.Dequeue();
        resultado.Add(currentNode->data);
        if (currentNode->left != nullptr) nodeQueue.Enqueue(currentNode->left);
        if (currentNode->right != nullptr) nodeQueue.Enqueue(currentNode->right);
    }
}

template <class T>
void Tree<T>::PorNivelesRecursivo(LinkedList<T>& resultado)
{
    // Sin cola: se visita cada nivel por separado.
    // Mas lento porque los nodos de arriba se recorren
    // una vez por cada nivel que hay debajo de ellos.
    int treeHeight = GetAltura();
    for (int nivel = 1; nivel <= treeHeight; nivel++)
    {
        NivelRec(_root, nivel, resultado);
    }
}

template <class T>
void Tree<T>::NivelRec(Node* currentNode, int nivel, LinkedList<T>& resultado)
{
    if (currentNode == nullptr) return;
    if (nivel == 1)
    {
        resultado.Add(currentNode->data);
        return;
    }
    NivelRec(currentNode->left, nivel - 1, resultado);
    NivelRec(currentNode->right, nivel - 1, resultado);
}

template <class T>
void Tree<T>::Print()
{
    // Muestra el arbol en in-orden (sale ordenado en un BST).
    LinkedList<T> recorrido;
    InOrden(recorrido);
    ConsoleUI::PrintTitle("ARBOL (IN-ORDEN)");
    recorrido.Print();
}
