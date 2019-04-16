#include <iostream>
#include "trie_single.h"

int main(int argc, char** argv) {

        trie_single* ctrie_single = new trie_single;

        ctrie_single->insert("this");
        ctrie_single->insert("is");
        ctrie_single->insert("test");
        ctrie_single->insert("strings");

        ctrie_single->display();

        delete ctrie_single;
	return 0;
}



