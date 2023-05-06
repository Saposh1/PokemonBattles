#include "LinkedList.h"

struct t_Node
{
	element data;
	Node next;
};

struct t_LinkedList
{
	Node head;
	int size;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction equalFunc;
};

Node createNode(element val)
{
	if (val)
	{
		Node nd=(Node)malloc(sizeof(struct t_Node));
		if (!nd)
		{
			return NULL;
		}
		nd->data=val;
		if(!nd->data)
		{
			free(nd);
			return NULL;
		}
		nd->next=NULL;
		return nd;
	}
	return NULL;
}

status deleteNode(LinkedList sd, element val)
{
	if (sd && val)
	{
		Node curr=sd->head;
		Node prev=sd->head;
		int i=0;
		while (i<sd->size)
		{
			if (sd->equalFunc(curr->data,val)==0)//curr is the node to delete
			{
				if(prev==sd->head && sd->size>1)//the node we delete is the head
				{
					sd->head=prev->next;//change the head pointer.
				}
				else if(i!=sd->size-1)//the node we want to delete isnt in the end
				{
					prev->next=curr->next;//change of pointers.
				}
				sd->freeFunc(curr->data);
				sd->size-=1;
				free(curr);
				return success;
			}
			else
			{
				prev=curr;
				curr=curr->next;
				i++;
			}
		}
	}
	return failure;//didnt found the elem.
}

LinkedList createLinkedList(copyFunction copyf, freeFunction freef,printFunction printf,equalFunction compf)
{
	if (copyf && freef && printf && compf)
	{
		LinkedList list=(LinkedList)malloc(sizeof(struct t_LinkedList));
		if (!list)
		{
			return NULL;
		}
		list->head=NULL;
		list->size=0;
		list->copyFunc=copyf;
		list->freeFunc=freef;
		list->printFunc=printf;
		list->equalFunc=compf;
		return list;
	}
	return NULL;
}

void destroyList(LinkedList sd)
{
	if(sd)
	{
		Node curr;
		while(sd->head!=NULL)//list not empty
		{
			curr=sd->head;
			sd->head=curr->next;
			if(sd->freeFunc)
			{
				sd->freeFunc(curr->data);
			}
			free(curr);
		}
		free(sd);
	}
}

status appendNode(LinkedList sd, element val)
{
	if (sd && val)
	{
		if(sd->size==0)//no head to the list - add val as head node.
		{
			element new=sd->copyFunc(val);
			sd->head=createNode(new);
			if(!sd->head)
			{
				return memoryFail;
			}
			sd->size+=1;
			return success;
		}
		else//list has more than one node
		{
			int i=0;
			Node curr=sd->head;
			while(i<sd->size-1)//get to the end of the list
			{
				curr=curr->next;
				i++;
			}
			element new=sd->copyFunc(val);
			curr->next=createNode(new);//adds new node to the end of the list
			if(!curr)
			{
				return memoryFail;
			}
			sd->size+=1;
			return success;
		}
	}
	return failure;
}

void displayList(LinkedList sd)
{
	if(sd)
	{
		Node curr=sd->head;
		int i =0;
		while(i<sd->size)
		{
			sd->printFunc(curr->data);
			curr=curr->next;
			i++;
		}
	}
}
element searchByKeyInList(LinkedList sd, element val)
{
	if(sd && val)
	{
		Node curr =(Node)sd->head;
		char *cat=(char *)val;
		int i=0;
		while(i<sd->size)
		{
			if(sd->equalFunc(curr->data,cat)==0)
			{
				return curr->data;
			}
			curr=curr->next;
			i++;
		}
	}
	return NULL;
}

element getHead (LinkedList sd)
{
	if (sd)
	{
		return sd->head;
	}
	return NULL;
}
element getNext (Node sd)
{
	if (sd)
	{
		return sd->next;
	}
	return NULL;
}
element getData (Node sd)
{
	if(sd)
	{
		return sd->data;
	}
	return NULL;
}

