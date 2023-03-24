#pragma once

typedef struct {
	char* plateNo;
	char* model;
	char* category;
	int rented;
} Car;

Car createCar(char* plateNo, char* model, char* category);

void destroyCar(Car* p);


void testeMasina();
