#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"


struct battle_s{
	int capacity;
	int categories;
	char* categorysn;
	equalFunction equalFunc;
	copyFunction copyFunc;
	freeFunction freeFunc;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
	printFunction printFunc;
	LinkedList list;
};

element copyHelem(element elem)
{
	MaxHeap s1=(MaxHeap)elem;
	return (element)copyHeap(s1);
}

int equalHelem(element elem1,element elem2)
{
	MaxHeap s1=(MaxHeap)elem1;
	char* s2=(char*)elem2;
	return equalHeap(s1,s2);
}

status printHelem(element elem)
{
	MaxHeap s1=(MaxHeap)elem;
	return printHeap(s1);
}

status destroyHelem(element elem)
{
	MaxHeap s1=(MaxHeap)elem;
	return destroyHeap(s1);
}

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{
	if(equalElement && copyElement && freeElement && getCategory && getAttack && printElement)
	{
		Battle ptr=(Battle)malloc(sizeof(struct battle_s));
		if(!ptr)
		{
			return NULL;
		}
		LinkedList list=createLinkedList((copyFunction)copyHelem,(freeFunction)destroyHelem,(printFunction)printHelem,(equalFunction)equalHelem);
		if(!list)
		{
			free(ptr);
			return NULL;
		}
		ptr->list=list;
		ptr->capacity=capacity;
		ptr->categories=numberOfCategories;
		ptr->categorysn=(char *)malloc((strlen(categories)+1)*sizeof(char));
		if(!ptr->categorysn)
		{
			destroyList(list);
			free(ptr);
			return NULL;
		}
		strcpy(ptr->categorysn,categories);
		char *tok=strtok(categories,",\n\r");
		int i=0;
		while (i<numberOfCategories)
		{
			MaxHeap heap=createHeap(tok,capacity,copyElement,freeElement,printElement,equalElement);
			if(appendNode(ptr->list,heap)==memoryFail)
			{
				destroyHeap(heap);
				free(ptr->categorysn);
				destroyList(list);
				free(ptr);
				return NULL;
			}
			destroyHeap(heap);
			tok=strtok(NULL,",\n\r");
			i++;
		}
		ptr->equalFunc=equalElement;
		ptr->copyFunc=copyElement;
		ptr->freeFunc=freeElement;
		ptr->getCategory=getCategory;
		ptr->getAttack=getAttack;
		ptr->printFunc=printElement;
		return ptr;
	}
	return NULL;
}

status destroyBattleByCategory(Battle b)
{
	if(b)
	{
		destroyList(b->list);
		free(b->categorysn);
		free(b);
		return success;
	}
	return failure;
}

status insertObject(Battle b, element elem)//to fix
{
	if(b && elem)
	{
		char * categ;
		categ=b->getCategory(elem);
		MaxHeap heap=NULL;
		status stat;
		heap=searchByKeyInList(b->list,categ);
		if(!heap)
		{
			return failure;
		}
		stat=insertToHeap(heap,elem);
		return stat;
	}
	return failure;
}

void displayObjectsByCategories(Battle b)
{
	if (b && b->list)
	{
		displayList(b->list);
	}
}

element removeMaxByCategory(Battle b,char* category)
{
	if (b && category)
	{
		MaxHeap heap=NULL;
		heap=searchByKeyInList(b->list,category);
		if (!heap)
		{
			return NULL;
		}
		return PopMaxHeap(heap);

	}
	return NULL;
}

int getNumberOfObjectsInCategory(Battle b,char* category)
{
	if (b && category)
	{
		MaxHeap heap=NULL;
		heap=searchByKeyInList(b->list,category);
		if (!heap)
		{
			return 0;
		}
		return getHeapCurrentSize(heap);
	}
	return 0;
}

element fight(Battle b,element elem)
{
	if (b && elem)
	{
		if(b->capacity<1)//no elements to fight against
		{
			return NULL;
		}
		LinkedList list=b->list;
//		Node curr=getHead(list);
//		if (!curr)
//		{
//			return NULL;
//		}
		element save=NULL,winner=NULL;
		int *attackFirst=(int *)malloc(sizeof(int));
		if(!attackFirst)
		{
			return NULL;
		}
		int *attackSecond=(int *)malloc(sizeof(int));
		if(!attackSecond)
		{
			free(attackFirst);
			return NULL;
		}
		int finalFirst,finalSecond;
		MaxHeap heap=NULL;
		int i=0,curRes=0,Final=-2222222;
		char* tok2=(char *)malloc((strlen(b->categorysn)+1)*sizeof(char));
		if(!tok2)
		{
			free(attackFirst);
			free(attackSecond);
			return NULL;
		}
		strcpy(tok2,b->categorysn);
		element tok=(element)strtok(tok2,",\n\r");
		for (i=0;i<b->categories;i++)
		{
			heap=(MaxHeap)searchByKeyInList(list, tok);
			tok=strtok(NULL,",\n\r");
			save=TopMaxHeap(heap);
			if(save)
			{
				curRes=b->getAttack(save,elem,attackFirst,attackSecond);
				if(curRes>Final)//assigment of curRes
				{
					if(winner !=NULL)//if there is ptr of Final
					{
						b->freeFunc(winner);
					}
					Final=curRes;
					winner=save;
					finalFirst=*attackFirst;
					finalSecond=*attackSecond;
				}
				else//no assigment of curRes
				{
					b->freeFunc(save);
				}
			}
		}
		if(tok2)
		{
			free(tok2);
		}
		free(attackFirst);
		free(attackSecond);
		if (!winner)//no pokemons to fight against
		{
			return NULL;
		}
		printf("The final battle between:\n");
		b->printFunc(elem);
		printf("In this battle his attack is :%d\n\n",finalSecond);
		printf("against ");
		b->printFunc(winner);
		printf("In this battle his attack is :%d\n\n",finalFirst);
		if (Final>0)
		{
			printf("THE WINNER IS:\n");
			b->printFunc(winner);
			return winner;
		}
		if (Final==0)
		{
			printf("IT IS A DRAW.\n");
			return winner;
		}
		printf("THE WINNER IS:\n");
		b->printFunc(elem);
		b->freeFunc(winner);
		return elem;
	}
	return NULL;
}
