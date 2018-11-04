#include <stdio.h>
#include <stdlib.h>

typedef struct PascalList{
	int **array; //dynamic array
	int size;	//how much is in
	int capacity;	//current maximum size
}PascalList;

//generate a new PascalList
PascalList *initPascalList(int size);

//prints out row based on term. If row does not exist generate row.
void printPascalRow(PascalList *list, int term);
int *generatePascalRow(PascalList *list, int term);
void expandList(PascalList *list, int term);
void printPascalsTriangle(PascalList *list, int term);
int combination(PascalList *list, int n, int k);
int main(){
	PascalList *test = initPascalList(4); 
	printf("Hello World\n");

	//printf("Value is: %d\n", test->array[2]);

	//printPascalRow(test, 0);

	printPascalRow(test, 3);
	printPascalRow(test, 2);
	//printf("Now checking 8\n");
	printPascalRow(test, 8);
	printPascalRow(test, 24);
	printPascalsTriangle(test, 24);

	printf("The combination 3 chooses 2 is %d\n", combination(test, 3, 2));
	printf("The combination 25 chooses 24 is %d\n", combination(test, 25, 24));
	printPascalRow(test, 25);
	return 0;
}

PascalList *initPascalList(int size){
	if(size < 2){
		size = 10;
	}

	PascalList *out = malloc(sizeof(*out));
	if(!out){
		printf("Out of memory\n");
		return NULL;
	}

	out->size = 2;
	out->capacity = 2*size;
	out->array = calloc((2*size), sizeof(int*));

	if(!(out->array)){
		printf("Out of memory");
		return NULL;
	}


	out->array[0] = malloc(sizeof(int) * 1);
	out->array[1] = malloc(sizeof(int) * 2);

	if(!(out->array[0])|| !(out->array[1])){
		printf("Out of memory");
		return NULL;
	}

	out->array[0][0] = out->array[1][0] = out->array[1][1] = 1;
	return out;
}


void printPascalRow(PascalList *list, int term){
	if(!list || !(list->array)){
		printf("No list.\n");
		return;
	}

	if(term < 0){
		printf("Invalid term\n");
		return;
	}
	//printf("Term is %d Capacity is %d\n",term, list->capacity );
	if(term >= list->capacity){
		//printf("Going into expandList\n");
		expandList(list, term);
	}
	

	//if term row does not exist generate it
	if(!list->array[term]){
		//printf("Entering from ppr\n");
		list->array[term] = generatePascalRow(list, term);
	}
	
	//print out Row
	if(list->array[term]){
		for(int i = 0; i < term+1; i++){
			printf("%d ", list->array[term][i]);
		}
		printf("\n");
	}
	else{
		printf("Pascal row does not exit\n");
		return;
	}

}

int *generatePascalRow(PascalList *list, int term){
	printf("Term %d row is generating.\n", term);
	//if list exist
	if(!list || !(list->array)){
		printf("No list.\n");
		return NULL;
	}
	//printf("Check 1\n");
	//if term is not valid
	if(term < 0){
		printf("Invalid term\n");
		return NULL;
	}
	//printf("Check 2\n");
	//check if term is within list
	if(term >= list->capacity){
		expandList(list, term);
	}
	
	//if term is already in list
	if((list->array[term])){
		return list->array[term];
	}
	//printf("Check 3\n");

	
	//check for previous term
	if(!(list->array[term-1])){
		list->array[term-1] = generatePascalRow(list, term-1);
	}
	//printf("Check 4\n");
	//create space for new row
	int *newRow = NULL;

	newRow = malloc(sizeof(int) * (term+1));
	//printf("Check 5\n");
	//check is creation was a success
	if(!newRow){
		printf("Out of memory.\n");
		return NULL;
	}
	//printf("newRow is %d, term is %d\n", newRow, term);
	//set beginning and end of list
	newRow[0] = newRow[term] = 1;

	//printf("Check 6\n");
	//fill in the rest
	for(int i = 1; i < term; i++){
		newRow[i] = list->array[term-1][i-1] + list->array[term-1][i];
		//printf("Test %d\n", newRow[i]);
	}
	//printf("Check 7\n");
	//update size
	if(term > list->size)
		list->size = term+1;

	return newRow;
}

void expandList(PascalList *list, int term){
	//check if the list exist
	if(!list || !list->array){
		printf("List does not exist.\n");
		return;
	}
	int newCap = list->capacity;
	while(term >= newCap){
		newCap *= 1.5;
	}
	printf("%d is newCap\n", newCap);
	list->array = realloc(list->array, newCap*sizeof(int*));

	for(int i = list->capacity; i < newCap; i++){
		list->array[i] = NULL;
	}
	list->capacity = newCap;
}

void printPascalsTriangle(PascalList *list, int term){
	if(!list || !(list->array)){
		printf("No list to print.\n");
		return;
	}

	for(int i = 0; i <= term; i++){
		printPascalRow(list, i);
	}
}

int combination(PascalList *list, int n, int k){
	if(!list || !(list->array)){
		printf("No list\n");
		return 0;
	}

	if(n < 0 || k < 0 || k > n+1){
		printf("N or K are out of bounds\n");
		return 0;
	}

	if(n >= list->capacity){
		expandList(list, n);
	}

	if(!list->array[n]){
		list->array[n] = generatePascalRow(list, n);
	}

	return list->array[n][k];
}