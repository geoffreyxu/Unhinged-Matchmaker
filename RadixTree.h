//
//  RadixTree.h
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <stdio.h>
#include <map>
#include <vector>
#include "provided.h"
using namespace std;

template<typename ValueType>
class RadixTree
{
public:
    RadixTree();
    ~RadixTree();
    void insert(string key, const ValueType& value);
    ValueType* search(string key) const;
private:
    struct RadixNode {
        bool leaf;
        RadixNode* child[128];
        string child_s[128];
        ValueType* val;
        RadixNode() {
            for (int i = 0; i < 128; i++)
                child[i] = nullptr;
        }
        ~RadixNode() {
            for (int i = 0; i < 128; i++)
                delete child[i];
        }
    };
    void insertHelper(RadixNode* root, string key, ValueType value)
    {
        if (key.empty())
        {
            root->leaf = true;
            root->val = &value;
            return;
        }
        int cur_char = key[0];
        if (root->child[cur_char] == nullptr)
        {
            root->child[cur_char] = new RadixNode;
            root->child_s[cur_char] = key;
            insertHelper(root->child[cur_char], "", value);
            return;
        }
        string transition = root->child_s[cur_char];
        int match_len = 0;
        while (match_len < min(transition.length(), key.length()) && transition[match_len] == key[match_len])
            match_len++;
        if (match_len == transition.length()) // case if part of the key perfectly matches the transition
        {
            insertHelper(root->child[cur_char], key.substr(match_len), value);
        }
        else if (match_len == key.length()) // case if entire inserted string is a substring of a preexisting word
        {
            RadixNode* newNode = new RadixNode;
            newNode->child[transition[match_len]] = root->child[cur_char];
            newNode->child_s[transition[match_len]] = transition.substr(match_len);
            root->child[cur_char] = newNode;
            root->child_s[cur_char] = key;
            insertHelper(root->child[cur_char], "", value);
        }
        else // case if part of s matches part of the transition string
        {
            RadixNode* newNode = new RadixNode;
            newNode->child[transition[match_len]] = root->child[cur_char];
            newNode->child_s[transition[match_len]] = transition.substr(match_len);
            root->child[cur_char] = newNode;
            root->child_s[cur_char] = key.substr(0, match_len);
            insertHelper(root->child[cur_char], key.substr(match_len), value);
        }
        
    }
    RadixNode* searchHelper(RadixNode* root, string key) const
    {
        if (key.empty())
            return (root->leaf) ? root : nullptr;
        int cur_char = key[0];
        if (root->child[cur_char] == nullptr) // return nullptr if first char of key is not in tree
            return nullptr;
        string transition = root->child_s[cur_char];
        int len = min(transition.length(), key.length());
        if (transition.substr(0, len) != key.substr(0, len))
            return nullptr;
        if (transition.length() == len)
            return searchHelper(root->child[cur_char], key.substr(transition.length()));
        else
            return nullptr;
    }
    vector<string> keys;
    RadixNode* root2 = new RadixNode;
    //map<string, ValueType*>* m_map;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree() : m_map(new map<string, ValueType*>)
{}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
    /*for (auto it = m_map->begin(); it != m_map->end(); it++)
        delete it->second;
    m_map->clear();*/
    for (int i = 0; i < keys.size(); i++)
    {
        ValueType* dead = search(keys[i]);
        delete dead;
    }
}

template <typename ValueType>
void RadixTree<ValueType>::insert(string key, const ValueType& value)
{
    //(*m_map)[key] = new ValueType(value);
    keys.push_back(key);
    insertHelper(root2, key, value);
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(string key) const
{
     /*if (m_map->find(key) == m_map->end())
        return nullptr;
    else
        return (m_map->find(key)->second);*/
    if (searchHelper(root2, key) == nullptr)
        return nullptr;
    return searchHelper(root2, key)->val;*/
}


#endif /* RadixTree_h */
