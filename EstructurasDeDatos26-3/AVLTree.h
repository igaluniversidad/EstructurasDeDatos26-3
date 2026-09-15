#pragma once // evita que este archivo se incluya dos veces
#include "LinkedList.h" // la necesito para guardar el recorrido in-orden
#include "ConsoleUI.h" // la necesito para imprimir bonito

// =====================================================================
// AVLTree: es un BST que se arregla solo.
// Idea simple: despues de insertar, si un lado quedo muy alto, rotamos.
// Factor de balance = altura(izq) - altura(der).
// Solo puede valer -1, 0 o 1. Si vale 2 o -2, hay que rotar.
// Alturas: vacio = 0, hoja (sin hijos) = 1. Siempre igual, sin mezclar.
// Truco: las funciones reciben un nodo y regresan el que quedo arriba,
// porque al rotar el de arriba baja y otro sube.
// =====================================================================

template <class T> // T es el tipo de dato que guardo (int, char, etc.)
class AVLTree // empieza la clase del arbol AVL
{ // abre la clase
private: // lo de aqui solo lo usa el arbol por dentro
    struct Node // cajita que guarda un dato del arbol
    { // abre el struct
        T data; // el valor guardado (ej. 5)
        Node* left; // apunta al hijo de la izquierda (los menores)
        Node* right; // apunta al hijo de la derecha (los mayores)
        int height; // altura de este pedazo de arbol
    }; // cierra el struct

    Node* _root; // punta a la raiz (el de hasta arriba)
    int _size; // cuenta cuantos nodos hay

    // --- helpers de altura ---
    int Altura(Node* n); // me dice la altura guardada de un nodo
    int FactorBalance(Node* n); // me dice si esta cargado a un lado
    void ActualizarAltura(Node* n); // vuelve a calcular la altura de un nodo

    // --- rotaciones ---
    Node* RotarDerecha(Node* n); // arregla cuando esta cargado a la izquierda
    Node* RotarIzquierda(Node* n); // arregla cuando esta cargado a la derecha
    Node* Balancear(Node* n); // revisa y rota si hace falta

    // --- helpers con recursion ---
    Node* InsertRec(Node* n, T valor); // inserta abajo y arregla al subir
    bool ContainsRec(Node* n, T valor); // busca un valor desde un nodo
    void InRec(Node* n, LinkedList<T>& resultado); // junta el in-orden
    void DestruirRec(Node* n); // borra todos los nodos
    bool BalanceadoRec(Node* n); // revisa que todo este balanceado

public: // lo de aqui lo puede usar cualquiera
    AVLTree(); // crea un arbol vacio
    ~AVLTree(); // borra todo el arbol

    void Insert(T valor); // mete un valor y balancea
    bool Contains(T valor); // true si el valor esta
    int GetSize(); // cuantos nodos hay
    int GetAltura(); // que tan alto esta el arbol
    bool EstaBalanceado(); // true si todo esta parejo
    void InOrden(LinkedList<T>& resultado); // llena la lista en orden
    void Print(); // muestra el arbol en pantalla
}; // cierra la clase


template <class T> // esto es para un tipo cualquiera T
AVLTree<T>::AVLTree() // constructor: hace un arbol nuevo
{ // abre constructor
    _root = nullptr; // al inicio no hay raiz
    _size = 0; // al inicio hay 0 nodos
} // cierra constructor

template <class T> // esto es para un tipo cualquiera T
AVLTree<T>::~AVLTree() // destructor: se llama cuando el arbol muere
{ // abre destructor
    DestruirRec(_root); // borro todo desde la raiz
    _root = nullptr; // dejo la raiz en nada para no usar basura
    _size = 0; // dejo el contador en 0
} // cierra destructor

template <class T> // esto es para un tipo cualquiera T
void AVLTree<T>::DestruirRec(Node* n) // borra un pedazo de arbol
{ // abre funcion
    if (n == nullptr) return; // si no hay nodo, no hay nada que borrar
    DestruirRec(n->left); // primero borro todo lo de la izquierda
    DestruirRec(n->right); // despues borro todo lo de la derecha
    delete n; // al final borro este nodo
} // cierra funcion


// --- ALTURA Y BALANCE ---

template <class T> // para cualquier tipo T
int AVLTree<T>::Altura(Node* n) // dime la altura de este nodo
{ // abre funcion
    if (n == nullptr) return 0; // si es vacio, mide 0
    return n->height; // si existe, regreso lo que tiene guardado
} // cierra funcion

template <class T> // para cualquier tipo T
int AVLTree<T>::FactorBalance(Node* n) // que tan cargado esta
{ // abre funcion
    if (n == nullptr) return 0; // vacio = parejo = 0
    return Altura(n->left) - Altura(n->right); // izq menos der
} // cierra funcion
// Si sale positivo, pesa mas la izquierda. Si negativo, la derecha.

template <class T> // para cualquier tipo T
void AVLTree<T>::ActualizarAltura(Node* n) // recalcula la altura
{ // abre funcion
    if (n == nullptr) return; // si no hay nodo, me salgo
    int alturaIzq = Altura(n->left); // altura del hijo izquierdo
    int alturaDer = Altura(n->right); // altura del hijo derecho
    if (alturaIzq > alturaDer) // si la izquierda es mas alta
        n->height = 1 + alturaIzq; // altura = 1 + izquierda
    else // si no
        n->height = 1 + alturaDer; // altura = 1 + derecha
} // cierra funcion


// --- ROTACIONES ---
// Dibujalo asi: una rotacion solo cambia 2 flechas y luego arregla 2 alturas.

template <class T> // para cualquier tipo T
typename AVLTree<T>::Node* AVLTree<T>::RotarDerecha(Node* n) // gira a la derecha
{ // abre funcion
    // Caso: n esta cargado a la izquierda, su hijo izq sube.
    //     n            izq
    //    / \          /   \
    //  izq   C  -->  A     n
    //  / \                / \
    // A   B              B   C
    Node* izq = n->left; // guardo al hijo izquierdo (el que va a subir)
    Node* subB = izq->right; // guardo a B (el del medio, el que estorba)

    izq->right = n; // ahora n es hijo derecho de izq
    n->left = subB; // B pasa a ser hijo izquierdo de n

    ActualizarAltura(n); // primero arreglo al que bajo (n)
    ActualizarAltura(izq); // despues arreglo al que subio (izq)

    return izq; // regreso al nuevo jefe de este pedazo
} // cierra funcion

template <class T> // para cualquier tipo T
typename AVLTree<T>::Node* AVLTree<T>::RotarIzquierda(Node* n) // gira a la izquierda
{ // abre funcion
    // Es lo mismo pero al reves (espejo).
    //     n              der
    //    / \            /   \
    //   C  der  -->    n     A
    //      / \        / \
    //     B   A      C   B
    Node* der = n->right; // guardo al hijo derecho (el que va a subir)
    Node* subB = der->left; // guardo a B (el del medio)

    der->left = n; // ahora n es hijo izquierdo de der
    n->right = subB; // B pasa a ser hijo derecho de n

    ActualizarAltura(n); // primero arreglo al que bajo (n)
    ActualizarAltura(der); // despues arreglo al que subio (der)

    return der; // regreso al nuevo jefe de este pedazo
} // cierra funcion

template <class T> // para cualquier tipo T
typename AVLTree<T>::Node* AVLTree<T>::Balancear(Node* n) // revisa y arregla
{ // abre funcion
    if (n == nullptr) return nullptr; // si no hay nodo, regreso nada

    ActualizarAltura(n); // primero pongo al dia la altura de n
    int factor = FactorBalance(n); // veo si esta cargado

    if (factor > 1) // si pesa mucho a la izquierda (vale 2)
    { // abre caso izquierda
        if (FactorBalance(n->left) >= 0) // si el hijo tambien pesa a la izq
        { // abre caso LL
            return RotarDerecha(n); // solo giro a la derecha (caso LL)
        } // cierra caso LL
        // si no, el hijo pesa a la derecha (caso LR)
        n->left = RotarIzquierda(n->left); // primero giro al hijo a la izq
        return RotarDerecha(n); // luego giro este a la der
    } // cierra caso izquierda

    if (factor < -1) // si pesa mucho a la derecha (vale -2)
    { // abre caso derecha
        if (FactorBalance(n->right) <= 0) // si el hijo tambien pesa a la der
        { // abre caso RR
            return RotarIzquierda(n); // solo giro a la izquierda (caso RR)
        } // cierra caso RR
        // si no, el hijo pesa a la izquierda (caso RL)
        n->right = RotarDerecha(n->right); // primero giro al hijo a la der
        return RotarIzquierda(n); // luego giro este a la izq
    } // cierra caso derecha

    return n; // si estaba parejo, lo dejo igual
} // cierra funcion


// --- INSERTAR ---

template <class T> // para cualquier tipo T
void AVLTree<T>::Insert(T valor) // mete un valor al arbol
{ // abre funcion
    _root = InsertRec(_root, valor); // guardo lo que regrese porque la raiz puede cambiar
} // cierra funcion

template <class T> // para cualquier tipo T
typename AVLTree<T>::Node* AVLTree<T>::InsertRec(Node* n, T valor) // inserta con recursion
{ // abre funcion
    if (n == nullptr) // si llegue a un hueco vacio
    { // abre crear nodo
        Node* nuevo = new Node(); // creo una cajita nueva
        nuevo->data = valor; // le guardo el valor
        nuevo->left = nullptr; // aun no tiene hijo izq
        nuevo->right = nullptr; // aun no tiene hijo der
        nuevo->height = 1; // un nodo solo mide 1
        _size++; // cuento uno mas
        return nuevo; // regreso el nodo nuevo
    } // cierra crear nodo

    if (valor < n->data) // si el valor es mas chico
    { // abre ir a la izquierda
        n->left = InsertRec(n->left, valor); // lo meto a la izquierda y guardo lo que regrese
    } // cierra ir a la izquierda
    else if (valor > n->data) // si el valor es mas grande
    { // abre ir a la derecha
        n->right = InsertRec(n->right, valor); // lo meto a la derecha y guardo lo que regrese
    } // cierra ir a la derecha
    else // si es igual
    { // abre duplicado
        return n; // no meto repetidos, regreso igual
    } // cierra duplicado

    return Balancear(n); // al subir, arreglo este nodo y regreso quien quedo arriba
} // cierra funcion


// --- BUSCAR Y PREGUNTAR ---

template <class T> // para cualquier tipo T
bool AVLTree<T>::Contains(T valor) // esta este valor en el arbol?
{ // abre funcion
    return ContainsRec(_root, valor); // busco desde la raiz
} // cierra funcion

template <class T> // para cualquier tipo T
bool AVLTree<T>::ContainsRec(Node* n, T valor) // busca desde un nodo
{ // abre funcion
    if (n == nullptr) return false; // si llegue a vacio, no esta
    if (valor == n->data) return true; // si es igual, si esta
    if (valor < n->data) return ContainsRec(n->left, valor); // si es menor, busco a la izq
    return ContainsRec(n->right, valor); // si es mayor, busco a la der
} // cierra funcion

template <class T> // para cualquier tipo T
int AVLTree<T>::GetSize() // cuantos nodos hay
{ // abre funcion
    return _size; // regreso el contador
} // cierra funcion

template <class T> // para cualquier tipo T
int AVLTree<T>::GetAltura() // que tan alto esta todo el arbol
{ // abre funcion
    return Altura(_root); // la altura de la raiz es la de todo
} // cierra funcion

template <class T> // para cualquier tipo T
bool AVLTree<T>::EstaBalanceado() // todo esta parejo?
{ // abre funcion
    return BalanceadoRec(_root); // reviso desde la raiz
} // cierra funcion

template <class T> // para cualquier tipo T
bool AVLTree<T>::BalanceadoRec(Node* n) // revisa un pedazo
{ // abre funcion
    if (n == nullptr) return true; // vacio = parejo
    int factor = FactorBalance(n); // veo el factor de este nodo
    if (factor < -1 || factor > 1) return false; // si es 2 o -2, esta mal
    if (!BalanceadoRec(n->left)) return false; // si la izq esta mal, todo mal
    if (!BalanceadoRec(n->right)) return false; // si la der esta mal, todo mal
    return true; // si todo bien, regreso true
} // cierra funcion


// --- RECORRIDO Y MOSTRAR ---

template <class T> // para cualquier tipo T
void AVLTree<T>::InOrden(LinkedList<T>& resultado) // dame todo en orden
{ // abre funcion
    InRec(_root, resultado); // empiezo desde la raiz
} // cierra funcion

template <class T> // para cualquier tipo T
void AVLTree<T>::InRec(Node* n, LinkedList<T>& resultado) // ayuda del in-orden
{ // abre funcion
    if (n == nullptr) return; // si no hay nodo, me salgo
    InRec(n->left, resultado); // primero junto lo de la izquierda
    resultado.Add(n->data); // luego guardo este dato
    InRec(n->right, resultado); // al final junto lo de la derecha
} // cierra funcion
// Si esto sale desordenado, una rotacion movio mal un puntero.

template <class T> // para cualquier tipo T
void AVLTree<T>::Print() // muestra el arbol
{ // abre funcion
    LinkedList<T> recorrido; // creo una lista vacia
    InOrden(recorrido); // la lleno en orden
    ConsoleUI::PrintTitle("AVL (IN-ORDEN)"); // pongo un titulo bonito
    recorrido.Print(); // muestro la lista
} // cierra funcion
