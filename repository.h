#pragma once

#include "Car.h"

typedef struct
{
	Car* elems;
	int lg; //length
	int cap; //capacity
} 
CarList;


CarList createEmpty();

//distruge lista
void destroy(CarList* l);

Car get(CarList* l, int poz);

Car set(CarList* l, int poz, Car c);

int size(CarList* l);

void add(CarList* l, Car el);


void testeLista();