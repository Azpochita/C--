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

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;
    };

    Node *root = nullptr;

    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //

    public:
        //Empty Constructor
        Wordlist() {}

         //Constructor that takes in a filename
        Wordlist(const std::string &filename) {
            ifstream file(filename);
            string word;
            while (file >> word) {
                add_word(word);
            }
        }
        
        //Destructor
        virtual ~Wordlist() {
            clear(root);
        }

        //delete_tree
        void clear(Node *root) {
            if (root == nullptr) {
                return;
            }
            //delete left and right subtrees
            clear(root->left);
            clear(root->right);
            delete root;
        }

        int height(Node *N)  
        {  
            if (N == NULL)  
                return 0;  
            return N->height;  
        }  

        //rotate_left, using reference
        Node *rightRotate(Node *y)  
        {  
            Node *x = y->left;  
            Node *T2 = x->right;  
        
            // Perform rotation  
            x->right = y;  
            y->left = T2;  
        
            // Update heights  
            y->height = max(height(y->left), height(y->right)) + 1;  
            x->height = max(height(x->left), height(x->right)) + 1;  
        
            // Return new root  
            return x;  
        }  

        //rotate_left, using reference
        Node *leftRotate(Node *x)  
        {  
            Node *y = x->right;  
            Node *T2 = y->left;  
        
            // Perform rotation  
            y->left = x;  
            x->right = T2;  
        
            // Update heights  
            x->height = max(height(x->left), height(x->right)) + 1;  
            y->height = max(height(y->left), height(y->right)) + 1;  
        
            // Return new root  
            return y;  
        }

        //insert, using reference
        Node* insert(Node* n, const string &w){
            if (n == nullptr) {
                return new Node{w, 1, nullptr, nullptr, 1};
            }
            int compare_result = w.compare(n->word);
            //if w is less than n->word, go left
            if (compare_result < 0) {
                n->left = insert(n->left, w);
            } else if (compare_result > 0) {
                //if w is greater than n->word, go right
                n->right = insert(n->right, w);
            } else {
                //if w is equal to n->word, increment count and return
                n->count++;
                return n;
            }
            
            //update height
            n->height = 1 + max(height(n->left), height(n->right));

            //find balance
            int balance = getBalance(n);
            
            //left left case
            if (balance > 1) {
                if(getBalance(n->left) > 0) {
                    return rightRotate(n);
                } else if(getBalance(n->left) < 0) {
                    //left right case
                    n->left = leftRotate(n->left);
                    return rightRotate(n);
                }
            }
            //right right case
            if (balance < -1) {
                if(getBalance(n->right) < 0) {
                    return leftRotate(n);
                } else if(getBalance(n->right) > 0) {
                    //right left case
                    n->right = rightRotate(n->right);
                    return leftRotate(n);
                }
            }
            return n;
        }  

        // Get Balance factor of node N  
        int getBalance(Node *N)  
        {  
            if (N == NULL)  
                return 0;  
            return height(N->left) - height(N->right);  
        }  

        //add_word
        void add_word(const string &w) {
            root = insert(root, w);
        }
        
        //is_sorted
        virtual bool is_sorted() const {
            return is_sorted_helper(root);
        }

        //is_sorted helper
        bool is_sorted_helper(Node *n) const {
            //base case
            if (n == nullptr) {
                return true;
            }
            if (n->left != nullptr && n->word.compare(n->left->word) < 0) {
                return false;
            }
            if (n->right != nullptr && n->word.compare(n->right->word) > 0) {
                return false;
            }
            return is_sorted_helper(n->left) && is_sorted_helper(n->right);
        }

        virtual int get_count(const string &w) const {
            Node *n = root;
            while (n != nullptr) {
                //compare w to n->word
                int compare_result = w.compare(n->word);

                //if w is less than n->word, go left
                if (compare_result < 0) {
                    n = n->left;
                } else if (compare_result > 0) {
                    //if w is greater than n->word, go right
                    n = n->right;
                } else {
                    //if w is equal to n->word, return count
                    return n->count;
                }
            }
            return 0;
        }

        //Returns the number of nodes in the word list
        virtual int num_different_words() const {
            return count_helper(root);
        }

        //num_different_words helper
        int count_helper(Node *n) const {
            if(n == nullptr){
                return 0;
            }
            //count left and right subtrees
            return 1 + count_helper(n->left) + count_helper(n->right);
        }

        //Returns the total number of words in the word list
        virtual int total_words() const {
            return count_words(root);
        }

        //total_words helper
        int count_words(Node *n) const {
            if(n == nullptr){
                return 0;
            }
            //count left and right subtrees nodes
            return(n->count + count_words(n->left) + count_words(n->right));
        }

        //Returns string of most frequent 
        virtual string most_frequent() const {
            Node* bigger = freq_helper(root);
            if(bigger == nullptr){
                return "";
            }
            string freqCount = to_string(bigger->count);
            string out = bigger->word + " " + freqCount;
            
            return out;
        }

        //most_frequent helper--Recursive bigger
        Node* freq_helper(Node *n) const{
            if (n == nullptr){
                return nullptr;
            }
            Node* rightBigger = freq_helper(n->right);

            //compare left and right bigger counts
            Node* bigger = n;
            if (rightBigger != nullptr && rightBigger->count > n->count){
                bigger = rightBigger;
            }
            
            //compare left and right bigger counts
            Node* leftBigger = freq_helper(n->left);
            if (leftBigger != nullptr && leftBigger->count > bigger->count){
                bigger = leftBigger;
            }

            return bigger;
        }

        //Find the number of singletons in the tree
        virtual int num_singletons() const {
            return single_helper(root);
        }
        
        //num_singletons helper--Recursive count
        int single_helper(Node *n) const {
            if(n == nullptr){
                return 0;
            }
            
            //return sum of left and right subtrees
            if (n->count == 1){
                return 1 + single_helper(n->left) + single_helper(n->right);
            } else {
                return single_helper(n->left) + single_helper(n->right);
            }
        }
        
        //print list of words
        void print_words() const{
            if(root != nullptr){
                print_inorder(root, 0);
            }
        }

        //Recursive print in order
        int print_inorder(Node* n, int order) const {
            if (n == nullptr){
                return order;
            }
            int count = print_inorder(n->left, order);
            
            //word and count
            count++;
            cout << count << ". {\"" << n->word << "\", " << n->count << "}" << endl;
            
            return print_inorder(n->right, count);
        }

    }; // class Wordlist

    //
    // Make sure to thoroughly test your code as you go!
    
    //Citation:
    //https://www.geeksforgeeks.org/insertion-in-an-avl-tree/ 
