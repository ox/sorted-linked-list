/*
 * sorted-list.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

int compareInts(void *p1, void *p2) {
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2) {
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2) {
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

int main() {
  struct SortedList * sl = SLCreate(compareInts);
  struct SortedListIterator * iter = NULL;
  char * input = malloc(256);
  char * next_item = NULL;
  int num = 0;
  int * tmp = NULL;
  
  while (gets(input), strcmp(input, "quit") != 0) {
    num = atoi(input);
    tmp = malloc(sizeof(int));
    *tmp = num;
    
    SLInsert(sl, tmp);
    
    iter = SLCreateIterator(sl);
    
    while (next_item = SLNextItem(iter), next_item != NULL) {
      printf("%i ", *next_item);
    }
    
    puts("");
    
    SLDestroyIterator(iter);
  }
  
  SLDestroy(sl);
}
