#include "MaxHeap.h"

struct t_MaxHeap
{
	char *name;
	int size;
	int maxSize;
	element *array;
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printFunc;
	equalFunction equalFunc;

};

MaxHeap createHeap(char *name,int maxSize,copyFunction copyf, freeFunction freef,printFunction printf,equalFunction compf)
{
	if (copyf && freef && printf && compf)
	{
		MaxHeap heap=(MaxHeap)malloc(sizeof(struct t_MaxHeap));
		if(!heap)
		{
			return NULL;
		}
		heap->name=(char *)malloc((strlen(name)+1)*sizeof(char));
		if(!heap->name)
		{
			free(heap);
			return NULL;
		}
		strcpy(heap->name,name);
		heap->size=0;
		heap->maxSize=maxSize;
		heap->array=(element*)malloc(1*sizeof(element));
		if(!heap->array)
		{
			free(heap->name);
			free(heap);
			return NULL;
		}
		heap->copyFunc=copyf;
		heap->freeFunc=freef;
		heap->printFunc=printf;
		heap->equalFunc=compf;
		return heap;
	}
	return NULL;
}

status destroyHeap(MaxHeap sd)
{
	if(sd)
	{
		int i=0;
		if(sd->array)
		{
			for(i=1;i<=sd->size;i++)
			{
				sd->freeFunc(sd->array[i]);
			}
		}
		if(sd->name)
		{
			free(sd->name);
		}
		//free(sd->array[0]);//a cell with no ptr inside
		free(sd->array);
		free(sd);
		return success;
	}
	return failure;
}

element TopMaxHeap(MaxHeap sd)
{
	if(sd && sd->size!=0)
	{
		return sd->copyFunc(sd->array[1]);
	}
	return NULL;
}

char *getHeapId(MaxHeap sd)
{
	if(sd)
	{
		return sd->name;
	}
	return NULL;
}

int getHeapCurrentSize(MaxHeap sd)
{
	if(sd)
	{
		return sd->size;
	}
	return 0;
}

int parent(int i)
{
	if (i!=0)
	{
		return (int)(i/2);
	}
	return 0;
}

MaxHeap maxHeapify(MaxHeap sd, int i)
{
	if(sd && i!=0)
	{
		int l,r,largest;
		l=i*2;//left
		r=i*2+1;//right
		if (l<=sd->size && sd->equalFunc(sd->array[l],sd->array[i])==1)
		{
			largest=l;
		}
		else
		{
			largest=i;
		}
		if (r<=sd->size && sd->equalFunc(sd->array[r],sd->array[largest])==1)
		{
			largest=r;
		}
		if (largest!=i)
		{
			element temp=sd->array[largest];
			sd->array[largest]=sd->array[i];
			sd->array[i]=temp;
			maxHeapify(sd,largest);
		}
		return sd;
	}
	return NULL;
}

MaxHeap buildMaxHeap(MaxHeap sd)
{
	if(sd && sd->size!=0)
	{
		int i;
		if (sd->size==1)
		{
			return sd;
		}
		for(i=(int)(sd->size/2);i>0;i--)
		{
			sd=maxHeapify(sd,i);
		}
		return sd;
	}
	return NULL;
}

element PopMaxHeap(MaxHeap sd)
{
	if (sd && sd->size!=0)
	{
		element max = sd->array[1];
		sd->array[1]=sd->array[sd->size];
		sd->size-=1;
		sd->array=(element*)realloc(sd->array,sizeof(element)*(sd->size+1));
		if (!sd->array)
		{
			return NULL;
		}
		sd=maxHeapify(sd,1);
		if(!sd)
		{
			return NULL;
		}
		return max;
	}
	return NULL;
}

MaxHeap insertionMax(MaxHeap sd, int i,element val)
{
	if(sd && val)
	{
		if(sd->equalFunc(val,sd->array[sd->size])==-1)//array is max sorted
		{
			return sd;
		}
		while(i>1 && sd->equalFunc(sd->array[parent(i)],sd->array[i])==-1)
		{
			element temp=sd->array[parent(i)];
			sd->array[parent(i)]=sd->array[i];
			sd->array[i]=temp;
			i=parent(i);
		}
		return sd;
	}
	return NULL;
}

status insertToHeap(MaxHeap sd,element val)
{
	if(sd && sd->size<=sd->maxSize)
	{
		sd->size+=1;
		element temp;
		temp=(element*)realloc(sd->array,(sd->size+1)*sizeof(element));
		if (!temp)
		{
			return memoryFail;
		}
		sd->array=temp;
		element new=sd->copyFunc(val);
		if (!new)
		{
			return memoryFail;
		}
		sd->array[sd->size]=new;
		if(sd->size==1)//array is now of size 1 - done
		{
			return success;
		}
		sd=insertionMax(sd,sd->size,new);
		if(sd)
		{
			return success;
		}
	}
	return failure;
}

status printHeap(MaxHeap sd)
{
	if(sd)
	{
		printf("%s:\n", sd->name);
		if(sd->size==0)
		{
			printf("No elements.\n\n");
			return success;
		}
		int i;
		MaxHeap copy=createHeap(sd->name,sd->maxSize,sd->copyFunc,sd->freeFunc,sd->printFunc,sd->equalFunc);
		if (!copy)//no alloc.
		{
			return memoryFail;
		}
		copy->array=(element*)realloc(copy->array,sizeof(element)*(sd->size+1));
		if (!copy->array)
		{
			destroyHeap(copy);
			return memoryFail;
		}
		copy->size=sd->size;
		for (i=1;i<=sd->size;i++)
		{
			element new1=sd->copyFunc(sd->array[i]);
			if (!new1)
			{
				destroyHeap(copy);
				return memoryFail;
			}
			copy->array[i]=new1;
		}
		int counter=1;
		for (i=1;i<=sd->size;i++)
		{
			element max=PopMaxHeap(copy);
			printf("%d. ",counter);
			copy->printFunc(max);
			copy->freeFunc(max);
			counter+=1;
		}
		copy->size=0;
		destroyHeap(copy);
		return success;
	}
	return failure;
}

MaxHeap copyHeap(MaxHeap elem)
{
	if(elem)
	{
		MaxHeap s = elem;
		element res=(element)createHeap(s->name,s->maxSize,s->copyFunc,s->freeFunc,s->printFunc,s->equalFunc);
		if(!res)
		{
			return NULL;
		}
		int i=1;
		for (i=1;i<=s->size;i++)
		{
			if(insertToHeap(res,s->array[i])==memoryFail)
			{
				destroyHeap(res);
				return NULL;
			}
		}
		return (element)res;
	}
	return NULL;
}

int equalHeap(MaxHeap elem1,char* elem2)
{
	if (elem1 && elem2)
	{
		if (strcmp(elem1->name,elem2)==0)
		{
			return 0;
		}
		return 1;
	}
	return -1;
}


