
#ifndef BATTLEBYCATEGORY_H_
#define BATTLEBYCATEGORY_H_
#include "Defs.h"

typedef struct battle_s* Battle;

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement);
//get info to battle and returns a ptr to the new battle created.
status destroyBattleByCategory(Battle b);//gets ptr to battle and returns a status if the battle was successfully destroyed.
status insertObject(Battle b, element elem);//gets ptr to battle and ptr to element of char * (name of heap) and returns a status if the element was successfully added to battle.
void displayObjectsByCategories(Battle b);//gets ptr to battle and prints the battle.
element removeMaxByCategory(Battle b,char* category);//gets ptr to battle and ptr to element of char * (name of heap) and returns an element ptr to the first element in the list.  .
int getNumberOfObjectsInCategory(Battle b,char* category);//gets ptr to battle and ptr to element of char * (name of heap) and returns the size of the heap.
element fight(Battle b,element elem);//gets ptr to battle and ptr to element of pokemon the pokemon which win in the fight.

#endif /* BATTLEBYCATEGORY_H_ */
