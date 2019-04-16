/*
 * Single words trie
 * This is a compressed trie structure
 */

#ifndef __TRIE_SINGLE__
#define __TRIE_SINGLE__

#define Max 26

#include <string>


struct trie_node
{
    std::string   key;
    trie_node*  child[Max];   //link list of children
    unsigned int freq;        //word count/frequence
    bool feature;             //true: multi-character; false: single-character
};

class trie_single
{
    private:
      trie_node*  T_root;
      int words_num;
      void delNode(trie_node* node);
      trie_node* createNode(std::string key);
      int calIndex(char letter);
      void output_d(trie_node* node, std::string output_word);
    public:
      trie_single();
      ~trie_single();
    public:
      void insert(std::string key);
      unsigned int search(std::string key);  //return frequence of word
      void display();
      int get_words_num()
      {
          return words_num;
      }
};


#endif


