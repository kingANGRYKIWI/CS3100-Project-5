//Logan current, project 5, this is the header file containing all the functions for the Node class and Trie class
#include <iostream>
#include <vector>
#include <array> 

#pragma once

using namespace std;

class Node
{
public:
    bool theEnd;
    Node *nodeArray[26];

    Node();
    ~Node();
};

class Trie
{
private:
    Node *root;
    int size;
    int countNum;
public:
    Trie();
    Trie(Trie *other);
    ~Trie();
    void clear(Node *node);
    void clear();
    bool insert(string str);
    int count();
    int getSize();
    bool find(string str);
    int completeCount(string str);
    vector<string> complete(string str);
    Trie &operator=(const Trie &other);
    void copyHelper(Node *otherNode, Node *thisNode);
    void copyHelper(Node *node);
    Node *findHelper(string str);
    void completeHelper(vector<string>& vec, string str, Node* node);
};
