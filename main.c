#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Car.h"
#include "storeservice.h"

#include <stdio.h>

void readCar(Store* store)
{
	printf("Plate:");
	char plate[30];
	scanf_s("%s", plate, 30);

	printf("Model:");
	char model[30];
	scanf_s("%s", model, 30);

	printf("Type:");
	char type[30];
	scanf_s("%s", type, 30);

	int error = addCar(store, plate, model, type);
	if (error != 0)
		printf("Invalid.\n");
	else
		printf("Car added.\n");
}

//se citeste numar de inmatriculare
//se returneaza pozitia din lista unde a fost gasit
//sau -1 daca nu exista
int readPlate(Store* store)
{
	int x = 0;
	printf("Plate:");
	char plate[30];
	scanf_s("%s", plate, 30);
	x = searchByPlate(&store -> allCars, plate);
	return x;
}

//print toate masinile, cu toate criteriile
void printAllCars (CarList* l)
{
	printf("Cars:\n");
	for (int i = 0; i < size(l); i++) {
		Car p = get(l, i);
		printf("plateNo:%s Model:%s Category:%s Rented: %d\n", p.plateNo, p.model, p.category, p.rented);
	}
}

//print dupa model
void printCarsModel(CarList* l)
{
	printf("Cars:\n");
	for (int i = 0; i < size(l); i++) {
		Car p = get(l, i);
		printf("%s Rented: %d\n", p.model, p.rented);
	}
}

//print dupa categorie
void printCarsCategory(CarList* l)
{
	printf("Cars:\n");
	for (int i = 0; i < size(l); i++) {
		Car p = get(l, i);
		printf("%s Rented: %d\n", p.category, p.rented);
	}
}

void run_ui()
{
	Store store = createStore();
	int ruleaza = 1;
	while (ruleaza)
	{
		printf("1 Add\n2 Show all\n3 Rent/return car\n4 view by category\n5 view by model\n6 sort by category\n7 sort by model\n0 exit\nCommand:");
		int cmd = 0;
		scanf_s("%d", &cmd);
		switch (cmd)
		{
			case 1:
				readCar(&store);
				break;
			case 2:
				printAllCars(&store.allCars);
				break;
			case 3:
			{
				int x = readPlate(&store);
				if (x == -1) printf("This car does not exist!\n");
				else
				{
					Car c = changeRentStatus(x, &store.allCars);
					set(&store.allCars, x, c);
				}
				break;
			}
			case 4:
				printCarsCategory(&store.allCars);
				break;
			case 5:
				printCarsModel(&store.allCars);
				break;
			case 6:
				sort1(&store.allCars);
				break;
			case 7:
				sort2(&store.allCars);
				break;
			case 0:
				ruleaza = 0;
				break;
			default:
				printf("Comanda invalida! Incercati din nou\n");
		}
	}
	destroyStore(&store);
	return;
}

int main()
{
	testeService();
	testeMasina();
	testeLista();
	run_ui();
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
	return 0;
}