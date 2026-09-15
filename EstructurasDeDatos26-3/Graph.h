#pragma once
#include "Node.h"
#include "Edge.h"
#include "LinkedList.h"
#include "LinkedQueue.h"
#include "ConsoleUI.h"

// =====================================================================
//  Graph<T>  -  Grafo NO dirigido
//
//  EL GRAFO ES EL DUENO DE TODO. El crea los nodos y las aristas, y el
//  las destruye. Ni Node ni Edge liberan nada.
//
//  POR QUE: una arista esta en la lista de vecinos de DOS nodos. Si cada
//  nodo liberara sus propias aristas en su destructor, la arista que
//  conecta A con B se liberaria dos veces: una cuando muere A y otra
//  cuando muere B. Eso es un DOUBLE FREE y tumba el programa, o peor, lo
//  corrompe en silencio.
//
//  Por eso el grafo guarda DOS listas propias: una con todos los nodos y
//  otra con todas las aristas. El destructor recorre esas dos listas y
//  libera cada cosa una sola vez.
//
//  Es el mismo principio por el que hiciste privado el Push(TNode<T>*)
//  de tu Stack: cuando no queda claro quien es dueno de un pedazo de
//  memoria, la estructura contenedora debe serlo, y nadie de afuera
//  puede meter mano.
// =====================================================================

template <class T>
class Graph
{
private:
    LinkedList<Node<T>*> _nodes;
    LinkedList<Edge<T>*> _edges;

    // Auxiliar recursiva del DFS. Recibe el nodo actual porque la
    // recursion necesita avanzar, y desde afuera nadie ve los nodos.
    void DFSRec(Node<T>* n, LinkedList<T>& resultado);

public:
    Graph();
    ~Graph();

    Node<T>* AddNode(T valor);
    void AddEdge(Node<T>* a, Node<T>* b);

    int GetNodeCount();
    int GetEdgeCount();
    void ResetVisited();

    void DFS(LinkedList<T>& resultado);
    void BFS(LinkedList<T>& resultado);
    void Print();
};

template <class T>
Graph<T>::Graph()
{
}

template <class T>
Graph<T>::~Graph()
{
    // El grafo es el unico dueno, aqui se libera todo una sola vez.
    for (int i = 0; i < _edges.GetSize(); i++) // recorro todas las aristas
    {
        delete _edges.GetAt(i); // borro cada arista
    }
    for (int i = 0; i < _nodes.GetSize(); i++) // recorro todos los nodos
    {
        delete _nodes.GetAt(i); // borro cada nodo
    }
}

template <class T>
Node<T>* Graph<T>::AddNode(T valor)
{
    Node<T>* nuevo = new Node<T>(valor); // creo un nodo nuevo con ese valor
    _nodes.Add(nuevo); // lo guardo en mi lista de nodos
    return nuevo; // lo regreso para poder usarlo despues
}

template <class T>
void Graph<T>::AddEdge(Node<T>* a, Node<T>* b)
{
    if (a == nullptr || b == nullptr) // si alguno no existe
    {
        return; // no hago nada y me salgo
    }

    Edge<T>* e = new Edge<T>(a, b); // creo la arista entre a y b
    _edges.Add(e); // la guardo en mi lista de aristas

    // Es no dirigido, la misma arista va en los dos nodos
    a->AddNeighbor(e); // se la agrego al primer nodo
    b->AddNeighbor(e); // se la agrego al segundo nodo
}

template <class T>
int Graph<T>::GetNodeCount()
{
    return _nodes.GetSize(); // regreso cuantos nodos hay
}

template <class T>
int Graph<T>::GetEdgeCount()
{
    return _edges.GetSize(); // regreso cuantas aristas hay
}

template <class T>
void Graph<T>::ResetVisited()
{
    for (int i = 0; i < _nodes.GetSize(); i++) // recorro todos los nodos
    {
        _nodes.GetAt(i)->SetVisited(false); // los marco como no visitados
    }
    for (int i = 0; i < _edges.GetSize(); i++) // recorro todas las aristas
    {
        _edges.GetAt(i)->SetVisited(false); // las marco como no visitadas
    }
}

template <class T>
void Graph<T>::DFS(LinkedList<T>& resultado)
{
    ResetVisited(); // limpio las marcas para empezar de cero

    for (int i = 0; i < _nodes.GetSize(); i++) // recorro todos los nodos
    {
        Node<T>* n = _nodes.GetAt(i); // agarro el nodo de esta posicion
        if (!n->GetVisited()) // si todavia no lo visite
        {
            DFSRec(n, resultado); // empiezo a explorar desde ahi
        }
    }
}

template <class T>
void Graph<T>::DFSRec(Node<T>* n, LinkedList<T>& resultado)
{
    if (n == nullptr) // si me pasaron un nodo vacio
    {
        return; // no hago nada
    }

    n->SetVisited(true); // marco este nodo como visitado
    resultado.Add(n->GetValue()); // agrego su valor al resultado

    for (int i = 0; i < n->GetNeighborCount(); i++) // reviso todos sus vecinos
    {
        Edge<T>* e = n->GetNeighbor(i); // agarro la arista de esta posicion

        // Ver cual es el otro extremo
        Node<T>* otro = e->GetFrom(); // supongo que el otro es el origen
        if (otro == n) // si el origen soy yo
        {
            otro = e->GetTo(); // entonces el otro es el destino
        }

        if (otro != nullptr && !otro->GetVisited()) // si existe y no lo visite
        {
            DFSRec(otro, resultado); // me voy para alla
        }
    }
}

template <class T>
void Graph<T>::BFS(LinkedList<T>& resultado)
{
    ResetVisited(); // limpio las marcas para empezar de cero

    LinkedQueue<Node<T>*> cola; // aqui guardo los que faltan por revisar

    for (int i = 0; i < _nodes.GetSize(); i++) // recorro todos los nodos
    {
        Node<T>* inicio = _nodes.GetAt(i); // agarro el nodo de esta posicion

        if (inicio->GetVisited()) // si ya lo visite
        {
            continue; // me brinco al siguiente
        }

        inicio->SetVisited(true); // lo marco como visitado
        cola.Enqueue(inicio); // lo meto a la cola

        while (!cola.IsEmpty()) // mientras haya algo en la cola
        {
            Node<T>* actual = cola.Dequeue(); // saco el primero
            resultado.Add(actual->GetValue()); // agrego su valor al resultado

            for (int j = 0; j < actual->GetNeighborCount(); j++) // reviso sus vecinos
            {
                Edge<T>* e = actual->GetNeighbor(j); // agarro la arista

                Node<T>* vecino = e->GetFrom(); // supongo que el vecino es el origen
                if (vecino == actual) // si el origen soy yo
                {
                    vecino = e->GetTo(); // entonces el vecino es el destino
                }

                if (vecino != nullptr && !vecino->GetVisited()) // si existe y no lo visite
                {
                    vecino->SetVisited(true); // lo marco de una vez
                    cola.Enqueue(vecino); // lo meto a la cola para revisarlo luego
                }
            }
        }
    }
}

template <class T>
void Graph<T>::Print()
{
    ConsoleUI::PrintTitle("GRAFO"); // pongo el titulo

    for (int i = 0; i < _nodes.GetSize(); i++) // recorro todos los nodos
    {
        Node<T>* n = _nodes.GetAt(i); // agarro el nodo
        std::cout << n->GetValue() << " -> "; // imprimo su valor

        for (int j = 0; j < n->GetNeighborCount(); j++) // recorro sus vecinos
        {
            Edge<T>* e = n->GetNeighbor(j); // agarro la arista
            Node<T>* otro = e->GetFrom(); // supongo que el otro es el origen
            if (otro == n) // si soy yo
            {
                otro = e->GetTo(); // el otro es el destino
            }
            std::cout << otro->GetValue() << " "; // imprimo el valor del vecino
        }
        std::cout << std::endl; // salto de linea para el siguiente nodo
    }
}
