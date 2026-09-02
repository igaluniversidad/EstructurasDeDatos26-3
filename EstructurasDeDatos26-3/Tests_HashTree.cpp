// =====================================================================
//  Tests_HashTree.cpp  -  Pruebas de HashTable y Tree
//  Estructuras de Datos (GPD4402) - SAE Institute Mexico
// =====================================================================
//
//  OJO: este archivo NO lleva DOCTEST_CONFIG_IMPLEMENT.
//  Ese define ya vive en Tests.cpp y solo puede estar en UN archivo.
//  Aqui basta con incluir doctest: las pruebas se registran solas.
//
//  Grupos nuevos: "HashTable", "Tree", "Recorridos"
//
//  Igual que antes: NO modifiques este archivo. Es el contrato.
//
// =====================================================================

#include "doctest.h"

#include "HashTable.h"
#include "Tree.h"
#include "LinkedList.h"

#include <string>


// =====================================================================
//  SUITE: HashTable
// =====================================================================
TEST_SUITE("HashTable")
{
    TEST_CASE("Una tabla recien creada esta vacia")
    {
        HashTable<int> tabla(16);
        CHECK(tabla.GetSize() == 0);
        CHECK(tabla.GetCapacidad() == 16);
    }

    TEST_CASE("El hash SIEMPRE cae dentro del rango de buckets")
    {
        // Sin importar que tan larga o rara sea la llave, el resultado
        // debe poder usarse como indice del arreglo de buckets.
        HashTable<int> tabla(16);

        CHECK(tabla.Hash("a") >= 0);
        CHECK(tabla.Hash("a") < 16);
        CHECK(tabla.Hash("zzzzzzzzzzzzzzzzzzzzzzzzzzzz") >= 0);
        CHECK(tabla.Hash("zzzzzzzzzzzzzzzzzzzzzzzzzzzz") < 16);
        CHECK(tabla.Hash("") >= 0);
        CHECK(tabla.Hash("") < 16);
    }

    TEST_CASE("El hash es determinista: la misma llave da siempre lo mismo")
    {
        HashTable<int> tabla(16);
        CHECK(tabla.Hash("jugador") == tabla.Hash("jugador"));
    }

    TEST_CASE("El hash distingue el orden de los caracteres")
    {
        // Si tu funcion solo suma los caracteres, "abc" y "cba" van a dar
        // el mismo hash. Una buena funcion los distingue.
        HashTable<int> tabla(1024);
        CHECK(tabla.Hash("abc") != tabla.Hash("cba"));
    }

    TEST_CASE("Insert y Get guardan y recuperan el valor")
    {
        HashTable<int> tabla(16);
        tabla.Insert("vida", 100);
        tabla.Insert("mana", 50);

        CHECK(tabla.GetSize() == 2);
        CHECK(tabla.Get("vida") == 100);
        CHECK(tabla.Get("mana") == 50);
    }

    TEST_CASE("Contains dice si la llave existe")
    {
        HashTable<int> tabla(16);
        tabla.Insert("vida", 100);

        CHECK(tabla.Contains("vida") == true);
        CHECK(tabla.Contains("municiones") == false);
    }

    TEST_CASE("Insertar una llave que ya existe REEMPLAZA el valor")
    {
        // No debe crear una segunda entrada con la misma llave.
        HashTable<int> tabla(16);
        tabla.Insert("vida", 100);
        tabla.Insert("vida", 75);

        CHECK(tabla.Get("vida") == 75);
        CHECK(tabla.GetSize() == 1);
    }

    TEST_CASE("La tabla maneja colisiones correctamente")
    {
        // Con capacidad 1, TODAS las llaves caen en el mismo bucket,
        // sin importar como este escrita tu funcion hash.
        // O sea: todo colisiona. Si tu encadenamiento sirve, esto pasa.
        HashTable<int> tabla(1);
        tabla.Insert("uno", 1);
        tabla.Insert("dos", 2);
        tabla.Insert("tres", 3);

        CHECK(tabla.GetSize() == 3);
        CHECK(tabla.Get("uno") == 1);
        CHECK(tabla.Get("dos") == 2);
        CHECK(tabla.Get("tres") == 3);
    }

    TEST_CASE("Remove quita la llave y reduce el tamanio")
    {
        HashTable<int> tabla(16);
        tabla.Insert("vida", 100);
        tabla.Insert("mana", 50);

        CHECK(tabla.Remove("vida") == true);
        CHECK(tabla.Contains("vida") == false);
        CHECK(tabla.GetSize() == 1);
        CHECK(tabla.Contains("mana") == true);   // no toco a los vecinos
    }

    TEST_CASE("Remove de una llave que no existe regresa false")
    {
        HashTable<int> tabla(16);
        tabla.Insert("vida", 100);

        CHECK(tabla.Remove("nolaconozco") == false);
        CHECK(tabla.GetSize() == 1);
    }

    TEST_CASE("Remove funciona sobre una llave en medio de una cadena")
    {
        // Otra vez capacidad 1: las tres viven en el mismo bucket.
        // Quitar la de en medio no debe romper la cadena.
        HashTable<int> tabla(1);
        tabla.Insert("uno", 1);
        tabla.Insert("dos", 2);
        tabla.Insert("tres", 3);

        CHECK(tabla.Remove("dos") == true);
        CHECK(tabla.Contains("uno") == true);
        CHECK(tabla.Contains("tres") == true);
        CHECK(tabla.Contains("dos") == false);
        CHECK(tabla.GetSize() == 2);
    }

    TEST_CASE("La tabla sirve para cualquier tipo de valor")
    {
        HashTable<std::string> tabla(16);
        tabla.Insert("arma", "espada");
        CHECK(tabla.Get("arma") == "espada");
    }
}


// =====================================================================
//  SUITE: Tree
// =====================================================================
TEST_SUITE("Tree")
{
    TEST_CASE("Un arbol recien creado esta vacio")
    {
        Tree<int> arbol;
        CHECK(arbol.GetSize() == 0);
        CHECK(arbol.GetAltura() == 0);
    }

    TEST_CASE("Insert agrega elementos y sube el tamanio")
    {
        Tree<int> arbol;
        arbol.Insert(50);
        arbol.Insert(30);
        arbol.Insert(70);

        CHECK(arbol.GetSize() == 3);
    }

    TEST_CASE("Contains encuentra lo que esta y no lo que no esta")
    {
        Tree<int> arbol;
        arbol.Insert(50);
        arbol.Insert(30);
        arbol.Insert(70);

        CHECK(arbol.Contains(50) == true);
        CHECK(arbol.Contains(30) == true);
        CHECK(arbol.Contains(70) == true);
        CHECK(arbol.Contains(99) == false);
    }

    TEST_CASE("Insertar un valor repetido NO lo duplica")
    {
        Tree<int> arbol;
        arbol.Insert(50);
        arbol.Insert(50);

        CHECK(arbol.GetSize() == 1);
    }

    TEST_CASE("La altura se calcula correctamente")
    {
        //        50
        //       /  \
        //     30    70
        //    /
        //  20
        Tree<int> arbol;
        arbol.Insert(50);
        CHECK(arbol.GetAltura() == 1);

        arbol.Insert(30);
        arbol.Insert(70);
        CHECK(arbol.GetAltura() == 2);

        arbol.Insert(20);
        CHECK(arbol.GetAltura() == 3);
    }

    TEST_CASE("Un arbol degenerado tiene altura igual a su tamanio")
    {
        // Si insertas en orden, el BST se convierte en una lista.
        // Por eso existen los arboles balanceados.
        Tree<int> arbol;
        arbol.Insert(1);
        arbol.Insert(2);
        arbol.Insert(3);
        arbol.Insert(4);

        CHECK(arbol.GetSize() == 4);
        CHECK(arbol.GetAltura() == 4);
    }
}


// =====================================================================
//  SUITE: Recorridos
//
//  Todos los recorridos trabajan sobre este mismo arbol:
//
//              50
//             /  \
//           30    70
//          /  \     \
//        20    40    80
//
// =====================================================================
TEST_SUITE("Recorridos")
{
    TEST_CASE("PreOrden: nodo, izquierda, derecha")
    {
        Tree<int> arbol;
        arbol.Insert(50); arbol.Insert(30); arbol.Insert(70);
        arbol.Insert(20); arbol.Insert(40); arbol.Insert(80);

        LinkedList<int> r;
        arbol.PreOrden(r);

        CHECK(r.GetSize() == 6);
        CHECK(r.GetAt(0) == 50);
        CHECK(r.GetAt(1) == 30);
        CHECK(r.GetAt(2) == 20);
        CHECK(r.GetAt(3) == 40);
        CHECK(r.GetAt(4) == 70);
        CHECK(r.GetAt(5) == 80);
    }

    TEST_CASE("InOrden: izquierda, nodo, derecha (sale ORDENADO)")
    {
        Tree<int> arbol;
        arbol.Insert(50); arbol.Insert(30); arbol.Insert(70);
        arbol.Insert(20); arbol.Insert(40); arbol.Insert(80);

        LinkedList<int> r;
        arbol.InOrden(r);

        CHECK(r.GetSize() == 6);
        CHECK(r.GetAt(0) == 20);
        CHECK(r.GetAt(1) == 30);
        CHECK(r.GetAt(2) == 40);
        CHECK(r.GetAt(3) == 50);
        CHECK(r.GetAt(4) == 70);
        CHECK(r.GetAt(5) == 80);
    }

    TEST_CASE("PostOrden: izquierda, derecha, nodo")
    {
        Tree<int> arbol;
        arbol.Insert(50); arbol.Insert(30); arbol.Insert(70);
        arbol.Insert(20); arbol.Insert(40); arbol.Insert(80);

        LinkedList<int> r;
        arbol.PostOrden(r);

        CHECK(r.GetSize() == 6);
        CHECK(r.GetAt(0) == 20);
        CHECK(r.GetAt(1) == 40);
        CHECK(r.GetAt(2) == 30);
        CHECK(r.GetAt(3) == 80);
        CHECK(r.GetAt(4) == 70);
        CHECK(r.GetAt(5) == 50);   // la raiz siempre sale al final
    }

    TEST_CASE("InOrdenIterativo da EXACTAMENTE lo mismo que InOrden")
    {
        // Mismo resultado, distinto motor: aqui usas TU Stack en lugar
        // de la pila de llamadas del compilador.
        Tree<int> arbol;
        arbol.Insert(50); arbol.Insert(30); arbol.Insert(70);
        arbol.Insert(20); arbol.Insert(40); arbol.Insert(80);

        LinkedList<int> recursivo;
        LinkedList<int> iterativo;
        arbol.InOrden(recursivo);
        arbol.InOrdenIterativo(iterativo);

        CHECK(iterativo.GetSize() == recursivo.GetSize());
        for (int i = 0; i < recursivo.GetSize(); i++)
        {
            CHECK(iterativo.GetAt(i) == recursivo.GetAt(i));
        }
    }

    TEST_CASE("PorNiveles (BFS con cola): nivel por nivel, de izquierda a derecha")
    {
        Tree<int> arbol;
        arbol.Insert(50); arbol.Insert(30); arbol.Insert(70);
        arbol.Insert(20); arbol.Insert(40); arbol.Insert(80);

        LinkedList<int> r;
        arbol.PorNiveles(r);

        CHECK(r.GetSize() == 6);
        CHECK(r.GetAt(0) == 50);   // nivel 1
        CHECK(r.GetAt(1) == 30);   // nivel 2
        CHECK(r.GetAt(2) == 70);
        CHECK(r.GetAt(3) == 20);   // nivel 3
        CHECK(r.GetAt(4) == 40);
        CHECK(r.GetAt(5) == 80);
    }

    TEST_CASE("PorNivelesRecursivo da EXACTAMENTE lo mismo que PorNiveles")
    {
        // Mismo resultado que la version con cola, pero visitando cada
        // nivel por separado. Es mas lento: los nodos de arriba se
        // recorren una vez por cada nivel que hay debajo de ellos.
        Tree<int> arbol;
        arbol.Insert(50); arbol.Insert(30); arbol.Insert(70);
        arbol.Insert(20); arbol.Insert(40); arbol.Insert(80);

        LinkedList<int> conCola;
        LinkedList<int> recursivo;
        arbol.PorNiveles(conCola);
        arbol.PorNivelesRecursivo(recursivo);

        CHECK(recursivo.GetSize() == conCola.GetSize());
        for (int i = 0; i < conCola.GetSize(); i++)
        {
            CHECK(recursivo.GetAt(i) == conCola.GetAt(i));
        }
    }

    TEST_CASE("Los recorridos sobre un arbol vacio no truenan")
    {
        Tree<int> arbol;
        LinkedList<int> r;

        arbol.PreOrden(r);
        arbol.InOrden(r);
        arbol.PostOrden(r);
        arbol.InOrdenIterativo(r);
        arbol.PorNiveles(r);
        arbol.PorNivelesRecursivo(r);

        CHECK(r.GetSize() == 0);
    }

    TEST_CASE("Los recorridos funcionan con un solo nodo")
    {
        Tree<int> arbol;
        arbol.Insert(42);

        LinkedList<int> r;
        arbol.InOrdenIterativo(r);

        CHECK(r.GetSize() == 1);
        CHECK(r.GetAt(0) == 42);
    }
}
