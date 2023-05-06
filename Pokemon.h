#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

/* init the structs of the program */

typedef struct Pokemon_Type
{
	char *name;
	int howMany;
	struct Pokemon_Type **effective_against_me;
	int sizeAgainstMe;
	struct Pokemon_Type **effective_against_others;
	int sizeAgainstOthers;
}Type;

typedef struct Bio_Info
{
	float height;
	float weight;
	int attack;
}Info;

typedef struct Pokemon
{
	char *name;
	char *species;
	Type *nameT;
	Info *infoB;
}Poke;

/*functions*/
Info* initBio( float , float , int );//gets bio info and returns a pointer to Info.
Poke* initPoke( char *, char *, Type *, float , float , int );//gets name,species,ptr to Type,height,weight,attack, returns a ptr to Poke.
Type* initType( char *);//gets a name of Type, and returns a ptr to Type.
//all status funcs return a status which indicates whether the func successfully done or not.
status addAgainstMe( Type *, Type *);//gets 2 ptrs to Types, and adds the right one to the list of effective_against_me of the left one
status addAgainstOthers( Type *, Type *);//gets 2 ptrs to Types, and adds the right one to the list of effective_against_others
                                         //of the left one
//status deleteAgainstMe( Type *, char *); //gets a ptr to Type and name, and deletes the right one from the list of effective_against_me
//                                         //of the left one
//status deleteAgainstOthers( Type *, char *);//gets a ptr to Type and name, and deletes the right one from the list of
//                                           //effective_against_others of the left one
status printPokemon( Poke* );//gets a ptr to Poke, and prints all the details about it.
status printType( Type *);//gets a ptr to Type, and prints all the details about it.
void deleteBio( Info *);//gets a ptr to Info, and frees it.
void deletePoke( Poke *);//gets a ptr to Poke, and frees all the allocated memory pointed by (except type), then frees the ptr given.
void deleteType( Type *);//gets a ptr to Type, and frees all the allocated memory pointed by, then frees the ptr given.
