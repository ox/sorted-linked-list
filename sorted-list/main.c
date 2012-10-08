/*
 * sorted-list.c
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

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

int test_vanilla() {
  struct SortedList * sl = SLCreate(compareInts);
  struct SortedListIterator * iter = NULL;
  
  void * item = NULL;
  int * number_space = NULL;
  
  int i = 0;
  
  for (; i < 5; i++) {
    number_space = malloc(sizeof(int));
    *number_space = i;
    SLInsert(sl, number_space);
  }
  
  i = 0;
  iter = SLCreateIterator(sl);
  
  while ((item = SLNextItem(iter))) {
    i ++;
  }
  
  SLDestroy(sl);
  SLDestroyIterator(iter);
  
  assert(i == 5);
  
  return 1;
}

int test_incomplete_iterator() {
  struct SortedList * sl = SLCreate(compareInts);
  struct SortedListIterator * iter = NULL;
  
  void * item = NULL;
  int * number_space = NULL;
  
  int i = 0;
  
  for (; i < 5; i++) {
    number_space = malloc(sizeof(int));
    *number_space = i;
    SLInsert(sl, number_space);
  }
  
  i = 0;
  iter = SLCreateIterator(sl);
  
  while ((item = SLNextItem(iter)) && i != 3) {
    i ++;
  }
  
  SLDestroy(sl);
  SLDestroyIterator(iter);
  
  assert(i == 3);
  
  return 1;
}

int test_multiple_iterators() {
  struct SortedList * sl = SLCreate(compareInts);
  struct SortedListIterator * iter = NULL;
  struct SortedListIterator * iter2 = NULL;
  
  void * item = NULL;
  void * item2 = NULL;
  
  int * number_space = NULL;
  int i = 0;
  
  for (; i < 5; i++) {
    number_space = malloc(sizeof(int));
    *number_space = i;
    SLInsert(sl, number_space);
  }
  
  i = 0;
  iter = SLCreateIterator(sl);
  iter2 = SLCreateIterator(sl);
  
  while ((item = SLNextItem(iter)) && (item2 = SLNextItem(iter2)) && (item == item2)) {
    i ++;
  }
  
  SLDestroy(sl);
  SLDestroyIterator(iter);
  SLDestroyIterator(iter2);
  
  assert(i == 5);

  return 1;
}

int test_multiple_iterators_with_failure() {
  struct SortedList * sl = SLCreate(compareInts);
  struct SortedListIterator * iter = NULL;
  
  void * item = NULL;
  
  int i = 1;
  int * int_space = malloc(sizeof(int));
  
  *int_space = i;
  SLInsert(sl, int_space);
  
  i = 0;
  iter = SLCreateIterator(sl);

  SLRemove(sl, &int_space);
  
  i = 0;
  
  while (item = SLNextItem(iter), item) {
    i ++;
  }
  
  SLDestroy(sl);
  SLDestroyIterator(iter);
    
  return 1;
}

int main() {
  int r = test_vanilla() &&
         test_incomplete_iterator() &&
         test_multiple_iterators() &&
         test_multiple_iterators_with_failure();
  
  printf("%i\n", r);
  return r;
}
