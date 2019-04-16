trie: main.o trie_single.o

	g++ -Wall -std=c++11 main.o trie_single.o


main.o: main.cpp trie_single.h

	g++ -c -std=c++11 main.cpp


trie_single.o: trie_single.cpp trie_single.h

	g++ -c -std=c++11 trie_single.cpp


clean:
	rm *.o trie
