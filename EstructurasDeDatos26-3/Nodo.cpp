#include "Nodo.h"

Nodo::Nodo() 
{
	std::cout << "NO LE PASASTE VALORES. CUIDADO" << std::endl;
	_dato = 0;
	_next = nullptr;
	_id = -1;
}

Nodo::Nodo(int dato, Nodo* nodo, int id)
{
	_dato = dato;
	_next = nodo;
	_id = id;
}


void Nodo::setDato(int d) {
	_dato = d;
}

int Nodo::GetDato()
{
	return _dato;
}

void Nodo::setId(int id)
{
	_id = id;
}

int Nodo::GetId()
{
	return _id;
}

void Nodo::setNext(Nodo* n)
{
	_next = n;
}

Nodo* Nodo::getNext()
{
	return _next;
}