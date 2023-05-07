#include "BattleByCategory.h"
#include "Pokemon.h"

//cast funcs for use with elements in pokemon funcs.
int equalPokemon(element s1, element s2)
{
	if(s1 && s2)
	{
		Poke* pok1=(Poke*)s1;
		Poke* pok2=(Poke*)s2;
		if((pok1->infoB->attack)>(pok2->infoB->attack))
		{
			return 1;
		}
		else if((pok1->infoB->attack)==(pok2->infoB->attack))
		{
			return 0;
		}
		return -1;
	}
	return 2;
}

element copyPokemon(element elem)
{
	if(elem)
	{
		Poke *s = (Poke*)elem;
		element res=(element)initPoke(s->name,s->species,s->nameT,s->infoB->height,s->infoB->weight,s->infoB->attack);
		if(!res)
		{
			return NULL;
		}
		return res;
	}
	return NULL;
}

status freePokemon(element elem)
{
	if (elem)
	{
		Poke* pok1=(Poke*)elem;
		deletePoke(pok1);
		return success;
	}
	return failure;
}

status printElem(element elem)
{
	Poke* pok1=(Poke*)elem;
	return printPokemon(pok1);
}


int getAttack(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond)
{
	if(firstElem && secondElem && attackFirst && attackSecond)
	{
		Poke *s = (Poke*)firstElem;
		Poke *ss = (Poke*)secondElem;
		*attackFirst=s->infoB->attack;
		*attackSecond=ss->infoB->attack;
		int i=0,dec1=0,dec2=0;
		for (i=0;i<s->nameT->sizeAgainstMe;i++)
		{
			if(strcmp(s->nameT->effective_against_me[i]->name,ss->nameT->name)==0)
			{
				*attackFirst-=10;
				dec1=1;
				break;
			}
		}
		for(i=0;i<s->nameT->sizeAgainstOthers;i++)
		{
			if(strcmp(s->nameT->effective_against_others[i]->name,ss->nameT->name)==0)
			{
				*attackSecond-=10;
				dec2=1;
				break;
			}
		}
		for (i=0;i<ss->nameT->sizeAgainstMe;i++)
		{
			if (dec2==1)
			{
				break;
			}
			if(strcmp(ss->nameT->effective_against_me[i]->name,s->nameT->name)==0)
			{
				*attackSecond-=10;
				dec2=1;
				break;
			}
		}
		for(i=0;i<ss->nameT->sizeAgainstOthers;i++)
		{
			if (dec1==1)
			{
				break;
			}
			if(strcmp(ss->nameT->effective_against_others[i]->name,s->nameT->name)==0)
			{
				*attackFirst-=10;
				dec1=1;
				break;
			}
		}
		return ((*attackFirst)-(*attackSecond));
	}
	return 0;
}

char * getCategory(element s1)
{
	if(!s1)
	{
		return NULL;
	}
	Poke* pok1=(Poke*)s1;
	return pok1->nameT->name;
}

void deleteTypes(Type **a, int numOfTypes)
{
	if(a)
	{
		int i=0;
		for(i=0;i<numOfTypes;i++)
		{
			deleteType(a[i]);
		}
		free(a);
	}
}

/*init list of Types*/
Type** initTypes(int numOfTypes)
{
	Type** types=(Type **)malloc(numOfTypes*sizeof(Type*));
	if(!types)
	{
		return NULL;
	}
	return types;
}

Type* searchType(Type** typess,int numOfTypes, char* save)
{
	int i;
    for(i=0;i<numOfTypes;i++)//search type
    {
    	if (strcmp(typess[i]->name,save)==0)
    	{
    		break; //type found
    	}
    }
    if(i==numOfTypes)
    {
    	return NULL;
    }
    return typess[i];
}

void destruction(Battle b,int numOfTypes, Type** types)
{
	if(b)
		destroyBattleByCategory(b);
	if(types)
		deleteTypes(types,numOfTypes);

}

int main(int argc/*num of args*/,char *argv[]/*array of strings args*/)
{
	if (argc!=4)
	{
		return 0;
	}

	/*args assigment*/
	int numOfTypes=atoi(argv[1]);
	int capacityInType=atoi(argv[2]);
	char *file=argv[3];

	/*file reading*/
		FILE *fp;
		char buffer[300];
		Type **types;
		status stat;
		char *tok;
		int i=0;
		int flagMe=0;
		int flagOther=0;
		int k;
		char *name;
		char *species;
		float height;
		float weight;
		int attack;
		Type *type=NULL, *addTo=NULL,*toAdd=NULL;
		Battle b=NULL;
		char *save=NULL;
		Poke *pok;
		/*checks if file is empty*/
		if(!file)
		{
			return 0;
		}
		fp=fopen(file,"r");
		if(!fp)
		{
			return 0;
		}
		/*memory for pointers which will be created*/
		types=initTypes(numOfTypes);
		if(!types)
		{
			printf("No memory available.\n");
			fclose(fp);
			return 0;
		}
		/*Types creation*/
		fgets(buffer,300,fp);
		tok=strtok(buffer,",\r\n");
		while(tok)
		{
			if(strcmp(tok,"Types")!=0)
			{
				types[i]=initType(tok);
				if(!types[i])
				{
					printf("No memory available.\n");
					deleteTypes(types,i-1);
					fclose(fp);
					return 0;
				}
				i++;
				tok=strtok(NULL,",\n\r");
			}
			else if (numOfTypes!=0){
				fgets(buffer,300,fp);
				tok=strtok(buffer,"\r\n\t");
				save=malloc((strlen(buffer)+1)*sizeof(char));
				if (!save)
				{
					printf("No memory available.\n");
					deleteTypes(types,numOfTypes);
					fclose(fp);
					return 0;
				}
				strcpy(save,buffer);
				b=createBattleByCategory(capacityInType,numOfTypes,buffer,(equalFunction)equalPokemon,(copyFunction)copyPokemon,(freeFunction)freePokemon,(getCategoryFunction)getCategory,(getAttackFunction)getAttack,(printFunction)printElem);
				if (!b)
				{
					printf("No memory available.\n");
					deleteTypes(types,numOfTypes);
					free(save);
					fclose(fp);
					return 0;
				}
				strcpy(buffer,save);
				tok=strtok(buffer,",\r\n");
			}
			else{
				b=createBattleByCategory(capacityInType,0,buffer,(equalFunction)equalPokemon,(copyFunction)copyPokemon,(freeFunction)freePokemon,(getCategoryFunction)getCategory,(getAttackFunction)getAttack,(printFunction)printElem);
				if (!b)
				{
					printf("No memory available.\n");
					deleteTypes(types,numOfTypes);
					fclose(fp);
					return 0;
				}
				break;
			}
		}
		if(save)
		{
		free(save);
		}
		/*Add to against lists*/
		while(fgets(buffer,300,fp)&& numOfTypes!=0)
		{
			if(numOfTypes==0) // no types so no lists to add.
			{
				break;
			}
			flagMe=0;
			flagOther=0;
			tok=strtok(buffer,"\t -:,\r\n");
			if (strcmp(tok,"Types")==0) //case of no types
			{
				continue;
			}
			if (strcmp(tok,"Pokemons")==0) //done with types and their lists.
			{
				break;
			}
			addTo=searchType(types,numOfTypes,tok);
			while(tok)
			{
				if(strcmp(tok,"me")==0) //an against me list
				{
					flagMe=1;
				}
				if(strcmp(tok,"other")==0) //an against other list
				{
					flagOther=1;
				}
				if(flagMe==1 && strcmp(tok,"me")!=0)
				{
					toAdd=searchType(types,numOfTypes,tok);
					if (toAdd)
					{
						stat=addAgainstMe(addTo,toAdd);
	   		    	    if(stat==failure)
	   					{
	   		    	    	printf("No memory available.\n");
	   		    	    	destruction(b,numOfTypes,types);
//	   						destroyBattleByCategory(b);
//	   						deleteTypes(types,numOfTypes);
	   						fclose(fp);
	   						return 0;
	   					}
					}
				}
				if(flagOther==1 && strcmp(tok,"other")!=0)
				{
					toAdd=searchType(types,numOfTypes,tok);
					if (toAdd)
					{
						stat=addAgainstOthers(addTo,toAdd);
	   		    	   if(stat==failure)
	   					{
	   		    		   printf("No memory available.\n");
	   		    		   destruction(b,numOfTypes,types);
//	   						destroyBattleByCategory(b);
//	   						deleteTypes(types,numOfTypes);
	   						fclose(fp);
	   						return 0;
	   					}
					}
				}
			tok=strtok(NULL,",-:\t\r\n");
			}
		}
		/*init pokemons*/
		while(fgets(buffer,300,fp))
		{
			k=0;
			tok=strtok(buffer,",\t\r\n");
			if (strcmp(tok,"Pokemons")==0) //done with types and their lists.
			{
				continue;
			}
			while(tok)
			{
				if (k==0)
				{
					name=tok;
				}
				if(k==1)
				{
					species=tok;
				}
				if(k==2)
				{
					height=atof(tok);
				}
				if(k==3)
				{
					weight=atof(tok);
				}
				if(k==4)
				{
					attack=atoi(tok);
				}
				if(k==5)
				{
					type=searchType(types,numOfTypes,tok);
					break;
				}
				tok=strtok(NULL,",\t\r\n");
				k++;
			}
			if(type && type->howMany<capacityInType)
			{
				pok=initPoke(name,species,type,height,weight,attack);
				if(!pok)
				{
					printf("No memory available.\n");
					destruction(b,numOfTypes,types);
//					destroyBattleByCategory(b);
//					deleteTypes(types,numOfTypes);
					fclose(fp);
					return 0;
				}
				if(insertObject(b,pok)==memoryFail)
				{
					printf("No memory available.\n");
					deletePoke(pok);
					destruction(b,numOfTypes,types);
//					destroyBattleByCategory(b);
//					deleteTypes(types,numOfTypes);
					fclose(fp);
					return 0;
				}
				deletePoke(pok);
			}
		}
		fclose(fp);

/*main menu*/
char ar=1;
   while( ar != '6') {
      printf("Please choose one of the following numbers:\n");
	  printf("1 : Print all Pokemons by types\n");
      printf("2 : Print all Pokemons types\n");
      printf("3 : Insert Pokemon to battles training camp\n");
      printf("4 : Remove strongest Pokemon by type\n");
      printf("5 : Fight\n");
      printf("6 : Exit\n");
      scanf("%s", &ar);
    		  switch( ar )
    		  {
    		  case '1' :/*displayList*/
    			   	  displayObjectsByCategories(b);
    		  	  	  break;
    		  case '2' : /*print all types*/
    			  	  for(i=0;i<numOfTypes;i++)
    			  	  {
    			  		  printType(types[i]);
    			  	  }
    			  	  break;
    		  case '3' : /*insertion*/
    			  	 printf("Please enter Pokemon type name:\n");
    			  	 scanf("%s", buffer);
  			  	     save=malloc((strlen(buffer)+1)*sizeof(char));
  					 if (!save)
  					 {
  						printf("No memory available.\n");
  						destruction(b,numOfTypes,types);
//  						destroyBattleByCategory(b);
//  						deleteTypes(types,numOfTypes);
  						return 0;
  					 }
  					 strcpy(save,buffer);
  					 Type* type=searchType(types,numOfTypes,save);
    			  	 if (!type)//type not found
    			  	 {
    			  		 printf("Type name doesn't exist.\n");
    			  		 free(save);
    			  		 break;
    			  	 }
     				if(getNumberOfObjectsInCategory(b,type->name)==capacityInType)
     				{
     					printf("Type at full capacity.\n");
     					free(save);
     					break;
     				}
    			  	 free(save);
    			 	 printf("Please enter Pokemon name:\n");
    			  	 scanf("%s", buffer);
  			  	     name=malloc((strlen(buffer)+1)*sizeof(char));
  					 if (!name)
  					 {
  						printf("No memory available.\n");
  						destruction(b,numOfTypes,types);
//  						destroyBattleByCategory(b);
//  						deleteTypes(types,numOfTypes);
  						return 0;
  					 }
  					 strcpy(name,buffer);
    				 printf("Please enter Pokemon species:\n");
    			  	 scanf("%s", buffer);
  			  	     species=malloc((strlen(buffer)+1)*sizeof(char));
  					 if (!species)
  					 {
  						free(name);
  						printf("No memory available.\n");
  						destruction(b,numOfTypes,types);
//  						destroyBattleByCategory(b);
//  						deleteTypes(types,numOfTypes);
  						return 0;
  					 }
  					strcpy(species,buffer);
    			    printf("Please enter Pokemon height:\n");
    			    scanf("%f",&height);
    			    printf("Please enter Pokemon weight:\n");
    			    scanf("%f", &weight);
    			    printf("Please enter Pokemon attack:\n");
    			    scanf("%d", &attack);
    				pok=initPoke(name,species,type,height,weight,attack);
    				if(!pok)
    				{
    					printf("No memory available.\n");
    					free(name);
    					free(species);
    					destruction(b,numOfTypes,types);
//    					destroyBattleByCategory(b);
//    					deleteTypes(types,numOfTypes);
    					return 0;
    				}
    				if(insertObject(b,pok)==failure)
    				{
    					printf("No memory available.\n");
    					free(name);
    					free(species);
    					deletePoke(pok);
    					destruction(b,numOfTypes,types);
//    					destroyBattleByCategory(b);
//    					deleteTypes(types,numOfTypes);
    					return 0;
    				}
    				printf("The Pokemon was successfully added.\n");
					free(name);
					free(species);
    				printPokemon(pok);
    				deletePoke(pok);
    			  	 break;
    		  case '4':
    			    printf("Please enter type name:\n");
    			    scanf("%s", buffer);
 			  	     save=malloc((strlen(buffer)+1)*sizeof(char));
 					 if (!save)
 					 {
 						printf("No memory available.\n");
 						destruction(b,numOfTypes,types);
// 						destroyBattleByCategory(b);
// 						deleteTypes(types,numOfTypes);
 						return 0;
 					 }
 					 strcpy(save,buffer);
 					 type=searchType(types,numOfTypes,save);
    			    if (!type)//type not found
    			    {
    			    	printf("Type name doesn't exist.\n");
    			    	free(save);
    			    	break;
    			    }
    			    if(getNumberOfObjectsInCategory(b,type->name)==0)
    			    {
    			    	printf("There is no Pokemon to remove.\n");
    			    	free(save);
    			    	break;
    			    }
    			    pok=removeMaxByCategory(b,save);
    			    printf("The strongest Pokemon was removed:\n");
    			    free(save);
    			    printPokemon(pok);
    			    deletePoke(pok);
    			    break;
    		  case '5':/*fight*/
    			  	  printf("Please enter Pokemon type name:\n");
    			  	  scanf("%s", buffer);
    			  	  save=malloc((strlen(buffer)+1)*sizeof(char));
    			  	  if (!save)
    			  	  {
    			  		  printf("No memory available.\n");
    			  		  destruction(b,numOfTypes,types);
//    			  		  destroyBattleByCategory(b);
//    			  		  deleteTypes(types,numOfTypes);
    			  		  return 0;
    			  	  }
    			  	  strcpy(save,buffer);
    			  	  type=searchType(types,numOfTypes,save);
    			  	  if (!type)//type not found
    			  	  {
    			  		  printf("Type name doesn't exist.\n");
    			  		  free(save);
    			  		  break;
    			  	  }
    			  	  free(save);
    			  	  printf("Please enter Pokemon name:\n");
    			  	  scanf("%s", buffer);
    			  	  name=malloc((strlen(buffer)+1)*sizeof(char));
    			  	  if (!name)
    			  	  {
    			  		  printf("No memory available.\n");
    			  		  destroyBattleByCategory(b);
    			  		  deleteTypes(types,numOfTypes);
    			  		  return 0;
    			  	  }
    			  	  strcpy(name,buffer);
    			  	  printf("Please enter Pokemon species:\n");
    			  	  scanf("%s", buffer);
    			  	  species=malloc((strlen(buffer)+1)*sizeof(char));
    			  	  if (!species)
    			  	  {
    			  		  free(name);
    			  		  printf("No memory available.\n");
    			  		  destruction(b,numOfTypes,types);
//    			  		  destroyBattleByCategory(b);
//    			  		  deleteTypes(types,numOfTypes);
    			  		  return 0;
    			  	  }
    			  	  strcpy(species,buffer);
    			  	  printf("Please enter Pokemon height:\n");
    			  	  scanf("%f",&height);
    			  	  printf("Please enter Pokemon weight:\n");
    			  	  scanf("%f", &weight);
    			  	  printf("Please enter Pokemon attack:\n");
    			  	  scanf("%d", &attack);
    			  	  pok=initPoke(name,species,type,height,weight,attack);
    			  	  printf("You choose to fight with:\n");
    			  	  printPokemon(pok);
    			  	  element p=fight(b,pok);
    			  	  if(!p)
    			  	  {
    			  		  printf("There are no Pokemons to fight against you.\n");
    			  	  }
    			  	  else if(pok!=p)
    			  		  deletePoke(p);
    			  	  free(name);
    			  	  free(species);
    			  	  deletePoke(pok);
    			  	  break;
 			  	  case '6' :/*exit*/
 			  		  	  destruction(b,numOfTypes,types);
// 				      	  destroyBattleByCategory(b);
// 				      	  deleteTypes(types,numOfTypes);
 				      	  printf("All the memory cleaned and the program is safely closed.\n");
 				      	  break;
 			  	  default: /*invalid num*/
	      		  	  	  printf("Please choose a valid number.\n");
    		  	  }
   	   }
   	   return 0;
	}
