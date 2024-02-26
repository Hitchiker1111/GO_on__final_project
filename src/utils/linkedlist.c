#include "../../include/utils/linkedlist.h"

void InitList(LinkedList *list)
{
  list->head = NULL;
  list->tail = NULL;
}

void FreeList(LinkedList *list)
{
  if (list->head == NULL)
  {
    return;
  }

  Node *cur = list->head;
  Node *next;

  do
  {
    next = cur->next;
    free(cur);
    cur = next;
  } while (cur != NULL && cur != list->head);
}

void Append(LinkedList *list, int x, int y)
{
  Node *node = malloc(sizeof (Node));
  if (node == NULL)
  {
    SDL_Log("Allocation failed!");
    exit(EXIT_FAILURE);
  }

  node->pos.x = x, node->pos.y = y;

  if (IsEmpty(list))
    list->head = node;
  else
    list->tail->next = node;
  list->tail = node;
  list->tail->next = list->head;
  list->num += 1;
}

bool IsEmpty(LinkedList *list)
{
  return list->head == NULL;
}

bool IsSingleton(LinkedList *list)
{
  return !IsEmpty(list) && list->head == list->tail;
}

void Delete(LinkedList *list, Node *prev)
{
  if (IsEmpty(list))
    return;

  if (IsSingleton(list))
  {
    free(list->head);
    InitList(list);
    return;
  }

  Node *cur = prev->next;
  Node *next = cur->next;

  if (cur == list->head)
    list->head = next;
  if (cur == list->tail)
    list->tail = prev;

  prev->next = next;
  free(cur);

  list->num -= 1;
}