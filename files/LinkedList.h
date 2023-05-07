#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Defs.h"

typedef struct t_LinkedList *LinkedList;
typedef struct t_Node *Node;

status deleteNode(LinkedList sd, element val);//gets 2 ptrs to list and to elment of node, and returns a status if the node was successfully deleted.
LinkedList createLinkedList(copyFunction copyf, freeFunction freef,printFunction printf,equalFunction compf);//gets the info needed for a list and returns a ptr to the new list.
void destroyList(LinkedList sd);//gets a ptr to list and destroys the list.
status appendNode(LinkedList sd, element val);//gets 2 ptrs to list and to elment of node, and returns a status if the node was successfully added.
void displayList(LinkedList sd);//gets a ptr to list and displays the list.
element searchByKeyInList(LinkedList sd, element val);//gets 2 ptrs to list and to a name of a heap, and returns a ptr to element of the heap which have the name given.
element getHead (LinkedList sd);//gets a ptr to list and returns a ptr to element of the head of the list.
element getNext (Node sd);//gets a ptr to node in the list and returns a ptr to element of the head of the list.
element getData (Node sd);//gets a ptr to node in the list and returns a ptr to element of the head of the list.
#endif /* LINKEDLIST */
