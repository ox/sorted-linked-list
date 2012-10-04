#include <stdio.h>
#include <stdlib.h>
#include "sorted-list.h"

struct SortedList* SLCreate(CompareFuncT cf) {
  struct SortedList* sl = malloc(sizeof(struct SortedList));
  sl->cf = cf;
  sl->head = NULL;
  sl->size = 0;
  
  return sl;
}

void destroy_node(struct Node * node) {
  free(node->data);
  free(node);
}

void destroy_nodes(struct Node * node) {
  if (!node->next) {
    destroy_node(node);
  } else {
    destroy_nodes(node->next);
  }
}

void SLDestroy(struct SortedList* list) {
  destroy_nodes(list->head);
  free(list);
}

void swap_nodes(struct Node * a, struct Node * b) {
  void * temp_data = a->data;
  a->data = b->data;
  b->data = temp_data;
}

struct Node * sort_nodes(struct Node * head, int (*cf)(void *, void *)) {
  /* bubble sort the first element */
  struct Node * first = head, * target = head->next;
  
  while (target && cf(first->data, target->data) <= 0) {
    swap_nodes(first, target);
    target = target->next;
    first = first->next;
  }
  
  return head;
}

int sort_list(struct SortedList * list) {
  return !!(list->head = sort_nodes(list->head, list->cf));
}

int SLInsert(struct SortedList* list, void *newObj) {
  struct Node * new = malloc(sizeof(struct Node));
  
  new->data = newObj;
  new->next = list->head;
  
  list->head = new;
  list->size += 1;
  
  return sort_list(list);
}

int SLRemove(struct SortedList* list, void *newObj) {
  struct Node * prev_node = NULL, * curr_node = list->head;
  
  while (list->cf(curr_node->data, newObj) != 0 && curr_node) {
    prev_node = curr_node;
    curr_node = curr_node->next;
  }
  
  if (curr_node) {
    prev_node->next = curr_node->next;
    destroy_node(curr_node);
    
    sort_list(list);
    
    list->size -= 1;
    
    return 1;
  } else {
    return 0;
  }
}



struct SortedListIterator* SLCreateIterator(struct SortedList* list) {
  struct SortedListIterator * sli = malloc(sizeof(struct SortedListIterator));
  
  sli->sl = list;
  sli->curr_node = sli->sl->head;
  
  return sli;
}

void SLDestroyIterator(struct SortedListIterator* iter) {
  free(iter);
}

void *SLNextItem(struct SortedListIterator* iter) {
  void * data;
  
  if (iter->curr_node) {
    data = iter->curr_node->data;
    iter->curr_node = iter->curr_node->next;
    return data;
  } else {
    return NULL;
  }
}
