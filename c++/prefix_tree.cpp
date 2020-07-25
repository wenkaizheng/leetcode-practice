#include "prefix_tree.hpp"
#include <iostream>
#include <cassert>
using namespace std;
// we offer '/'
#define INDEX(c) ((int)c - (int)'a')
namespace tree
{
    
        tree::prefix_tree::prefix_tree(vector<string> strs) : arr(strs), isLeaf(false)
        {
            unsigned int i;
            for (i = 0; i < SIZE; i++)
                children[i] = NULL;
            isLeaf = false;
        }
        tree::prefix_tree::~prefix_tree() 
        { 
            for (int i = 0; i < SIZE; i++){
               if(this->children[i]){
                   delete (this->children[i]);
               }
           }
          
        } 
        // If not present, inserts the key into the trie
        // If the key is a prefix of trie node, just marks leaf node
        void tree::prefix_tree::insert(string key)
        {
            unsigned int length = key.length();
            unsigned int index;
            prefix_tree *pCrawl = this;
            unsigned int level ;
            for (level = 0; level < length; level++)
            {
                key[level]!='/'?index = INDEX(key[level]):index=26;
               // cout<<"-------------\n";
                if (!pCrawl->children[index])
                    pCrawl->children[index] = new prefix_tree(arr);

                pCrawl = pCrawl->children[index];
            }
            //cout<<"32th\n";
             // mark last node as leaf
             pCrawl->isLeaf = true;
        }
        // check if there is any substring content key world
        // return true if exis otherwise return false
        bool tree::prefix_tree::search(string key){
             unsigned int length = key.length();
             unsigned int index;
             unsigned int count = 0;
             prefix_tree *pCrawl = this;
             unsigned int level ;
             for (level = 0; level < length; level++)
             {
                key[level]!='/'?index = INDEX(key[level]):index=26;
               // cout<<"-------------\n";
                if (!pCrawl->children[index])
                    return false;
                else{
                    count ++;
                    if(count ==length){
                        return true;
                    }
                }

                pCrawl = pCrawl->children[index];
             }
             // should not be here
             return false;

        }
        // Counts and returns the number of children of the
        // current node
        int tree::prefix_tree::countChildren( prefix_tree *node,int &index)
        {
            int count = 0;
            unsigned int i;
            for (i = 0; i < SIZE; i++)
            {
                if (node->children[i] != NULL)
                {
                    count++;
                    index = i;
                }
            }
            return count;
        }
        // Perform a walk on the trie and return the
        // longest common prefix string
        string tree::prefix_tree::walkTrie()
        {

            prefix_tree *pCrawl = this;
            int index = -1;
            string prefix;
            while (countChildren(pCrawl,index) == 1 &&
               pCrawl->isLeaf == false)
            {   
                assert(index != -1);
                pCrawl = pCrawl->children[index];
                index !=26?prefix.push_back('a' + index):prefix.push_back('/');
               // cout<<"67th\n";
            }
            //cout<<"69th\n";
            return (prefix);
        }   
        // A Function to construct trie
        void tree::prefix_tree::constructTrie()
        {
            unsigned int i;
            for (i = 0; i < arr.size(); i++)
                insert(arr[i]);
       
        }
    }
