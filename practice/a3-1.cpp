// a3.cpp

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
// Do not #include any other files!
//
#include "Announcement.h"
#include "JingleNet_announcer.h"
#include "Queue_base.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
template <typename T>
class Queue: public Queue_base<T> {
    struct Node{
        T data;
        Node* prev;
        Node* next;
    };

    Node *start;
    Node *back;
    int count;

    public:
        Queue(){
            start = nullptr;
            back = nullptr;
            count = 0;
        }
        
        ~Queue(){
            clear();
        }

        int size() const override {
            return count;
        }

        void enqueue(const T &item) override {
            Node *newNode = new Node{item, nullptr, nullptr};
            if(is_empty()){
                start = newNode;
                back = newNode;
            } else {
                back->next = newNode;
                newNode->prev = back;
                back = newNode;
            }
            count++;
        }

        const T &front() const override {
            if(is_empty()){
                throw std::runtime_error("Queue is empty");
            }
            return start->data;
        }

        void dequeue() override {
            if(is_empty()){
                throw std::runtime_error("Queue is empty");
            }

            Node* temp = start;
            start = start->next;

            if (start != nullptr) {
                start->prev = nullptr;
            } else {
                back = nullptr;
            }

            delete temp;
            count--;
        }
        
        //helper function used to find and delete the pointer associated with the name
        void remove(const string name){
            Node *current = start;
            if(!is_empty()){
                while (current != nullptr) {
                    if(current->data.get_sender_name().compare(name) == 0){
                        if (current == start) {
                            dequeue();
                            current = start;
                        } else if (current == back) {
                            back = current->prev;
                            back->next = nullptr;

                            delete current;
                            current = nullptr;
                        } else {
                            Node* prevNode = current->prev;
                            Node* nextNode = current->next;

                            prevNode->next = nextNode;
                            nextNode->prev = prevNode;
                            
                            delete current;
                            current = nextNode;
                        }
                        count--;
                    }
                    else {
                        current = current->next;
                    }
                }
            }
        }

        //Checks if queue is empty
        bool is_empty() const {
            return (start == nullptr);
        }

        //Clears the queue
        void clear() {
            while(!is_empty()){
                dequeue();
            }
        }
};

//JingleNet class
class JingleNet{
    Queue<Announcement> santa;
    Queue<Announcement> reindeer;
    Queue<Announcement> elf2;
    Queue<Announcement> elf1;
    Queue<Announcement> snowman;

    public:
    void send(const Announcement &s) {
        if (s.get_rank() == Rank::SANTA) {
            santa.enqueue(s);
        } else if (s.get_rank() == Rank::REINDEER) {
            reindeer.enqueue(s);
        } else if (s.get_rank() == Rank::ELF2) {
            elf2.enqueue(s);
        } else if (s.get_rank() == Rank::ELF1) {
            elf1.enqueue(s);
        } else if (s.get_rank() == Rank::SNOWMAN) {
            snowman.enqueue(s);
        } else {
            throw std::runtime_error("Rank not in lists");
        }
    }
    
    void announce(int n) {
        int count = 0;
        while (!santa.is_empty() && count < n)
        {
            Announcement current = santa.front();
            jnet.announce(current);
            santa.dequeue();
            count++;
        }

        while (!reindeer.is_empty() && count < n)
        {
            Announcement current = reindeer.front();
            jnet.announce(current);
            reindeer.dequeue();
            count++;
        }

        while (!elf2.is_empty() && count < n)
        {
            Announcement current = elf2.front();
            jnet.announce(current);
            elf2.dequeue();
            count++;
        }

        while (!elf1.is_empty() && count < n)
        {
            Announcement current = elf1.front();
            jnet.announce(current);
            elf1.dequeue();
            count++;
        }

        while (!snowman.is_empty() && count < n)
        {
            Announcement current = snowman.front();
            jnet.announce(current);
            snowman.dequeue();
            count++;
        }
    }
    
    void remove_all(string name){
        if(!santa.is_empty()){
            santa.remove(name);
        }
        if(!reindeer.is_empty()){
            reindeer.remove(name);
        }
        if(!elf2.is_empty()){
            elf2.remove(name);
        }
        if(!elf1.is_empty()){
            elf1.remove(name);
        }
        if(!snowman.is_empty()){
            snowman.remove(name);
        }
    }
    void promote(const string& name) {
        int counter = reindeer.size();
        while (counter > 0) {
            if (reindeer.front().get_sender_name() == name) {
                string temp_name = reindeer.front().get_sender_name();
                string temp_message = reindeer.front().get_text();
                reindeer.dequeue();
                Announcement temp(temp_name, Rank::SANTA, temp_message);
                santa.enqueue(temp);
            } else {
                string temp_name = reindeer.front().get_sender_name();
                string temp_message = reindeer.front().get_text();
                reindeer.dequeue();
                Announcement temp(temp_name, Rank::REINDEER, temp_message);
                reindeer.enqueue(temp);            
            }
            counter--;
        }

        counter = elf2.size();
        while (counter > 0) {
            if (elf2.front().get_sender_name() == name) {
                string temp_name = elf2.front().get_sender_name();
                string temp_message = elf2.front().get_text();
                elf2.dequeue();
                Announcement temp(temp_name, Rank::REINDEER, temp_message);
                reindeer.enqueue(temp);
            } else {
                string temp_name = elf2.front().get_sender_name();
                string temp_message = elf2.front().get_text();
                elf2.dequeue();
                Announcement temp(temp_name, Rank::ELF2, temp_message);
                elf2.enqueue(temp);
            }
            counter--;
        }

        counter = elf1.size();
        while (counter > 0) {
            if (elf1.front().get_sender_name() == name) {
                string temp_name = elf1.front().get_sender_name();
                string temp_message = elf1.front().get_text();
                elf1.dequeue();
                Announcement temp(temp_name, Rank::ELF2, temp_message);
                elf2.enqueue(temp);
            } else {
                string temp_name = elf1.front().get_sender_name();
                string temp_message = elf1.front().get_text();
                elf1.dequeue();
                Announcement temp(temp_name, Rank::ELF1, temp_message);
                elf1.enqueue(temp);
            }
            counter--;
        }

        counter = snowman.size();
        while (counter > 0) {
            if (snowman.front().get_sender_name() == name) {
                string temp_name = snowman.front().get_sender_name();
                string temp_message = snowman.front().get_text();
                snowman.dequeue();
                Announcement temp(temp_name, Rank::ELF1, temp_message);
                elf1.enqueue(temp);
            } else {
                string temp_name = snowman.front().get_sender_name();
                string temp_message = snowman.front().get_text();
                snowman.dequeue();
                Announcement temp(temp_name, Rank::SNOWMAN, temp_message);
                snowman.enqueue(temp);
            }
            counter--;
        }

    }

};
    

int main(int argc, char *argv[])
{
    JingleNet lst;
    string filename = argv[1];
    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {   
        if (argc != 2)
        {
            cout << "Usage: " << argv[0] << " <filename>" << endl;
            return 1; 
        }
        size_t pos = line.find(' ');
        string command = line.substr(0, pos);
        line = line.substr(pos + 1);

        if (command == "SEND") {
            Announcement input(line);
            lst.send(input);
        } else if (command == "ANNOUNCE") {
            int numAnn= stoi(line);
            lst.announce(numAnn);
        } else if (command == "REMOVE_ALL") {
            lst.remove_all(line);
        } else if (command == "PROMOTE_ANNOUNCEMENTS") {
            lst.promote(line);
        } else {
            throw std::runtime_error("main: Invalid command");
            return 1;
        }
    }
    return 0;
}
