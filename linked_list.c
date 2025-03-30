#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{ 
  struct list_node * n = malloc(sizeof(struct list_node));
  n->next = NULL;
  n->value = value;
  return n; 
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node * i = new_node(value);
  i->next = list->head;
  list->head = i;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node * i = new_node(value);
  struct list_node * p = list->head;
  while(p->next!=NULL)
  {
    p=p->next;
  }
  p->next = i;
}

size_t remove_from_head(struct linked_list *list) 
{
  struct list_node* p = list->head;
  list->head = p->next;
  free(p);
  return ((list->head)->value); 
}

size_t remove_from_tail(struct linked_list *list) 
{ 
  struct list_node* p = (list->head)->next;
  struct list_node* q = list->head;
  while(p->next!=NULL)
  {
    p=p->next;
    q=q->next;
  }
  free(p);
  q->next=NULL;
  return q->value; 
}

void free_list(struct linked_list list) 
{
  struct list_node* p = (list.head)->next;
  struct list_node* q = list.head;
  while(p!=NULL)
  {
    free(q);
    q=p;
    p=p->next;
  }
  free(q);
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
