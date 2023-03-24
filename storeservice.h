#pragma once

#include "repository.h"

typedef struct {
	CarList allCars;
} Store;

Store createStore();

void sort1(CarList* l);

void sort2(CarList* l);

void destroyStore(Store* store);

int addCar(Store* store, char* plateNo, char* model, char* category);

int searchByPlate(CarList* l, char* plateNo);

Car changeRentStatus(int i, CarList* l);

int ensureCapacity(CarList* l);


void testeService();