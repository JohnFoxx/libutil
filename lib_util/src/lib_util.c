/*
 ============================================================================
 Name        : lib_util.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "UList.h"
#include "UType.h"

static int dumpNum = 0;

void dumpWagoon(ULWagoon *wag,int pos) {
	printf("Wagoon %d: %p|",pos,wag);
	printf("Content : %d|",*((int*)wag->content));
	printf("NextWagoonAdress: %p\n",wag->next_wagoon);
}

void dumpList(UList* list)
{
	ULWagoon *current = NULL;
	int pos = 0;
	dumpNum++;
	printf("DUMP NUMBER %d--------\n",dumpNum);
	printf("List : %p\n",list);
	printf("\t>List Size: %d\n",list->size);
	printf("\t>List first: %p\n",list->first_wagoon);
	printf("\t>List first: %p\n",list->last_wagoon);
	current = list->first_wagoon;
	while(current != NULL) {
		dumpWagoon(current,pos);
		current = current->next_wagoon;
		pos++;
	}

}

int main(void) {

	UList* test = NULL;
	int data1 = 1;
	int data2 = 2;
	int data3 = 3;
	int data4 = 4;

	test = UListCreate();
	dumpList(test);
	UListPushAt(test,0,&data1);
	UListPushAt(test,0,&data2);
	UListPushAt(test,1,&data3);
	UListPushAt(test,0,&data4);
	dumpList(test);
	printf("GET AT %d is %d\n",0,*(int*)UListGetAt(test,0));
	printf("GET AT %d is %d\n",1,*(int*)UListGetAt(test,1));
	printf("GET AT %d is %d\n",2,*(int*)UListGetAt(test,2));
	printf("GET AT %d is %d\n",3,*(int*)UListGetAt(test,3));
	UListDestroy(test);
	dumpList(test);

}
