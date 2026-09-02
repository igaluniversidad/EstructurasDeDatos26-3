// =====================================================================
//  Tests_Graph.cpp  -  Pruebas de Graph, recorridos y ordenamientos
//  Estructuras de Datos (GPD4402) - SAE Institute Mexico
// =====================================================================
//
//  OJO: este archivo NO lleva DOCTEST_CONFIG_IMPLEMENT.
//  Ese define ya vive en Tests.cpp y solo puede estar en UN archivo.
//
//  Grupos nuevos: "Graph", "GraphRecorridos", "Ordenamientos"
//
//  NO modifiques este archivo. Es el contrato.
//
// =====================================================================

#include "doctest.h"

#include "Edge.h"
#include "Node.h"
#include "Graph.h"
#include "Sorts.h"
#include "LinkedList.h"

#include <string>


// =====================================================================
//  SUITE: Graph
// =====================================================================
TEST_SUITE("Graph")
{
    TEST_CASE("Un grafo recien creado esta vacio")
    {
        Graph<int> g;
        CHECK(g.GetNodeCount() == 0);
        CHECK(g.GetEdgeCount() == 0);
    }

    TEST_CASE("AddNode agrega el nodo y regresa un puntero valido")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(10);

        CHECK(a != nullptr);
        CHECK(a->GetValue() == 10);
        CHECK(g.GetNodeCount() == 1);
    }

    TEST_CASE("Una arista recien creada NO apunta a ningun nodo")
    {
        // Si el constructor por defecto hace 'new Node', cada arista vacia
        // deja dos nodos huerfanos en el heap que nadie libera nunca.
        Edge<int> e;
        CHECK(e.GetFrom() == nullptr);
        CHECK(e.GetTo() == nullptr);
        CHECK(e.GetVisited() == false);
    }

    TEST_CASE("El constructor de Edge NO invierte los extremos")
    {
        // Edge(from, to): 'from' va en _from y 'to' va en _to.
        // Invertirlos es un error clasico que en un grafo no dirigido
        // se esconde, porque los recorridos revisan los dos extremos.
        Node<int> a(1);
        Node<int> b(2);
        Edge<int> e(&a, &b);

        CHECK(e.GetFrom() == &a);
        CHECK(e.GetTo() == &b);
        CHECK(e.GetFrom()->GetValue() == 1);
        CHECK(e.GetTo()->GetValue() == 2);
    }

    TEST_CASE("AddEdge crea la arista y la registra en el grafo")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        g.AddEdge(a, b);

        CHECK(g.GetEdgeCount() == 1);
        CHECK(g.GetNodeCount() == 2);
    }

    TEST_CASE("En un grafo no dirigido, la arista aparece en AMBOS nodos")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        g.AddEdge(a, b);

        CHECK(a->GetNeighborCount() == 1);
        CHECK(b->GetNeighborCount() == 1);
    }

    TEST_CASE("Los dos nodos comparten LA MISMA arista, no una copia")
    {
        // Por eso la lista de vecinos guarda punteros. Si guardara copias,
        // marcar una como visitada no afectaria a la otra.
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        g.AddEdge(a, b);

        CHECK(a->GetNeighbor(0) == b->GetNeighbor(0));
    }

    TEST_CASE("Un nodo puede tener varias aristas")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        Node<int>* c = g.AddNode(3);
        g.AddEdge(a, b);
        g.AddEdge(a, c);

        CHECK(a->GetNeighborCount() == 2);
        CHECK(b->GetNeighborCount() == 1);
        CHECK(c->GetNeighborCount() == 1);
        CHECK(g.GetEdgeCount() == 2);
    }

    TEST_CASE("ResetVisited deja todos los nodos sin visitar")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        a->SetVisited(true);
        b->SetVisited(true);

        g.ResetVisited();

        CHECK(a->GetVisited() == false);
        CHECK(b->GetVisited() == false);
    }

    TEST_CASE("AddEdge con un nodo nulo no truena")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        g.AddEdge(a, nullptr);
        CHECK(true);   // si llegamos hasta aqui, no exploto
    }

    TEST_CASE("El grafo funciona con cualquier tipo de dato")
    {
        Graph<std::string> g;
        Node<std::string>* a = g.AddNode("inicio");
        Node<std::string>* b = g.AddNode("final");
        g.AddEdge(a, b);

        CHECK(a->GetValue() == "inicio");
        CHECK(g.GetEdgeCount() == 1);
    }
}


// =====================================================================
//  SUITE: GraphRecorridos
//
//  Casi todas las pruebas usan este grafo (una estrella con una rama):
//
//              1
//            / | \
//           2  3  4
//           |
//           5
//
//  Nodos agregados en orden:   1, 2, 3, 4, 5
//  Aristas agregadas en orden: 1-2, 1-3, 1-4, 2-5
//
//  Al no tener ciclos, el orden de ambos recorridos es predecible.
// =====================================================================
TEST_SUITE("GraphRecorridos")
{
    TEST_CASE("DFS recorre en profundidad: se clava en una rama antes de volver")
    {
        Graph<int> g;
        Node<int>* n1 = g.AddNode(1);
        Node<int>* n2 = g.AddNode(2);
        Node<int>* n3 = g.AddNode(3);
        Node<int>* n4 = g.AddNode(4);
        Node<int>* n5 = g.AddNode(5);
        g.AddEdge(n1, n2);
        g.AddEdge(n1, n3);
        g.AddEdge(n1, n4);
        g.AddEdge(n2, n5);

        LinkedList<int> r;
        g.DFS(r);

        CHECK(r.GetSize() == 5);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);
        CHECK(r.GetAt(2) == 5);   // baja hasta el fondo de la rama de 2
        CHECK(r.GetAt(3) == 3);   // y HASTA ENTONCES regresa por los otros
        CHECK(r.GetAt(4) == 4);
    }

    TEST_CASE("BFS recorre en anchura: primero todos los vecinos directos")
    {
        Graph<int> g;
        Node<int>* n1 = g.AddNode(1);
        Node<int>* n2 = g.AddNode(2);
        Node<int>* n3 = g.AddNode(3);
        Node<int>* n4 = g.AddNode(4);
        Node<int>* n5 = g.AddNode(5);
        g.AddEdge(n1, n2);
        g.AddEdge(n1, n3);
        g.AddEdge(n1, n4);
        g.AddEdge(n2, n5);

        LinkedList<int> r;
        g.BFS(r);

        CHECK(r.GetSize() == 5);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);   // los tres vecinos de 1 primero
        CHECK(r.GetAt(2) == 3);
        CHECK(r.GetAt(3) == 4);
        CHECK(r.GetAt(4) == 5);   // y hasta el final el nieto
    }

    TEST_CASE("Correr el mismo recorrido dos veces da el mismo resultado")
    {
        // Si no llamas a ResetVisited() al inicio, la segunda corrida
        // regresa vacia. Es el mismo error del Flood Fill.
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        g.AddEdge(a, b);

        LinkedList<int> primera;
        LinkedList<int> segunda;
        g.DFS(primera);
        g.DFS(segunda);

        CHECK(primera.GetSize() == 2);
        CHECK(segunda.GetSize() == 2);
        CHECK(segunda.GetAt(0) == primera.GetAt(0));
        CHECK(segunda.GetAt(1) == primera.GetAt(1));
    }

    TEST_CASE("DFS y BFS se pueden correr uno despues del otro")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        g.AddEdge(a, b);

        LinkedList<int> conDFS;
        LinkedList<int> conBFS;
        g.DFS(conDFS);
        g.BFS(conBFS);

        CHECK(conDFS.GetSize() == 2);
        CHECK(conBFS.GetSize() == 2);
    }

    TEST_CASE("Un grafo con CICLO no provoca un recorrido infinito")
    {
        // Triangulo: 1-2, 2-3, 3-1. Sin la marca de visitado,
        // el recorrido se cicla para siempre y el programa se congela.
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        Node<int>* c = g.AddNode(3);
        g.AddEdge(a, b);
        g.AddEdge(b, c);
        g.AddEdge(c, a);

        LinkedList<int> r;
        g.DFS(r);

        CHECK(r.GetSize() == 3);   // cada nodo UNA sola vez
    }

    TEST_CASE("BFS tampoco se cicla ni repite nodos")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        Node<int>* c = g.AddNode(3);
        g.AddEdge(a, b);
        g.AddEdge(b, c);
        g.AddEdge(c, a);

        LinkedList<int> r;
        g.BFS(r);

        CHECK(r.GetSize() == 3);
    }

    TEST_CASE("DFS visita TODOS los nodos aunque el grafo este desconectado")
    {
        // Dos islas: 1-2 por un lado, 3-4 por el otro.
        // Un recorrido que solo arranque desde el primer nodo se queda
        // con la mitad del grafo.
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        Node<int>* c = g.AddNode(3);
        Node<int>* d = g.AddNode(4);
        g.AddEdge(a, b);
        g.AddEdge(c, d);

        LinkedList<int> r;
        g.DFS(r);

        CHECK(r.GetSize() == 4);
        CHECK(r.GetAt(0) == 1);
        CHECK(r.GetAt(1) == 2);
        CHECK(r.GetAt(2) == 3);
        CHECK(r.GetAt(3) == 4);
    }

    TEST_CASE("BFS visita TODOS los nodos aunque el grafo este desconectado")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        Node<int>* c = g.AddNode(3);
        Node<int>* d = g.AddNode(4);
        g.AddEdge(a, b);
        g.AddEdge(c, d);

        LinkedList<int> r;
        g.BFS(r);

        CHECK(r.GetSize() == 4);
    }

    TEST_CASE("Un nodo suelto, sin ninguna arista, tambien se visita")
    {
        Graph<int> g;
        Node<int>* a = g.AddNode(1);
        Node<int>* b = g.AddNode(2);
        g.AddEdge(a, b);
        g.AddNode(99);            // aislado, sin conexiones

        LinkedList<int> r;
        g.DFS(r);

        CHECK(r.GetSize() == 3);
        CHECK(r.GetAt(2) == 99);
    }

    TEST_CASE("Los recorridos sobre un grafo vacio no truenan")
    {
        Graph<int> g;
        LinkedList<int> r;
        g.DFS(r);
        g.BFS(r);
        CHECK(r.GetSize() == 0);
    }

    TEST_CASE("Los recorridos funcionan con un solo nodo")
    {
        Graph<int> g;
        g.AddNode(42);

        LinkedList<int> r;
        g.DFS(r);

        CHECK(r.GetSize() == 1);
        CHECK(r.GetAt(0) == 42);
    }
}


// =====================================================================
//  SUITE: Ordenamientos
// =====================================================================
TEST_SUITE("Ordenamientos")
{
    TEST_CASE("MergeSort ordena de menor a mayor")
    {
        int a[6] = { 5, 2, 8, 1, 9, 3 };
        MergeSort(a, 6);

        CHECK(a[0] == 1);
        CHECK(a[1] == 2);
        CHECK(a[2] == 3);
        CHECK(a[3] == 5);
        CHECK(a[4] == 8);
        CHECK(a[5] == 9);
    }

    TEST_CASE("QuickSort ordena de menor a mayor")
    {
        int a[6] = { 5, 2, 8, 1, 9, 3 };
        QuickSort(a, 6);

        CHECK(a[0] == 1);
        CHECK(a[1] == 2);
        CHECK(a[2] == 3);
        CHECK(a[3] == 5);
        CHECK(a[4] == 8);
        CHECK(a[5] == 9);
    }

    TEST_CASE("Ordenar un arreglo que YA estaba ordenado no lo descompone")
    {
        int a[5] = { 1, 2, 3, 4, 5 };
        int b[5] = { 1, 2, 3, 4, 5 };
        MergeSort(a, 5);
        QuickSort(b, 5);

        for (int i = 0; i < 5; i++)
        {
            CHECK(a[i] == i + 1);
            CHECK(b[i] == i + 1);
        }
    }

    TEST_CASE("Ordenar un arreglo en orden INVERSO")
    {
        int a[5] = { 5, 4, 3, 2, 1 };
        int b[5] = { 5, 4, 3, 2, 1 };
        MergeSort(a, 5);
        QuickSort(b, 5);

        for (int i = 0; i < 5; i++)
        {
            CHECK(a[i] == i + 1);
            CHECK(b[i] == i + 1);
        }
    }

    TEST_CASE("Los ordenamientos conservan los elementos repetidos")
    {
        // Ordenar no debe perder ni inventar elementos.
        int a[7] = { 3, 1, 3, 2, 1, 3, 2 };
        MergeSort(a, 7);

        CHECK(a[0] == 1);
        CHECK(a[1] == 1);
        CHECK(a[2] == 2);
        CHECK(a[3] == 2);
        CHECK(a[4] == 3);
        CHECK(a[5] == 3);
        CHECK(a[6] == 3);
    }

    TEST_CASE("QuickSort tambien conserva los repetidos")
    {
        int a[7] = { 3, 1, 3, 2, 1, 3, 2 };
        QuickSort(a, 7);

        CHECK(a[0] == 1);
        CHECK(a[1] == 1);
        CHECK(a[2] == 2);
        CHECK(a[3] == 2);
        CHECK(a[4] == 3);
        CHECK(a[5] == 3);
        CHECK(a[6] == 3);
    }

    TEST_CASE("Un arreglo de un solo elemento no truena")
    {
        int a[1] = { 42 };
        int b[1] = { 42 };
        MergeSort(a, 1);
        QuickSort(b, 1);

        CHECK(a[0] == 42);
        CHECK(b[0] == 42);
    }

    TEST_CASE("Un arreglo de dos elementos se ordena bien")
    {
        int a[2] = { 2, 1 };
        int b[2] = { 2, 1 };
        MergeSort(a, 2);
        QuickSort(b, 2);

        CHECK(a[0] == 1); CHECK(a[1] == 2);
        CHECK(b[0] == 1); CHECK(b[1] == 2);
    }

    TEST_CASE("Un arreglo vacio no truena")
    {
        int a[1] = { 0 };
        MergeSort(a, 0);
        QuickSort(a, 0);
        CHECK(true);
    }

    TEST_CASE("Los ordenamientos sirven para cualquier tipo, no solo int")
    {
        // Por eso son funciones libres con template y no metodos de una
        // clase: no necesitan saber nada de la estructura, solo comparar.
        char a[5] = { 'd', 'a', 'e', 'b', 'c' };
        MergeSort(a, 5);

        CHECK(a[0] == 'a');
        CHECK(a[1] == 'b');
        CHECK(a[2] == 'c');
        CHECK(a[3] == 'd');
        CHECK(a[4] == 'e');
    }

    TEST_CASE("QuickSort tambien es generico")
    {
        std::string a[3] = { "zorro", "abeja", "mono" };
        QuickSort(a, 3);

        CHECK(a[0] == "abeja");
        CHECK(a[1] == "mono");
        CHECK(a[2] == "zorro");
    }

    TEST_CASE("Aguanta un arreglo grande sin perder el orden")
    {
        const int N = 200;
        int a[N];
        for (int i = 0; i < N; i++) a[i] = (i * 37) % N;   // desordenado

        MergeSort(a, N);

        bool ordenado = true;
        for (int i = 1; i < N; i++) if (a[i - 1] > a[i]) ordenado = false;
        CHECK(ordenado == true);
    }
}
