#include "storeservice.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

Store createStore()
{
	Store rez;
	rez.allCars = createEmpty();
	return rez;
}

//asigurare capacitate, 0 daca nu exista spatiu si 1 altfel
int ensureCapacity(CarList* l)
{
	if (l->lg < l->cap) return 1; 

	//alocare memorie
	int newCapacity = l->cap + 2;
	Car* nElems = malloc(sizeof(Car) * newCapacity);
	//copiere elemente
	for (int i = 0; i < l->lg; i++)
		nElems[i] = l->elems[i];
	//dealocare tablou vechi
	free(l->elems);
	l->elems = nElems;
	l->cap = newCapacity;
	return 0;
}

//adauga masina la lista
void add(CarList* l, Car el)
{
	int a = ensureCapacity(l);
	l->elems[l->lg] = el;
	l->lg++;
}

int addCar(Store* store, char* plateNo, char* model, char* category) 
{
	Car p = createCar(plateNo, model, category);
	add(&store->allCars, p);
	if (plateNo[0] == 0) return 1;
	if (model[0] == 0) return 2;
	if (category[0] == 0) return 3;
	return 0;
}

void destroyStore(Store* store)
{
	destroy(&store->allCars);
}

void destroyCar(Car* p)
{
	free(p->plateNo);
	free(p->category);
	free(p->model);
	p->plateNo = NULL;
	p->category = NULL;
	p->model = NULL;
	p->rented = -1;

}

/*
  Se cauta masina cu nr de inmatriculare
  Se returneaza pozitia
  -1 daca nu exista
*/
int searchByPlate(CarList* l, char* plate)
{
	for (int i = 0; i < size(l); i++)
	{
		Car c = get(l, i);
		if (strcmp(c.plateNo, plate) == 0)
			return i;
	}
	return -1;
}

/*
* Se modifica statutul masinii (inchiriat/disponibil)
* Se returneaza un nou obiect tip Car
*/
Car changeRentStatus(int i, CarList* l)
{
	Car c = get(l, i);
	//daca este inchiriata, se elibereaza
	if (c.rented) c.rented = 0;
	else c.rented = 1;
	//in caz contrar (masina este disponibila), se inchiriaza
	return c;
}


/**
* Sorteaza in place dupa categorie
*/
void sort1(CarList* l) 
{
	int i, j;
	for (i = 0; i < size(l); i++)
		for (j = i + 1; j < size(l); j++) 
		{
			Car p1 = get(l, i);
			Car p2 = get(l, j);
			if (strcmp(p1.category, p2.category) > 0 )
			{
				//interschimbare
				set(l, i, p2);
				set(l, j, p1);
			}
		}
}

/**
* Sorteaza in place dupa model
*/
void sort2(CarList* l)
{
	int i, j;
	for (i = 0; i < size(l); i++)
		for (j = i + 1; j < size(l); j++)
		{
			Car p1 = get(l, i);
			Car p2 = get(l, j);
			if (strcmp(p1.model, p2.model) > 0)
			{
				//interschimbare
				set(l, i, p2);
				set(l, j, p1);
			}
		}
}

void testeService()
{
	Store store = createStore();
	assert(addCar(&store, "CJ01AAA", "Ferrari", "Sport") == 0);
	assert(addCar(&store, "", "Ferrari", "Sport") == 1);
	assert(addCar(&store, "CJ01AAA", "", "Sport") == 2);
	assert(addCar(&store, "CJ01AAA", "Ferrari", "") == 3);
	assert(addCar(&store, "CJ03DAN", "Tesla", "Sedan") == 0);
	assert(addCar(&store, "NT99XYZ", "BMW", "Break") == 0);
	assert(addCar(&store, "BC12ABC", "Aro", "SUV") == 0);
	assert(addCar(&store, "SV03ALX", "Volkswagen", "Hatchback") == 0);

	assert(searchByPlate(&store.allCars, "NT99XYZ") != -1);
	assert(searchByPlate(&store.allCars, "NT99") == -1);

	Car c = changeRentStatus(1, &store.allCars);
	set(&store.allCars, 1, c);
	assert(c.rented == 1);

	sort1(&store.allCars);
	sort2(&store.allCars);

	destroy(&store.allCars);
	destroyStore(&store);
}

