#include "Pokemon.h"

/*init Bio_Info*/
Info* initBio(float height, float weight, int attack)
{
	Info* pointer = malloc(sizeof(Info));
	if (!pointer)
	{
		return NULL;
	}
	pointer->height=height;
	pointer->weight=weight;
	pointer->attack=attack;
	return pointer;
}

/*init Pokemon*/
Poke* initPoke(char *name, char *species, Type *ptrT, float hieght, float weight, int attack)
{
	Poke* pointer=malloc(sizeof(Poke));
	if (!pointer)
	{
		return NULL;
	}

	//name of pokemon
	pointer->name=(char*)malloc(strlen(name)+1);
	if (!pointer->name)
	{
		free(pointer);
		return NULL;
	}
	strcpy(pointer->name,name);

	//species info
	pointer->species=(char*)malloc(strlen(species)+1);
	if (!pointer->species)
	{
		free(pointer->name);
		free(pointer);
		return NULL;
	}
	strcpy(pointer->species,species);

	//name of type
	if (ptrT)
	{
		pointer->nameT=ptrT;
	}
	pointer->nameT->howMany+=1;
	//bio info
	pointer->infoB=initBio(hieght,weight,attack);
	if (!pointer->infoB)
	{
		free(pointer->name);
		free(pointer->species);
		free(pointer);
		return NULL;
	}
	return pointer;
}
/*init list of Types*/
Type** initTypess(int numOfTypes)
{
	Type** types=(Type **)malloc(numOfTypes*sizeof(Type*));
	if(!types)
	{
		return NULL;
	}
	return types;
}

/*init Pokemon_Type*/
Type* initType(char *name)
{
	Type* pointer = malloc(sizeof(Type));
	if (!pointer)
	{
		return NULL;
	}
	pointer->name=(char*)malloc(strlen(name)+1);
	if (!pointer->name)
	{
		free(pointer);
		return NULL;
	}
	strcpy(pointer->name,name);
	pointer->howMany=0;
	pointer->effective_against_me=initTypess(0);
	if (!pointer->effective_against_me)
	{
		free(pointer->name);
		free(pointer);
		return NULL;
	}
	pointer->sizeAgainstMe=0;
	pointer->effective_against_others=initTypess(0);
	if (!pointer->effective_against_others)
	{
		free(pointer->name);
		free(pointer->effective_against_me);
		free(pointer);
		return NULL;
	}
	pointer->sizeAgainstOthers=0;
	return pointer;
}

/*add effective against me*/
status addAgainstMe(Type *a, Type *b)
{
	if (a && b)
	{
		int size=a->sizeAgainstMe+1;
		a->effective_against_me=(Type **)realloc(a->effective_against_me,size*sizeof(Type*));
		if(!a->effective_against_me)
		{
			return memoryFail;
		}
		a->sizeAgainstMe=size;
		a->effective_against_me[size-1]=b;
		return success;
	}
	return failure;
}

/*add effective against others*/
status addAgainstOthers(Type *a, Type *b)
{
	if (a && b)
	{
		int size=a->sizeAgainstOthers+1;
		a->effective_against_others=(Type **)realloc(a->effective_against_others,size*sizeof(Type*));
		if(!a->effective_against_others)
		{
			return memoryFail;
		}
		a->sizeAgainstOthers=size;
		a->effective_against_others[size-1]= b;
		return success;
	}
	return failure;
}

///*delete effective against me*/
//status deleteAgainstMe(Type *a, char *b)
//{
//    if(a && b && a->effective_against_me)
//    {
//        int i=0;
//        while(i < a->sizeAgainstMe)
//        {
//            if (strcmp(a->effective_against_me[i]->name,b)==0) //equal strings
//            {
//                while(i < a->sizeAgainstMe-1 && a->sizeAgainstMe!=1)
//                {
//                    a->effective_against_me[i]=a->effective_against_me[i+1];//shift left
//                    i++;
//                }
//                a->sizeAgainstMe-=1;
//                if (a->sizeAgainstMe==0)
//                {
//                    free(a->effective_against_me);
//                    a->effective_against_me=initTypess(0);
//                }
//                else
//                {
//                    a->effective_against_me=realloc(a->effective_against_me,a->sizeAgainstMe*sizeof(Type*));
//                }
//                if(!a->effective_against_me)
//                  {
//                      return memoryFail;
//                  }
//              return success;
//            }
//            else
//            {
//                i+=1;
//            }
//        }
//    }
//    return failure;
//}
//
///*delete effective against others*/
//status deleteAgainstOthers(Type *a, char *b)
//{
//    if(a && b && a->effective_against_others)
//    {
//        int i=0;
//        while(i < a->sizeAgainstOthers)
//        {
//            if (strcmp(a->effective_against_others[i]->name,b)==0) //equal strings
//            {
//                while(i < a->sizeAgainstOthers-1 && a->sizeAgainstOthers!=1)
//                {
//                    a->effective_against_others[i]=a->effective_against_others[i+1];//shift left
//                    i++;
//                }
//                a->sizeAgainstOthers-=1;
//                if (a->sizeAgainstOthers==0)
//                {
//                    free(a->effective_against_others);
//                    a->effective_against_others=initTypess(0);;
//                }
//                else
//                {
//                    a->effective_against_others=realloc(a->effective_against_others,a->sizeAgainstOthers*sizeof(Type*));
//                }
//                if(!a->effective_against_others)
//                  {
//                      return memoryFail;
//                  }
//              return success;
//            }
//            else
//            {
//                i+=1;
//            }
//        }
//    }
//    return failure;
//}

/*print Pokemon*/
status printPokemon(Poke* s)
{
	if (!s)
	{
		return failure;
	}
	Poke *a = s;
	printf("%s :\n%s, %s Type.\nHeight: %.2f m    Weight: %.2f kg    Attack: %d\n\n",a->name,a->species,a->nameT->name,a->infoB->height,a->infoB->weight,a->infoB->attack);
	return success;
}

/*print Type*/
status printType(Type *a)
{
	if (!a)
	{
		return failure;
	}
	int i;
	printf("Type %s -- %d pokemons\n",a->name,a->howMany);
	if (a->sizeAgainstMe==0 && a->sizeAgainstOthers==0)
	{
		printf("\n");
		return success;
	}
	if (a->sizeAgainstMe!=0)
	{
		printf("\tThese types are super-effective against %s:",a->name);
		for (i=0;i<a->sizeAgainstMe-1;i++)
		{
			printf("%s ,",a->effective_against_me[i]->name);
		}
		printf("%s\n",a->effective_against_me[a->sizeAgainstMe-1]->name);
	}
	if(a->sizeAgainstOthers==0)
	{
		printf("\n");
		return success;

	}
	if (a->sizeAgainstOthers!=0)
	{
		printf("\t%s moves are super-effective against:",a->name);
		for (i=0;i<a->sizeAgainstOthers-1;i++)
		{
			printf("%s ,",a->effective_against_others[i]->name);
		}
		printf("%s\n\n",a->effective_against_others[a->sizeAgainstOthers-1]->name);
	}
	return success;
}

/*free memory funcs*/
void deleteBio(Info *a)
{
	if (a)
	{
		free(a);
	}
}
void deletePoke(Poke *a)
{
	if (a)
	{
		if(a->nameT)
		{
			a->nameT->howMany-=1;
		}
		if (a->name)
		{
			free(a->name);
		}
		if (a->species)
		{
			free(a->species);
		}
		if (a->infoB)
		{
			deleteBio(a->infoB);
		}
		free(a);
	}
}
void deleteType(Type *a)
{
	if(a)
	{
		if (a->name)
		{
			free(a->name);
		}
		if (a->effective_against_me)
		{
			free(a->effective_against_me);
		}
		if (a->effective_against_others)
		{
			free(a->effective_against_others);
		}
			free(a);
	}
}





