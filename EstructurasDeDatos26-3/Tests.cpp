// =====================================================================
//  Tests.cpp  -  Pruebas unitarias de la libreria
//  Estructuras de Datos (GPD4402) - SAE Institute Mexico
// =====================================================================
//
//  QUE ES ESTO:
//  Este archivo contiene codigo que ejecuta TU codigo y verifica que
//  haga lo que debe hacer. En lugar de correr el programa a mano, meter
//  numeros y revisar con los ojos si funciono, estas pruebas lo hacen
//  por ti y te dicen "paso" o "fallo".
//
//  ESTAS PRUEBAS SON EL CONTRATO.
//  Si tu implementacion pasa todas las pruebas, tu implementacion es
//  correcta. Si no pasa, algo falta. NO modifiques este archivo para
//  que tus pruebas pasen: modifica tu codigo hasta que las pruebas
//  pasen. Cambiar el examen para aprobarlo no cuenta.
//
//  Al principio TODAS van a fallar. Eso es normal y es el punto de
//  partida: se les llama "rojo". Tu trabajo es ponerlas en "verde".
//
// =====================================================================

#define DOCTEST_CONFIG_IMPLEMENT   // OJO: sin _WITH_MAIN. Ver la guia.
#include "doctest.h"

#include "TNode.h"
#include "Stack.h"
#include "LinkedQueue.h"
#include "TwoStackQueue.h"
#include "LinkedList.h"
#include "Grid.h"


// =====================================================================
//  SUITE: Stack
// =====================================================================
TEST_SUITE("Stack")
{
    TEST_CASE("Una pila recien creada esta vacia")
    {
        Stack<int> s;
        CHECK(s.IsEmpty() == true);
        CHECK(s.GetSize() == 0);
    }

    TEST_CASE("Push aumenta el tamanio y deja de estar vacia")
    {
        Stack<int> s;
        s.Push(10);
        CHECK(s.IsEmpty() == false);
        CHECK(s.GetSize() == 1);

        s.Push(20);
        CHECK(s.GetSize() == 2);
    }

    TEST_CASE("La pila respeta el orden LIFO: el ultimo en entrar es el primero en salir")
    {
        Stack<int> s;
        s.Push(1);
        s.Push(2);
        s.Push(3);

        CHECK(s.Pop() == 3);
        CHECK(s.Pop() == 2);
        CHECK(s.Pop() == 1);
        CHECK(s.IsEmpty() == true);
    }

    TEST_CASE("Top regresa el tope SIN quitarlo")
    {
        Stack<int> s;
        s.Push(7);
        s.Push(9);

        CHECK(s.Top() == 9);
        CHECK(s.GetSize() == 2);   // Top NO debe modificar la pila
        CHECK(s.Top() == 9);       // llamarlo dos veces da lo mismo
    }

    TEST_CASE("Pop reduce el tamanio")
    {
        Stack<int> s;
        s.Push(1);
        s.Push(2);
        s.Pop();
        CHECK(s.GetSize() == 1);
    }

    TEST_CASE("Clear deja la pila vacia")
    {
        Stack<int> s;
        s.Push(1);
        s.Push(2);
        s.Push(3);
        s.Clear();

        CHECK(s.IsEmpty() == true);
        CHECK(s.GetSize() == 0);
    }

    TEST_CASE("Se puede volver a usar la pila despues de vaciarla")
    {
        Stack<int> s;
        s.Push(1);
        s.Pop();              // aqui queda vacia
        s.Push(2);            // esto truena si dejaste punteros colgando
        CHECK(s.Top() == 2);
        CHECK(s.GetSize() == 1);
    }

    TEST_CASE("La pila funciona con cualquier tipo, no solo con int")
    {
        Stack<char> s;
        s.Push('a');
        s.Push('b');
        CHECK(s.Pop() == 'b');
        CHECK(s.Pop() == 'a');
    }
}


// =====================================================================
//  SUITE: ReglaDeTres
//  Estas son las pruebas que revientan si copias de forma superficial.
// =====================================================================
TEST_SUITE("ReglaDeTres")
{
    TEST_CASE("El constructor de copia hace una copia PROFUNDA")
    {
        Stack<int> a;
        a.Push(1);
        a.Push(2);

        Stack<int> b = a;   // constructor de copia

        b.Pop();            // modificar 'b' NO debe afectar a 'a'

        CHECK(a.GetSize() == 2);
        CHECK(b.GetSize() == 1);
        CHECK(a.Top() == 2);
    }

    TEST_CASE("La copia conserva el mismo contenido y el mismo orden")
    {
        Stack<int> a;
        a.Push(1);
        a.Push(2);
        a.Push(3);

        Stack<int> b = a;

        CHECK(b.Pop() == 3);
        CHECK(b.Pop() == 2);
        CHECK(b.Pop() == 1);
    }

    TEST_CASE("El operador = hace una copia PROFUNDA")
    {
        Stack<int> a;
        a.Push(10);
        a.Push(20);

        Stack<int> b;
        b.Push(99);

        b = a;              // operator=

        CHECK(b.GetSize() == 2);
        CHECK(b.Top() == 20);

        b.Pop();
        CHECK(a.GetSize() == 2);   // 'a' sigue intacta
    }

    TEST_CASE("La autoasignacion no destruye la pila")
    {
        Stack<int> a;
        a.Push(1);
        a.Push(2);

        a = a;              // si liberas antes de copiar, aqui te quedas sin nada

        CHECK(a.GetSize() == 2);
        CHECK(a.Top() == 2);
    }
}


// =====================================================================
//  SUITE: Queue
//
//  OJO CON ESTO: las pruebas estan escritas UNA SOLA VEZ, en una
//  funcion con template, y se corren contra las DOS implementaciones.
//  Si ambas pasan exactamente las mismas pruebas, significa que ambas
//  cumplen el mismo contrato aunque por dentro sean muy distintas.
//  Eso es lo que significa "respetar una interfaz".
// =====================================================================
template <class TCola>
void PruebasDeCola()
{
    SUBCASE("Una cola recien creada esta vacia")
    {
        TCola q;
        CHECK(q.IsEmpty() == true);
        CHECK(q.GetSize() == 0);
    }

    SUBCASE("Enqueue aumenta el tamanio")
    {
        TCola q;
        q.Enqueue(10);
        CHECK(q.IsEmpty() == false);
        CHECK(q.GetSize() == 1);
        q.Enqueue(20);
        CHECK(q.GetSize() == 2);
    }

    SUBCASE("La cola respeta el orden FIFO: el primero en entrar es el primero en salir")
    {
        TCola q;
        q.Enqueue(1);
        q.Enqueue(2);
        q.Enqueue(3);

        CHECK(q.Dequeue() == 1);
        CHECK(q.Dequeue() == 2);
        CHECK(q.Dequeue() == 3);
        CHECK(q.IsEmpty() == true);
    }

    SUBCASE("Front regresa el frente SIN quitarlo")
    {
        TCola q;
        q.Enqueue(5);
        q.Enqueue(6);

        CHECK(q.Front() == 5);
        CHECK(q.GetSize() == 2);
        CHECK(q.Front() == 5);
    }

    SUBCASE("Encolar despues de vaciar la cola NO truena")
    {
        // Este es EL bug clasico de las colas.
        // Al sacar el ultimo elemento, _first queda en nullptr pero
        // _last se queda apuntando a memoria que ya liberaste.
        // El siguiente Enqueue escribe sobre un nodo muerto.
        TCola q;
        q.Enqueue(1);
        q.Dequeue();          // la cola queda vacia
        q.Enqueue(2);         // aqui revienta si el bug esta presente

        CHECK(q.Front() == 2);
        CHECK(q.GetSize() == 1);
    }

    SUBCASE("Intercalar Enqueue y Dequeue mantiene el orden")
    {
        TCola q;
        q.Enqueue(1);
        q.Enqueue(2);
        CHECK(q.Dequeue() == 1);

        q.Enqueue(3);
        CHECK(q.Dequeue() == 2);
        CHECK(q.Dequeue() == 3);
        CHECK(q.IsEmpty() == true);
    }

    SUBCASE("Clear deja la cola vacia")
    {
        TCola q;
        q.Enqueue(1);
        q.Enqueue(2);
        q.Clear();
        CHECK(q.IsEmpty() == true);
        CHECK(q.GetSize() == 0);
    }

    SUBCASE("Aguanta muchos elementos sin perder el orden")
    {
        TCola q;
        for (int i = 0; i < 50; i++) q.Enqueue(i);
        CHECK(q.GetSize() == 50);
        for (int i = 0; i < 50; i++) CHECK(q.Dequeue() == i);
        CHECK(q.IsEmpty() == true);
    }
}

TEST_SUITE("Queue")
{
    TEST_CASE("LinkedQueue cumple el contrato de una cola")
    {
        PruebasDeCola< LinkedQueue<int> >();
    }

    TEST_CASE("TwoStackQueue cumple el MISMO contrato de una cola")
    {
        PruebasDeCola< TwoStackQueue<int> >();
    }
}


// =====================================================================
//  SUITE: LinkedList
// =====================================================================
TEST_SUITE("LinkedList")
{
    TEST_CASE("Una lista recien creada esta vacia")
    {
        LinkedList<int> lista;
        CHECK(lista.GetSize() == 0);
    }

    TEST_CASE("Add agrega al final y en orden")
    {
        LinkedList<int> lista;
        lista.Add(10);
        lista.Add(20);
        lista.Add(30);

        CHECK(lista.GetSize() == 3);
        CHECK(lista.GetAt(0) == 10);
        CHECK(lista.GetAt(1) == 20);
        CHECK(lista.GetAt(2) == 30);
    }

    TEST_CASE("Add funciona igual en lista vacia que en lista con elementos")
    {
        LinkedList<int> lista;
        lista.Add(1);                  // primer elemento: caso especial
        CHECK(lista.GetSize() == 1);
        CHECK(lista.GetAt(0) == 1);

        lista.Add(2);                  // segundo elemento: caso normal
        CHECK(lista.GetAt(1) == 2);
    }

    TEST_CASE("operator[] permite LEER igual que GetAt")
    {
        LinkedList<int> lista;
        lista.Add(10);
        lista.Add(20);

        CHECK(lista[0] == 10);
        CHECK(lista[1] == 20);
    }

    TEST_CASE("operator[] regresa una REFERENCIA, asi que permite ESCRIBIR")
    {
        // Esta prueba solo compila si operator[] regresa T& y no T.
        // Si regresa una copia, el compilador marca error aqui.
        LinkedList<int> lista;
        lista.Add(10);
        lista.Add(20);

        lista[0] = 99;

        CHECK(lista[0] == 99);
        CHECK(lista.GetAt(0) == 99);   // el cambio es real, no sobre una copia
        CHECK(lista[1] == 20);         // no toco a los vecinos
    }

    TEST_CASE("SelectionSort ordena de menor a mayor")
    {
        LinkedList<int> lista;
        lista.Add(3);
        lista.Add(1);
        lista.Add(2);

        lista.SelectionSort();

        CHECK(lista.GetAt(0) == 1);
        CHECK(lista.GetAt(1) == 2);
        CHECK(lista.GetAt(2) == 3);
        CHECK(lista.GetSize() == 3);   // ordenar no pierde ni inventa elementos
    }

    TEST_CASE("InsertionSort ordena de menor a mayor")
    {
        LinkedList<int> lista;
        lista.Add(5);
        lista.Add(2);
        lista.Add(8);
        lista.Add(1);

        lista.InsertionSort();

        CHECK(lista.GetAt(0) == 1);
        CHECK(lista.GetAt(1) == 2);
        CHECK(lista.GetAt(2) == 5);
        CHECK(lista.GetAt(3) == 8);
        CHECK(lista.GetSize() == 4);
    }

    TEST_CASE("Ordenar una lista que ya estaba ordenada no la descompone")
    {
        LinkedList<int> lista;
        lista.Add(1);
        lista.Add(2);
        lista.Add(3);

        lista.SelectionSort();

        CHECK(lista.GetAt(0) == 1);
        CHECK(lista.GetAt(2) == 3);
    }

    TEST_CASE("Ordenar una lista de un solo elemento no truena")
    {
        LinkedList<int> lista;
        lista.Add(42);
        lista.SelectionSort();
        lista.InsertionSort();
        CHECK(lista.GetAt(0) == 42);
    }
}


// =====================================================================
//  SUITE: Recursividad
// =====================================================================
TEST_SUITE("Recursividad")
{
    TEST_CASE("GetAtRecursivo regresa lo mismo que GetAt")
    {
        LinkedList<int> lista;
        lista.Add(10);
        lista.Add(20);
        lista.Add(30);

        CHECK(lista.GetAtRecursivo(0) == lista.GetAt(0));
        CHECK(lista.GetAtRecursivo(1) == lista.GetAt(1));
        CHECK(lista.GetAtRecursivo(2) == lista.GetAt(2));
    }

    TEST_CASE("CountRecursivo regresa lo mismo que GetSize")
    {
        LinkedList<int> lista;
        CHECK(lista.CountRecursivo() == 0);   // caso base: lista vacia

        lista.Add(1);
        lista.Add(2);
        lista.Add(3);

        CHECK(lista.CountRecursivo() == 3);
        CHECK(lista.CountRecursivo() == lista.GetSize());
    }

    TEST_CASE("BuscarRecursivo encuentra el elemento y regresa su indice")
    {
        LinkedList<int> lista;
        lista.Add(10);
        lista.Add(20);
        lista.Add(30);

        CHECK(lista.BuscarRecursivo(10) == 0);
        CHECK(lista.BuscarRecursivo(20) == 1);
        CHECK(lista.BuscarRecursivo(30) == 2);
    }

    TEST_CASE("BuscarRecursivo regresa -1 cuando el elemento no existe")
    {
        LinkedList<int> lista;
        lista.Add(10);
        lista.Add(20);

        CHECK(lista.BuscarRecursivo(99) == -1);
    }

    TEST_CASE("BuscarRecursivo en una lista vacia regresa -1")
    {
        LinkedList<int> lista;
        CHECK(lista.BuscarRecursivo(1) == -1);
    }

    // NOTA SOBRE PrintReverse:
    // No hay prueba automatica de PrintReverse, y la razon es
    // interesante: esa funcion no REGRESA nada, IMPRIME. Una prueba
    // solo puede verificar valores que le regresan, no lo que salio en
    // la consola.
    //
    // Leccion: las funciones que calculan y regresan son faciles de
    // probar; las que imprimen no lo son. Por eso conviene separar el
    // calculo de la presentacion (que es exactamente el motivo por el
    // que existe ConsoleUI).
    //
    // PrintReverse se revisa a ojo y en la defensa oral.
}


// =====================================================================
//  SUITE: Grid
// =====================================================================
TEST_SUITE("Grid")
{
    TEST_CASE("El grid guarda y regresa lo que le pusiste")
    {
        Grid<int> g(3, 3);
        g.Set(0, 0, 5);
        g.Set(2, 2, 9);

        CHECK(g.Get(0, 0) == 5);
        CHECK(g.Get(2, 2) == 9);
        CHECK(g.GetFilas() == 3);
        CHECK(g.GetColumnas() == 3);
    }

    TEST_CASE("El grid no truena con coordenadas fuera de rango")
    {
        Grid<int> g(3, 3);
        g.Set(-1, 0, 5);      // no debe caerse
        g.Set(0, 99, 5);      // no debe caerse
        g.Get(99, 99);        // no debe caerse
        CHECK(true);          // si llegamos hasta aqui, no exploto
    }

    TEST_CASE("FloodFill de una celda aislada cuenta 1")
    {
        //   1 2 2
        //   2 2 2
        //   2 2 2
        Grid<int> g(3, 3);
        for (int f = 0; f < 3; f++)
            for (int c = 0; c < 3; c++)
                g.Set(f, c, 2);
        g.Set(0, 0, 1);

        CHECK(g.FloodFill(0, 0) == 1);
    }

    TEST_CASE("FloodFill cuenta un grupo conectado en linea")
    {
        //   1 1 1
        //   2 2 2
        //   2 2 2
        Grid<int> g(3, 3);
        for (int f = 0; f < 3; f++)
            for (int c = 0; c < 3; c++)
                g.Set(f, c, 2);
        g.Set(0, 0, 1);
        g.Set(0, 1, 1);
        g.Set(0, 2, 1);

        CHECK(g.FloodFill(0, 0) == 3);
        CHECK(g.FloodFill(0, 1) == 3);   // empezar desde en medio da lo mismo
    }

    TEST_CASE("FloodFill cuenta un grupo con forma de L")
    {
        //   1 2 2
        //   1 2 2
        //   1 1 2
        Grid<int> g(3, 3);
        for (int f = 0; f < 3; f++)
            for (int c = 0; c < 3; c++)
                g.Set(f, c, 2);
        g.Set(0, 0, 1);
        g.Set(1, 0, 1);
        g.Set(2, 0, 1);
        g.Set(2, 1, 1);

        CHECK(g.FloodFill(0, 0) == 4);
    }

    TEST_CASE("FloodFill NO cuenta las diagonales")
    {
        //   1 2 2
        //   2 1 2      las dos celdas con 1 se tocan solo en diagonal:
        //   2 2 2      NO son vecinas
        Grid<int> g(3, 3);
        for (int f = 0; f < 3; f++)
            for (int c = 0; c < 3; c++)
                g.Set(f, c, 2);
        g.Set(0, 0, 1);
        g.Set(1, 1, 1);

        CHECK(g.FloodFill(0, 0) == 1);
    }

    TEST_CASE("FloodFill sobre un tablero de un solo valor cuenta todo")
    {
        Grid<int> g(4, 4);
        for (int f = 0; f < 4; f++)
            for (int c = 0; c < 4; c++)
                g.Set(f, c, 7);

        CHECK(g.FloodFill(0, 0) == 16);
    }

    TEST_CASE("Se puede correr FloodFill dos veces seguidas")
    {
        // Si no reinicias las celdas visitadas, la segunda corrida da 0.
        Grid<int> g(3, 3);
        for (int f = 0; f < 3; f++)
            for (int c = 0; c < 3; c++)
                g.Set(f, c, 4);

        CHECK(g.FloodFill(0, 0) == 9);
        CHECK(g.FloodFill(0, 0) == 9);   // misma respuesta la segunda vez
    }
}


// =====================================================================
//  SUITE: Memoria
//
//  Estas pruebas verifican que no dejes nodos sin liberar.
//  Funcionan gracias a un contador estatico dentro de TNode que sube
//  con cada constructor y baja con cada destructor. Si al final del
//  scope el contador no regreso a cero, quedaron nodos vivos: fuga.
// =====================================================================
TEST_SUITE("Memoria")
{
    TEST_CASE("El destructor del Stack libera TODOS los nodos")
    {
        TNode<int>::contadorVivos = 0;
        {
            Stack<int> s;
            s.Push(1);
            s.Push(2);
            s.Push(3);
            CHECK(TNode<int>::contadorVivos == 3);
        }   // aqui se destruye 's'
        CHECK(TNode<int>::contadorVivos == 0);
    }

    TEST_CASE("Pop libera el nodo que saca")
    {
        TNode<int>::contadorVivos = 0;
        {
            Stack<int> s;
            s.Push(1);
            s.Push(2);
            s.Pop();
            CHECK(TNode<int>::contadorVivos == 1);
        }
        CHECK(TNode<int>::contadorVivos == 0);
    }

    TEST_CASE("Clear del Stack libera todos los nodos")
    {
        TNode<int>::contadorVivos = 0;
        Stack<int> s;
        s.Push(1);
        s.Push(2);
        s.Clear();
        CHECK(TNode<int>::contadorVivos == 0);
    }

    TEST_CASE("El destructor de LinkedQueue libera TODOS los nodos")
    {
        TNode<int>::contadorVivos = 0;
        {
            LinkedQueue<int> q;
            q.Enqueue(1);
            q.Enqueue(2);
            q.Enqueue(3);
            CHECK(TNode<int>::contadorVivos == 3);
        }
        CHECK(TNode<int>::contadorVivos == 0);
    }

    TEST_CASE("La copia profunda crea nodos NUEVOS, no comparte los mismos")
    {
        TNode<int>::contadorVivos = 0;
        {
            Stack<int> a;
            a.Push(1);
            a.Push(2);
            CHECK(TNode<int>::contadorVivos == 2);

            Stack<int> b = a;
            // Si la copia fuera superficial, seguirian siendo 2 nodos.
            // Con copia profunda deben ser 4.
            CHECK(TNode<int>::contadorVivos == 4);
        }
        CHECK(TNode<int>::contadorVivos == 0);
    }
}


// =====================================================================
//  ARRANQUE DE LAS PRUEBAS
//  Estas funciones se mandan llamar desde el menu en main.cpp.
// =====================================================================

void CorrerTodasLasPruebas()
{
    doctest::Context contexto;
    contexto.setOption("no-intro", false);
    contexto.run();
}

void CorrerPruebasDe(const char* nombreSuite)
{
    doctest::Context contexto;
    contexto.setOption("test-suite", nombreSuite);
    contexto.run();
}
