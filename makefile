PokemonsBattles:MainSecond.o Pokemon.o MaxHeap.o LinkedList.o BattleByCategory.o
		gcc MainSecond.o Pokemon.c MaxHeap.c LinkedList.c BattleByCategory.c -o PokemonsBattles
MainSecond.o:MainSecond.c Pokemon.h BattleByCategory.h Defs.h
		gcc -c MainSecond.c
Pokemon.o:Pokemon.c Pokemon.h Defs.h
		gcc -c Pokemon.c
MaxHeap.o:MaxHeap.c MaxHeap.h Defs.h
		gcc -c MaxHeap.c
LinkedList.o:LinkedList.c LinkedList.h Defs.h
		gcc -c LinkedList.c
BattleByCategory.o:BattleByCategory.c BattleByCategory.h MaxHeap.h LinkedList.h Defs.h
		gcc -c BattleByCategory.c
clean:
		rm -f *.o
