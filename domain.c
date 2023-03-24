#include "car.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

Car createCar(char* plateNo, char* model, char* category)
{
	Car rez;

	size_t nrC = strlen(plateNo) + 1;
	rez.plateNo= malloc(sizeof(char) * nrC);
	if (rez.plateNo != 0)
		strcpy_s(rez.plateNo, nrC, plateNo);

	nrC = strlen(model) + 1;
	rez.model = malloc(sizeof(char) * nrC);
	if (rez.model != 0)
		strcpy_s(rez.model, nrC, model);

	nrC = strlen(category) + 1;
	rez.category = malloc(sizeof(char) * nrC);
	if (rez.category != 0)
		strcpy_s(rez.category, nrC, category);

	rez.rented = 0;

	return rez;
}

void testeMasina()
{
	Car p = createCar("NT46DAN", "Skoda", "cazan");
	assert(strcmp(p.plateNo, "NT46DAN") == 0);
	assert(strcmp(p.model, "Skoda") == 0);
	assert(strcmp(p.category, "tigaie") != 0);

	destroyCar(&p);
	printf("%s", &p.plateNo);
	assert(p.plateNo == NULL);
	assert(p.model == NULL);
	assert(p.category == NULL);
	assert(p.rented == -1);
}