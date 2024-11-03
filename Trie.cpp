//Logan current, project 5, this file has all the logic and functions for the trie tree
#include "Trie.h"
#include <iostream>
#include <array>

using namespace std;

Node::Node()
{
    //initializes the node and makes the array all null
    theEnd = false;
    for (int i = 0; i < 26; i++)
    {
        nodeArray[i] = nullptr;
    }
}

Node::~Node()
{
}

Trie::Trie()
{
    //initializes the trie tree
    countNum = 0;
    size = 1;
    root = new Node();
}

Trie::Trie(Trie *other)
{
    //makes a shallow copy
    size = other->size;
    countNum = other->countNum;
    root = other->root;
    copyHelper(other->root, root);
}

Trie &Trie::operator=(const Trie &other)
{
    //makes a deep copy
    clear(root);
    root = new Node();
    size = other.size;
    countNum = other.countNum;
    root = other.root;
    copyHelper(other.root, root);
}

void Trie::copyHelper(Node *otherNode, Node *thisNode)
{
    //helps copy the other trie to the current trie recursively 
    if (otherNode->theEnd == true)
    {
        thisNode->theEnd = true;
    }
    for (int i = 0; i < 26; i++)
    {
        if (otherNode->nodeArray[i] != nullptr)
        {
            //if there's a node, copy it then go to the other nodes in the array and copy then keep going.
            thisNode->nodeArray[i] = otherNode->nodeArray[i];
            copyHelper(otherNode->nodeArray[i], thisNode->nodeArray[i]);
        }
    }
    return;
}

Trie::~Trie()
{
    //deletes the trie
    clear(root);
    root = new Node();
    size = 0;
    countNum = 0;
}

void Trie::clear(Node *node)
{
    //recursively deletes all the nodes and the nodes in the array
    for (int i = 0; i < 26; i++)
    {
        if (node->nodeArray[i] != nullptr)
        {
            clear(node->nodeArray[i]);
        }
    }
    delete node;
    return;
}

bool Trie::insert(string str)
{
    //if the word exists already then return false
    if (find(str))
    {
        return false;
    }
    else
    {
        //add the node
        Node *current = root;
        //goes through the string
        for (int i = 0; i < str.length(); i++)
        {
            //which letter we are adding
            char theLetter = str[i];
            //find the num equivalent so we can add the node into the correct spot int the array
            int theNode = theLetter - 'a';
            //if that spot is null go in
            if (current->nodeArray[theNode] == nullptr)
            {
                //make a new node there
                current->nodeArray[theNode] = new Node();
                //increase size
                size++;
            }
            //go to that node we made or already existed and add the next letter
            current = current->nodeArray[theNode];
        }
        //when done we want the last node to be the end 
        current->theEnd = true;
        //increase word count
        countNum++;
        return true;
    }
}

int Trie::count()
{
    //returns word count
    return countNum;
}

int Trie::getSize()
{
    //returns the amount of nodes
    return size;
}

bool Trie::find(string str)
{
    //very identical to the insert function except we never add a new node
    Node *current = root;
    //goes through the string 
    for (int i = 0; i < str.length(); i++)
    {
        //find the letter
        char theLetter = str[i];
        //position in the array
        int theChar = theLetter - 'a';
        //if that position doesn't exist then it's a new word and isn't in the trie
        if (current->nodeArray[theChar] == nullptr)
        {
            return false;
        }
        //go to the next letter
        current = current->nodeArray[theChar];
    }
    //returns true if the word is done
    if (current->theEnd == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Trie::completeCount(string str)
{
    //returns the size of the vector
    return complete(str).size();
}

vector<string> Trie::complete(string str)
{
    vector<string> vec;
    Node *iterator = findHelper(str);
    completeHelper(vec, str, iterator);
    return vec;
}

Node *Trie::findHelper(string str)
{
    Node *current = root;
    //iterates through the string
    for (int i = 0; i < str.length(); i++)
    {
        //get letter
        char theLetter = str[i];
        //get position
        int theChar = theLetter - 'a';
        //the node doesnt exist 
        if (current->nodeArray[theChar] == nullptr)
        {
            return nullptr;
        }
        //go to the next position
        current = current->nodeArray[theChar];
    }
    //returns the node that has the last character in the string word
    return current;
}

void Trie::completeHelper(vector<string> &vec, string str, Node *node)
{
    //found a full word!
    if (node->theEnd)
    {
        vec.push_back(str);
    }
    //iterate through the array
    for (int i = 0; i < 26; i++)
    {
        //if the node is there
        if (node->nodeArray[i] != nullptr)
        {
            //get the letter
            char letterToAdd = i + 'a';
            //add it to a new string
            string newString = str + letterToAdd;
            //call this function again but with the new string and at the node that was found
            completeHelper(vec, newString, node->nodeArray[i]);
        }
    }
}