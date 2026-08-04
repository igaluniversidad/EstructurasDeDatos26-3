#pragma once
#include <iostream>

class Nodo
{
private:
	int _dato;
	Nodo* _next;
	int _id;
public:
	void setDato(int d);
	int GetDato();

	void setId(int id);
	int GetId();

	void setNext(Nodo* n);
	Nodo* getNext();

	Nodo();
	Nodo(int dato, Nodo* nodo, int id);
};

