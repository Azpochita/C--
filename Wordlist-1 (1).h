// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Aaron Zhou>
// St.# : <301458837>
// Email: <ayz3@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement the doubly-linked list for the word list.
    // Don't change it any way!
    //
    struct Node
    {
        string word;
        Node *prev;
        Node *next;
    };

        Node *head = nullptr; //Creates the head initial pointer
        Node *tail = nullptr; //Creates the tail initial pointer
        bool frozen = false; 

        void pop_front()
        {
            assert(!empty()); // causes a crash if !empty() is false
            Node *p = head;
            head = head->next;
            delete p;
        }

        //Check is list is empty
        bool empty() const
        {
            return head == nullptr;
        }
        
        //Deletes full list
        void clear()
        {
            while (!empty())
            {
                pop_front();
            }
        }

    public:

        //Default Constructor
        Wordlist() : head(nullptr), tail(nullptr), frozen(false) {}
        //copy constructor
        Wordlist(const Wordlist& other) : head(nullptr), tail(nullptr), frozen(false) {
            Node* otherNode = other.head;
            while (otherNode != nullptr) {
                add_word(otherNode->word);
                otherNode = otherNode->next;
            }
        }
        
        Wordlist(const string& filename) : head(nullptr), tail(nullptr), frozen(false) {
            ifstream file(filename);
            if (file.is_open()) {
                string word;
                while (file >> word) {
                    add_word(word);
                }
                file.close();
            } else {
                cerr << "Error: Unable to open file " << filename << endl;
            }
        }

        //Destructor
        ~Wordlist()
        {
            clear();
        }
        
        //freeze list if callen upon
        void freeze()
        {
            frozen = true;
        }

        //Returns true if w is in the word list, false otherwise
        virtual bool contains(const string &w) const
        {
            Node* current = head;
            while (current) {
                if (current->word == w) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
        
        //Returns the total number of nodes in the list.
        virtual int length() const 
        {
            int count = 0;
            Node* current = head;
            while (current != nullptr) {
                current = current->next;
                count++;
            }
            return count;
        }

        //checks if list is frozen
        virtual bool is_frozen() const 
        {
            return frozen;
        }

        //Returns a copy of the word at the given index.
        virtual string get_word(int index) const
        {
            if (index < 0 || index >= length())
            {
                throw out_of_range("Index out of range");
            }
            Node *current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            return current->word;
        }

        // Add a word to the list
        virtual void add_word(const string& w) 
        {
            if (frozen == true) {
                throw runtime_error("Cannot add word to a frozen Wordlist.");
            }

            if (contains(w))
            {
                return;
            }

            Node* newNode = new Node;
            newNode->word = w;
            newNode->next = nullptr;
            newNode->prev = nullptr;

            //Checks for empty lists
            if (head == nullptr)
            {
                head = tail = newNode;
                return;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        //remove word from list
        virtual void remove_word(const string& w) {
            if (frozen) {
                throw runtime_error("Cannot remove a word from a frozen Wordlist.");
            }

            Node* current = head;
            while (current != nullptr) {
                if (current->word == w) {
                    if (current == head) {
                        head = current->next;
                    } else {
                        current->prev->next = current->next;
                    }
                    if (current == tail) {
                        tail = current->prev;
                    } else {
                        current->next->prev = current->prev;
                    }

                    Node* temp = current;
                    current = current->next;
                    delete temp;
                } else {
                    current = current->next;
                }
            }
        }

        //vector of pointers
        virtual vector<string*> get_sorted_index()
        {
            freeze();
            vector<string*> index;
            Node* current = head;
            while (current != nullptr) {
                index.push_back(&(current->word));
                current = current->next;
            }
            return index;
        }
};
    //
    // ... you can write helper methods if you need them ...
    // // class Wordlist

//
// ... you can write helper functions here (or before Wordlist) if you need them
// ...
//
