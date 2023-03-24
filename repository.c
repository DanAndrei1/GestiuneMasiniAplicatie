#include "Car.h"
#include "repository.h"
#include "storeservice.h"

#include <stdlib.h>
#include <assert.h>

//creare lista goala
CarList createEmpty()
{
	CarList rez;
	rez.lg = 0;
	rez.cap = 2;
	rez.elems = malloc(sizeof(Car) * rez.cap);
	return rez;
}

void destroy(CarList* l)
{	
	for (int i = 0; i < l->lg; i++)
		destroyCar(&l->elems[i]);
	free(l->elems);
	l->elems = NULL;
	l->lg = 0;
}

Car get(CarList* l, int poz)
{
	return l->elems[poz];
}

int size(CarList* l)
{
	return l->lg;
}

/*
  Modifica elementul de pe poz data
  Se returneaza elementul nou
*/
Car set(CarList* l, int poz, Car c)
{
	Car rez = l->elems[poz];
	l->elems[poz] = c;
	return rez;
}

void testeLista()
{
	Store store = createStore();
	CarList l = createEmpty();
	assert(size(&l) == 0);
	assert(addCar(&store, "B100LYA", "Ford", "Break") == 0);
	assert(size(&store.allCars) == 1);
	destroy(&store.allCars);
	destroyStore(&store);
	destroy(&l);
}