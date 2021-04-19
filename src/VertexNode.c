#include "../include/VertexNode.h"
#include <stdio.h>
#include <stdlib.h>

//----------------------------------------------------
// v : vector
// c : Color defining the color of a vertex
// return value : pointer to a new VertexNode
VertexNode *VN_new(Vector v, Color c) {
  VertexNode *tmp = (VertexNode *)malloc(sizeof(VertexNode));
  tmp->c = c;
  tmp->v = v;
  tmp->next = NULL;
  tmp->prev = NULL;
  return tmp;
}

//-----------------------------------------------------------
// head : pointer which is head of linked list of VertexNodes
// precondition : head should not be null, otherwise
// new VertexNode will be created
// v : vector
// c : color
// return value : head of linked list of VertexNodes
// function puts new VertexNode to the head of VertexNodes
VertexNode *VN_push(VertexNode *head, Vector v, Color c) {
  if (head == NULL) {
    head = VN_new(v, c);
    return head;
  }
  VertexNode *t = VN_new(v, c);
  t->next = head;
  head->prev = t;
  head = t;
  return head;
}

//------------------------------------------------------------
// head : pointer which is head of linked list of VertexNodes
// t : pointer to VertexNode after which the new node will be inserted
// precondion : if t is the last, we must not insert a node after it
// v : vector representing coordinates of vertex
// c : color
// return value : head pointer of VertexNodes
VertexNode *VN_insert(VertexNode *head, VertexNode *t, Vector v, Color c) {
  if (!t->next)
    return head;
  VertexNode *tmp = VN_new(v, c);
  tmp->next = t->next;
  tmp->prev = t;
  t->next->prev = tmp;
  t->next = tmp;
  return head;
}

//-------------------------------------------------------------
// head : pointer which is head of linked list of VertexNodes
// precondition : head should not be NULL,
// otherwise small warning will occur
// return value : head of VertexNodes
// funcion removes the VertexNode on the head of VertexNodes
VertexNode *VN_pop(VertexNode *head) {
  if (head == NULL) {
    printf("No vertexes left!\n");
    return head;
  }
  VertexNode *p = head;
  head = head->next;
  free(p);
  return head;
}

//-------------------------------------------------------------
// head : pointer which is head of linked list of VertexNodes
// t : pointer to VertexNode that will be deleted
// return value : pointer to the head of the VertexNodes
VertexNode *VN_remove(VertexNode *head, VertexNode *t) {
  if (head == NULL || t == NULL) {
    printf("head or t pointing to NULL\n");
    return head;
  }
  if (t == head) {
    return VN_pop(head);
  }
  if (!t->next) {
    t->prev->next = t->next;
    free(t);
    return head;
  }
  t->prev->next = t->next;
  t->next->prev = t->prev;
  free(t);
  return head;
}

//-------------------------------------------------------------
// head : pointer which is head of linked list of VertexNodes
// precondition : head must not be NULL, otherwise
// the warning will show up
// return value : vector representing position of head pointer of VertexNodes
Vector VN_top(VertexNode *head) {
  if (head == NULL) {
    printf("VN_pop: head pointing null\n");
    exit(0);
  }
  return head->v;
}

//-------------------------------------------------------------
// head : pointer which is head of linked list of VertexNodes
// label : string representing the name for the linked list of VertexNodes
// funcion prints all the vector positions of VertexNodes
void VN_display(VertexNode *head, char *label) {
  VertexNode *p = head;
  printf("----------------%s---------------\n", label);
  while (p) {
    printf("(%f, %f)\n", p->v.x, p->v.y);
    p = p->next;
  }
}
