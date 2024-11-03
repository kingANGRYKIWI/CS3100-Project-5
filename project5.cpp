//Logan current, project 5, this file is the autocomplete program and will go thru the dictionary and add it all to a trie then prompt the user for a prefix and find all the words that begin with that.

#include "Trie.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    //I copied the code from the OneNote to open the wordlist.txt and put it in a vector
    ifstream fileIn("wordlist.txt");
    vector<string> wordlist;
    if (fileIn.good()) // make sure we opened the file properly

    {
        string word;
        while (!fileIn.eof())
        {
            fileIn >> word;           // use >> just like with cin
            wordlist.push_back(word); // or insert into trie
        }
    }
    else
    {
        cerr << "Couldn't open file!" << endl; // cerr goes to the error output which is usually just stdout
    }
    Trie trieTree;
    for (int i = 0; i < wordlist.size(); i++)
    {
        trieTree.insert(wordlist[i]);
    }

    // this starts the program now that everything is set up
    bool running = true;
    while (running)
    {
        //prompts user for a prefix
        string choice = "";
        cout << "Please enter a word prefix (or press 1 to exit):";
        cin >> choice;

        //checks if the user wants to continue
        if (choice == "1")
        {
            running = false;
        }
        else
        {
            //if they want to print all the words with the prefix
            string decision = "";
            cout << "There are " << trieTree.completeCount(choice) << " completions for the prefix '" << choice << "'."
                 << " Show completions? ";
            cin >> decision;
            //prints it all if yes
            if (decision == "yes")
            {
                vector<string> theVec = trieTree.complete(choice);
                cout << "Completions" << endl;
                cout << "-----------" << endl;
                for (string str : theVec)
                {
                    cout << str << endl;
                }
            }
        }
    }
    //deletes the trie
    trieTree.~Trie();
    return 0;
}