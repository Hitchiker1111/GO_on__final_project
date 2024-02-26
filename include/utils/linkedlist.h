#include "../common.h"

typedef struct node
{
  SDL_Point pos;
  struct node *next;
} Node;

typedef struct
{
  Node *head;
  Node *tail;
  int num;
} LinkedList;

void InitList(LinkedList *list);
void FreeList(LinkedList *List);
void Append(LinkedList *list, int x, int y);
bool IsSingleton(LinkedList *list);
void Delete(LinkedList *list, Node *prev);
bool IsEmpty(LinkedList *list);