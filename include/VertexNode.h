#ifndef LINEDRAW_VERTEXNODE_H
#define LINEDRAW_VERTEXNODE_H
#include "../include/Color.h"
#include "../include/Vector.h"

typedef struct vertexnode {
  Vector v;
  Color c;
  struct vertexnode *next;
  struct vertexnode *prev;

} VertexNode;

VertexNode *VN_new(Vector v, Color c);
VertexNode *VN_push(VertexNode *head, Vector v, Color c);
VertexNode *VN_pop(VertexNode *head);
Vector VN_top(VertexNode *head);
void VN_display(VertexNode *head, char *label);
VertexNode *VN_insert(VertexNode *head, VertexNode *t, Vector v, Color c);
VertexNode *VN_remove(VertexNode *head, VertexNode *t);
#endif