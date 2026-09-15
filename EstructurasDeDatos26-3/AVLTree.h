#pragma once
#include "LinkedList.h"
#include "ConsoleUI.h"

// =====================================================================
//  AVLTree<T>  -  Arbol binario de busqueda BALANCEADO
//
//  Es el mismo BST de la practica 5, con una regla de mas: despues de
//  cada insercion, si alguna parte del arbol quedo demasiado cargada
//  hacia un lado, el arbol se reacomoda solo con una ROTACION.
//
//  EL FACTOR DE BALANCE de un nodo es:
//      altura(subarbol izquierdo) - altura(subarbol derecho)
//  Un nodo esta bien si vale -1, 0 o 1. En cuanto vale 2 o -2, ese nodo
//  esta desbalanceado y hay que corregirlo.
//
//  CONVENCION DE ALTURAS (respetala, las pruebas la asumen):
//      un nodo nulo mide 0
//      un nodo hoja mide 1
//  La mayoria de los errores de "se me desbalancea solo" salen de
//  mezclar convenciones a medio camino.
//
//  ---------------------------------------------------------------
//  UN CAMBIO DE PATRON RESPECTO A LA PRACTICA 5
//
//  En tu Tree usaste:      void InsertRec(Node*& n, T valor);
//  Aqui vas a usar:        Node* InsertRec(Node* n, T valor);
//
//  El cambio no es capricho. Una rotacion cambia CUAL nodo es la raiz
//  de ese subarbol: el que estaba arriba baja, y uno de sus hijos sube
//  a ocupar su lugar. Entonces cada llamada recursiva tiene que poder
//  decirle a su padre "despues de acomodarme, ahora el jefe de este
//  subarbol es este otro nodo".
//
//  El patron es: cada funcion recibe la raiz actual del subarbol, hace
//  lo suyo, y REGRESA la raiz que quedo. El padre guarda ese resultado:
//
//      n->left = InsertRec(n->left, valor);
//
//  Las rotaciones y Balancear usan el mismo patron. Cuando lo entiendas,
//  el codigo del AVL se vuelve sorprendentemente corto.
// =====================================================================

template <class T>
class AVLTree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        int height;      // la altura de ESTE subarbol
    };

    Node* _root;
    int _size;

    // --- auxiliares de altura y balance ---
    int Altura(Node* n);
    int FactorBalance(Node* n);
    void ActualizarAltura(Node* n);

    // --- las rotaciones ---
    Node* RotarDerecha(Node* n);
    Node* RotarIzquierda(Node* n);
    Node* Balancear(Node* n);

    // --- auxiliares recursivas ---
    Node* InsertRec(Node* n, T valor);
    bool ContainsRec(Node* n, T valor);
    void InRec(Node* n, LinkedList<T>& resultado);
    void DestruirRec(Node* n);
    bool BalanceadoRec(Node* n);

public:
    AVLTree();
    ~AVLTree();

    void Insert(T valor);
    bool Contains(T valor);
    int GetSize();
    int GetAltura();
    bool EstaBalanceado();
    void InOrden(LinkedList<T>& resultado);
    void Print();
};


template <class T>
AVLTree<T>::AVLTree()
{
    _root = nullptr;
    _size = 0;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    DestruirRec(_root);
    _root = nullptr;
    _size = 0;
}

template <class T>
void AVLTree<T>::DestruirRec(Node* n)
{
    // Post-orden: primero los hijos, al final el nodo actual.
    if (n == nullptr) return;
    DestruirRec(n->left);
    DestruirRec(n->right);
    delete n;
}


// ---------------------------------------------------------------------
//  ALTURA Y BALANCE
//
//  Empieza por aqui. Sin estas tres, no puedes programar nada mas.
// ---------------------------------------------------------------------

template <class T>
int AVLTree<T>::Altura(Node* n)
{
    // O(1): lee el campo guardado, no recorre el arbol.
    // Convencion: nulo = 0, hoja = 1.
    if (n == nullptr) return 0;
    return n->height;
}

template <class T>
int AVLTree<T>::FactorBalance(Node* n)
{
    // altura(izquierda) - altura(derecha). Nulo = 0 (balanceado).
    // Positivo = cargado a la izquierda, negativo = a la derecha.
    if (n == nullptr) return 0;
    return Altura(n->left) - Altura(n->right);
}

template <class T>
void AVLTree<T>::ActualizarAltura(Node* n)
{
    // La altura de n es 1 mas que la del mas alto de sus hijos.
    if (n == nullptr) return;
    int alturaIzq = Altura(n->left);
    int alturaDer = Altura(n->right);
    n->height = 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
}


// ---------------------------------------------------------------------
//  LAS ROTACIONES
//
//  Aqui esta el corazon de la practica, y es la parte que te toca
//  investigar. Apoyate en el visualizador de VisuAlgo: puedes insertar
//  valores y ver las rotaciones ocurrir paso a paso.
//
//  DIBUJALAS EN PAPEL ANTES DE PROGRAMARLAS. Tres nodos y sus
//  subarboles. Una rotacion mueve exactamente dos punteros y despues
//  actualiza dos alturas. Si no la puedes dibujar, no la vas a poder
//  programar.
// ---------------------------------------------------------------------

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::RotarDerecha(Node* n)
{
    //      n                izq
    //     / \              /   \
    //   izq   C    -->    A     n
    //   / \                    / \
    //  A   B                  B   C
    // El hijo izquierdo sube, n baja a ser hijo derecho.
    // El subarbol B (el que estorbaba) pasa a ser hijo izquierdo de n.
    Node* izq = n->left;
    Node* subB = izq->right;

    izq->right = n;
    n->left = subB;

    // Orden correcto: primero el que BAJO (n), despues el que SUBIO (izq).
    ActualizarAltura(n);
    ActualizarAltura(izq);

    return izq;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::RotarIzquierda(Node* n)
{
    // Espejo de RotarDerecha:
    //      n                  der
    //     / \                /   \
    //    C   der    -->     n     A
    //       / \            / \
    //      B   A          C   B
    Node* der = n->right;
    Node* subB = der->left;

    der->left = n;
    n->right = subB;

    ActualizarAltura(n);
    ActualizarAltura(der);

    return der;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::Balancear(Node* n)
{
    if (n == nullptr) return nullptr;

    ActualizarAltura(n);
    int factor = FactorBalance(n);

    // Cargado a la IZQUIERDA (factor 2)
    if (factor > 1)
    {
        // LL: hijo izquierdo cargado a la izquierda (o parejo) -> una rotacion.
        if (FactorBalance(n->left) >= 0)
        {
            return RotarDerecha(n);
        }
        // LR: hijo izquierdo cargado a la derecha -> dos rotaciones.
        n->left = RotarIzquierda(n->left);
        return RotarDerecha(n);
    }

    // Cargado a la DERECHA (factor -2)
    if (factor < -1)
    {
        // RR: hijo derecho cargado a la derecha (o parejo) -> una rotacion.
        if (FactorBalance(n->right) <= 0)
        {
            return RotarIzquierda(n);
        }
        // RL: hijo derecho cargado a la izquierda -> dos rotaciones.
        n->right = RotarDerecha(n->right);
        return RotarIzquierda(n);
    }

    // Balanceado: queda el mismo.
    return n;
}


// ---------------------------------------------------------------------
//  INSERCION
// ---------------------------------------------------------------------

template <class T>
void AVLTree<T>::Insert(T valor)
{
    // TODO: arrancar la recursion y GUARDAR el resultado en _root.
    // Ese "guardar" es importante: si la raiz rota, _root cambia.
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::InsertRec(Node* n, T valor)
{
    // TODO: la estructura es la misma de tu BST (bajar a la izquierda o
    // a la derecha segun la comparacion, no admitir duplicados), con dos
    // diferencias:
    //
    //   1. Guarda el resultado de la llamada recursiva:
    //          n->left = InsertRec(n->left, valor);
    //
    //   2. Al REGRESAR de la recursion, llama a Balancear(n) y regresa
    //      lo que te de.
    //
    // Ese "al regresar" es lo mismo que ya hiciste con PrintReverse y
    // con el post-orden: la accion ocurre cuando la recursion se
    // devuelve, no cuando baja.
    //
    // El nodo nuevo nace con altura 1.
    return n;
}


// ---------------------------------------------------------------------
//  CONSULTA
// ---------------------------------------------------------------------

template <class T>
bool AVLTree<T>::Contains(T valor)
{
    // TODO
    return false;
}

template <class T>
bool AVLTree<T>::ContainsRec(Node* n, T valor)
{
    // TODO: igual que en tu BST. El balanceo no cambia como se busca,
    // solo garantiza que la busqueda sea corta.
    return false;
}

template <class T>
int AVLTree<T>::GetSize()
{
    // TODO
    return 0;
}

template <class T>
int AVLTree<T>::GetAltura()
{
    // TODO: la altura del arbol completo.
    return 0;
}

template <class T>
bool AVLTree<T>::EstaBalanceado()
{
    // TODO
    return true;
}

template <class T>
bool AVLTree<T>::BalanceadoRec(Node* n)
{
    // TODO: un nodo nulo esta balanceado. Si no, su factor debe estar
    // entre -1 y 1, Y sus dos hijos tambien deben estar balanceados.
    //
    // Esta funcion es tu DETECTOR: llamala despues de cada insercion
    // mientras depuras. En cuanto regrese false, la insercion que
    // acabas de hacer es la que rompio algo.
    return true;
}


// ---------------------------------------------------------------------
//  RECORRIDO Y SALIDA
// ---------------------------------------------------------------------

template <class T>
void AVLTree<T>::InOrden(LinkedList<T>& resultado)
{
    // TODO
}

template <class T>
void AVLTree<T>::InRec(Node* n, LinkedList<T>& resultado)
{
    // TODO: izquierda, nodo, derecha. En un arbol de busqueda sale
    // ordenado, y eso es tu mejor verificacion: si tu in-orden sale
    // desordenado, alguna rotacion esta moviendo un puntero al lado
    // equivocado.
}

template <class T>
void AVLTree<T>::Print()
{
    // TODO: usa el recorrido in-orden y ConsoleUI. Casi todo el trabajo
    // ya lo hiciste: aqui solo lo conectas.
}
