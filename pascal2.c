#include <stdio.h>
#include <stdlib.h>

/*
Written By: Adenike Adeyemi
pascal2.c

A short program that generates Pascals triangle based on the term given.
The program can print a Row
Print the whole triange
Print out a single term or combination.

This version is a more spacially optimized version of the original pascal.c
the amount of space needed to store the triangle is cut in half because the triange is semmetrical

*/


typedef struct PascalList{
	int **array; //dynamic array
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
	PascalList *test2 = NULL;
	printf("Hello World\n");

	//printf("Value is: %d\n", test->array[2]);

	printPascalRow(test, -1);

	printPascalRow(test, 2);
	printPascalRow(test2, 3);
	//printf("Now checking 8\n");
	printPascalRow(test, 4);
	printPascalRow(test2, 24);
	printPascalsTriangle(test, -24);
	printPascalsTriangle(test, 24);
	printf("The combination 3 chooses 2 is %d\n", combination(test, -3, 2));
	printf("The combination 25 chooses 24 is %d\n", combination(test, 25, 26));
	printPascalRow(test, 25);
	return 0;
}

//This function initializes Pascals triangle
PascalList *initPascalList(int size){
	//if size is not big enough default size to 10;
	if(size < 2){
		size = 10;
	}

	//allocate size for the PascalList struct
	PascalList *out = malloc(sizeof(*out));
	
	//check if there is enough memory
	if(!out){
		printf("Out of memory\n");
		return NULL;
	}

	//set capasity to double the input size
	out->capacity = 2*size;
	//create array with size given
	out->array = calloc((2*size), sizeof(int*));

	//check if there is enough memory
	if(!(out->array)){
		printf("Out of memory");
		return NULL;
	}

	//allocate space the first two rows of the triangle
	out->array[0] = malloc(sizeof(int) * 1);
	out->array[1] = malloc(sizeof(int) * 1);

	//check if there is enough memory
	if(!(out->array[0])|| !(out->array[1])){
		printf("Out of memory");
		return NULL;
	}
	//set data
	out->array[0][0] = out->array[1][0] = 1;

	//return Pascal Triangle
	return out;
}

//This function will print out a row of the triangle
void printPascalRow(PascalList *list, int term){
	int i = 0;
	//check if the list exists
	if(!list || !(list->array)){
		printf("No list.\n");
		return;
	}

	//check if term is valid
	if(term < 0){
		printf("Invalid term\n");
		return;
	}
	//check if PascalList needs to expand
	if(term >= list->capacity){
		expandList(list, term);
	}
	
	//if term row does not exist generate it
	if(!list->array[term]){
		list->array[term] = generatePascalRow(list, term);
	}
	
	//print out Row if term exists
	if(list->array[term]){
		//prints first half
		for(i = 0; i < (term+1)/2; i++){
				printf("%d ", list->array[term][i]);
			
		}
		//prints middle term if needed
		if(term%2 == 0){
			
			printf("%d ", list->array[term][i]);	
		}
		i--;
		//prints last half
		for(; i >= 0 ; i--){
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
	int size = 0;
	int i = 0;
	printf("Term %d row is generating.\n", term);
	//if list exist
	if(!list || !(list->array)){
		printf("No list.\n");
		return NULL;
	}
	
	//if term is not valid
	if(term < 0){
		printf("Invalid term\n");
		return NULL;
	}
	
	//check if term is within list
	if(term >= list->capacity){
		expandList(list, term);
	}
	
	//if term is already in list
	if((list->array[term])){
		return list->array[term];
	}
	
	//check for previous term
	if(!(list->array[term-1])){
		list->array[term-1] = generatePascalRow(list, term-1);
	}
	
	//create space for new row
	size = (term/2)+1;
	int *newRow = NULL;

	newRow = malloc(sizeof(int) * size);
	
	//check is creation was a success
	if(!newRow){
		printf("Out of memory.\n");
		return NULL;
	}
	
	//set beginning and end of list
	newRow[0] = 1;

	//fill in the rest
	for(i = 1; i < size-1; i++){
				
		newRow[i] = list->array[term-1][i-1] + list->array[term-1][i];
	}

	//handels how to fill in last unique term
	if(term%2 == 0){
		newRow[i] = 2*list->array[term-1][i-1];
	}
	else{
		newRow[i] = list->array[term-1][i-1] + list->array[term-1][i];
	}
	
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

	if(k > n/2){
		k = n - k;
	}

	return list->array[n][k];
}