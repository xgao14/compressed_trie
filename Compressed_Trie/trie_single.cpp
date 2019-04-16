#include "trie_single.h"
#include <iostream>

trie_single::trie_single()
{
    T_root = new trie_node; //root doesn't store key
    T_root->key = "*"; //use * represents the root key
    for(int i=0; i<Max; i++)
    {
        T_root->child[i] = NULL;
    }
    T_root->freq = 0;
}

/*
 * delete trie node
 */
void trie_single::delNode(trie_node* node)
{
    for(int i=0; i<Max; i++)
    {
        if(node->child[i] != NULL)
        {
            delNode(node->child[i]);
        }
    }
    delete node;
}

trie_single::~trie_single()
{
    delNode(T_root);
}

/*
 * create a new node
 */
trie_node* trie_single::createNode(std::string key)
{
    trie_node* newNode = new trie_node;
    newNode->key = key;

    for(int i=0; i<Max; i++)
    {
        newNode->child[i] = NULL;
    }
    newNode->freq = 0;

    return newNode;
}

/*
 * calculate the index of the letter
 */
int trie_single::calIndex(char letter)
{
    char a = 'a';
    char A = 'A';
    int index = -1;
    if(letter >= 'a' && letter <= 'z')
    {
        index = (int)letter%(int)a;
    }
    else if(letter >= 'A' && letter <= 'Z')
    {
        index = (int)letter%(int)A;
    }
    return index;
}

/*
 *insert a key word
 *1. word exists: word count(the "freq" field of the leaf node) plus 1 
 *2. word prefix exists: insert the remain letters of the word in the child node of the prefix node
 *3. word dosen't exist(all the letters not exist): insert the word in the child node of the root node
 */
void trie_single::insert(std::string key)
{
    trie_node* p = T_root;
    int index = -1;
    while(key.length())
    {
        index = calIndex(key[0]);
        if(index == -1) //invalid index
        {
            return;
        }
        if(p->child[index] == NULL) //no this node, add it
        {
            trie_node* newNode = createNode(key);
            if(key.length() == 1) //single character
            {
                newNode->feature = false;
            }
            else //multi character
            {
                newNode->feature = true;
            }
            newNode->freq++;
            p->child[index] = newNode;
            words_num++;
            return;
        }
        else if(p->child[index]->feature == false) 
        {
            p = p->child[index];
            key = key.substr(1, key.length()-1);
        }
        else if(p->child[index]->feature == true)
        {
            int i = 0;
            while(i<key.length() && i<p->child[index]->key.length())
            {
                if(key[i] != p->child[index]->key[i])
                {
                    break;
                }
                i++;
            }
            if(i == key.length() && i == p->child[index]->key.length())
            {
                p->child[index]->freq++;
                return;
            }
            if(i == key.length() && i < p->child[index]->key.length()) //split p->child[index]->key
            {
                std::string temp_str = p->child[index]->key.substr(i, p->child[index]->key.length()-1); //the remanent of p->child[index]->key after removes key
                trie_node* newNode = createNode(temp_str);
                if(temp_str.length() == 1) //single character
                {
                    newNode->feature = false;
                }
                else //multi character
                {
                    newNode->feature = true;
                }
                newNode->freq = p->child[index]->freq;
                for(int k=0; k<Max; k++) //move down the children
                {
                    if(p->child[index]->child[k])
                    {
                        newNode->child[k] = p->child[index]->child[k];
                        p->child[index]->child[k] = NULL;
                    }
                }
                int in = calIndex(temp_str[0]);
                p->child[index]->child[in] = newNode;
                p->child[index]->key = key;
                words_num++;
                if(p->child[index]->key.length() == 1) //single character
                {
                    p->child[index]->feature = false;
                }
                else //multi character
                {
                    p->child[index]->feature = true;
                }
                p->child[index]->freq = 1;
                return;
            }
            if(i < key.length() && i == p->child[index]->key.length())
            {
                int in = calIndex(key[i]);
                key = key.substr(i, key.length()-1);
                p = p->child[index];
                continue;
            }
            if(i < key.length() && i < p->child[index]->key.length())
            {
                std::string temp_str = p->child[index]->key.substr(i, p->child[index]->key.length()-1); //the remanent of p->child[index]->key after removes the same characters
                trie_node* newNode = createNode(temp_str);
                if(temp_str.length() == 1) //single character
                {
                    newNode->feature = false;
                }
                else //multi character
                {
                    newNode->feature = true;
                }
                newNode->freq = p->child[index]->freq;
                for(int k=0; k<Max; k++) //move down the children
                {
                    if(p->child[index]->child[k])
                    {
                        newNode->child[k] = p->child[index]->child[k];
                        p->child[index]->child[k] = NULL;
                    }
                }
                int in = calIndex(temp_str[0]);
                p->child[index]->child[in] = newNode;
                p->child[index]->key = p->child[index]->key.substr(0, i);
                if(p->child[index]->key.length() == 1) //single character
                {
                    p->child[index]->feature = false;
                }
                else //multi character
                {
                    p->child[index]->feature = true;
                }
                p->child[index]->freq = 0;

                //insert the remanent key
                key = key.substr(i, key.length()-1);
                newNode = createNode(key);
                if(key.length() == 1) //single character
                {
                    newNode->feature = false;
                }
                else //multi character
                {
                    newNode->feature = true;
                }
                newNode->freq++;
                in = calIndex(key[0]);
                p->child[index]->child[in] = newNode;
                words_num++;
                return;
            }
        }
    }
    if(p != T_root) 
    {
        if(p->freq == 0)
        {
            words_num++;
        }
        p->freq++;
    }
}

/*
 *search the word and return the frequence of the word
 */
unsigned int trie_single::search(std::string key)
{
    int index = -1;
    trie_node* p = T_root;
    while(key.length())
    {
        index = calIndex(key[0]);
        if(index == -1)//invalid letter
        {
            return 0;
        }
        if(p->child[index] != NULL)
        {
            if(p->child[index]->key == key)
            {
                return p->child[index]->freq;
            }
            else
            {
                p = p->child[index];
                key = key.substr(1, key.length()-1);
            }
        }
        else 
        {
        	return 0;
		}
    }

    return 0;
}


void trie_single::output_d(trie_node* node, std::string output_word)
{
    output_word = output_word + node->key;
    for(int i=0; i<Max; i++)
    {
        if(node->child[i] != NULL)
        {
            output_d(node->child[i], output_word);
        }
    }

    if(node->freq > 0) {
        std::cout << "word: " << output_word << "  frequence: " << node->freq << std::endl;
    }
}
/*
 *print out the words information in the trie
 */
void trie_single::display()
{
    std::string output_word = "";
    output_d(T_root, output_word);
}


