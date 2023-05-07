#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include "Defs.h"

typedef struct t_MaxHeap *MaxHeap;

MaxHeap createHeap(char *name,int maxsize, copyFunction copyf, freeFunction freef,printFunction printf,equalFunction compf);//get the info needed for heap, and returns a ptr after
//creating the heap.
status destroyHeap(MaxHeap sd);//gets a ptr to heap, and frees the heap fields and its ptr.
element TopMaxHeap(MaxHeap sd);//gets a ptr to heap, and returns a ptr to the first element in the heap.
char *getHeapId(MaxHeap sd);//gets a ptr to heap, and returns a ptr to its name.
int getHeapCurrentSize(MaxHeap sd);//gets a ptr to heap, and returns its size.
element PopMaxHeap(MaxHeap sd);//gets a ptr to heap, and returns the first element in the heap, also delete it from the heap.
status insertToHeap(MaxHeap sd,element val);//gets a ptr to heap and to element, and returns a status if the element was successfully added to the heap.
status printHeap(MaxHeap sd);//gets a ptr to heap, and returns a status if the print of the heap was successfully done.
MaxHeap copyHeap(MaxHeap elem);
int equalHeap(MaxHeap elem1,char* elem2);
#endif /* MAXHEAP */
