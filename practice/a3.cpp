// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Enoch Yan>
// St.# : <301461267>
// Email: <eya29@sfu.ca>
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

        //Constructor, just setting values to nullptr and 0
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

        //Modification of lecture code
        void enqueue(const T &item) override {
            Node *newNode = new Node{item, nullptr, nullptr};
            if(is_empty()){
                start = newNode;
                back = newNode;
            }
            else{
                back->next = newNode;
                newNode->prev = back;
                back = newNode;
            }
            count++;
        }

        //Modification of lecture code that includes a check for empty queue
        const T &front() const override {
            if(is_empty()){
                throw std::runtime_error("front: Queue is empty");
            }
            return start->data;
        }

        //Modification of lecture code that includes a check for empty queue
        void dequeue() override {
            if(is_empty()){
                throw std::runtime_error("dequeue: Queue is empty");
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

        //Helper that sets a given queue with items of the same sender name
        void get_all_of_user(const string inp_username, Queue<T> &temp){ 
            Node *walk = start; 
            if(!is_empty()){
                while (walk != nullptr) {
                    if (walk->data.get_sender_name().compare(inp_username) == 0) {
                        temp.enqueue(walk->data);
                    }
                    walk = walk->next;
                } 
            }
        }

        //Helper that removes all items of a given sender name
        void remove_user(const string inp_username){
            Node *current = start;
            if(!is_empty()){
                while (current != nullptr) {
                    //Logic if username is found will set current to next node
                    if(current->data.get_sender_name().compare(inp_username) == 0){
                        if (current == start) {//Uses dequeue if node is the first node
                            dequeue();
                            current = start;
                        } else if (current == back) {// If node is the last node
                            back = current->prev;
                            back->next = nullptr;

                            delete current;

                            current = nullptr;
                        } else {// If node is in the middle
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
                        //Loop continues if username is not found
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
    //Declare queues for each rank
    Queue<Announcement> santa;
    Queue<Announcement> reindeer;
    Queue<Announcement> elf2;
    Queue<Announcement> elf1;
    Queue<Announcement> snowman;


    public:
    
    //Announce function that uses global jnet variable
    void jingle_announce(int n)
        {
            int numOfAnnounced = 0;

            //Loops until n announcements have been made or all queues are empty
            //Loops in priority order
            while (!santa.is_empty() && numOfAnnounced < n)
            {
                Announcement current = santa.front();
                jnet.announce(current);
                santa.dequeue();

                numOfAnnounced++;
            }

            while (!reindeer.is_empty() && numOfAnnounced < n)
            {
                Announcement current = reindeer.front();
                jnet.announce(current);
                reindeer.dequeue();

                numOfAnnounced++;
            }

            while (!elf2.is_empty() && numOfAnnounced < n)
            {
                Announcement current = elf2.front();
                jnet.announce(current);
                elf2.dequeue();

                numOfAnnounced++;
            }

            while (!elf1.is_empty() && numOfAnnounced < n)
            {
                Announcement current = elf1.front();
                jnet.announce(current);
                elf1.dequeue();

                numOfAnnounced++;
            }

            while (!snowman.is_empty() && numOfAnnounced < n)
            {
                Announcement current = snowman.front();
                jnet.announce(current);
                snowman.dequeue();

                numOfAnnounced++;
            }
        }


        //Send function, calls enqueue on the correct queue
        void send(const Announcement &m){
            switch(m.get_rank()){
                case Rank::SANTA:
                    santa.enqueue(m);
                    break;
                case Rank::REINDEER:
                    reindeer.enqueue(m);
                    break;
                case Rank::ELF2:
                    elf2.enqueue(m);
                    break;
                case Rank::ELF1:
                    elf1.enqueue(m);
                    break;
                case Rank::SNOWMAN:
                    snowman.enqueue(m);
                    break;
                default:
                    throw std::runtime_error("Rank not part of lists");
                    break;
            }
        }

        //Remove all function that removes all announcements of a given sender name
        void remove_all(string username){
            if(!santa.is_empty()){
                santa.remove_user(username);
            }
            if(!reindeer.is_empty()){
                reindeer.remove_user(username);
            }
            if(!elf2.is_empty()){
                elf2.remove_user(username);
            }
            if(!elf1.is_empty()){
                elf1.remove_user(username);
            }
            if(!snowman.is_empty()){
                snowman.remove_user(username);
            }
        }

        //Promote function that promotes all announcements of a given sender name
        void promote(string username){
            //Goes through each queue and promotes announcements of given sender name
            Queue<Announcement> temp_queue; 
            
            if(!reindeer.is_empty()){
                reindeer.get_all_of_user(username, temp_queue); 

                while(!temp_queue.is_empty()){ 
                    //Create new announcement with new rank
                    Announcement temp_announcement(temp_queue.front().get_sender_name(), Rank::SANTA, temp_queue.front().get_text());
                    //Add to santa queue
                    santa.enqueue(temp_announcement);
                    //Remove from reindeer queue
                    temp_queue.dequeue();

                }
                //Remove all announcements of given sender name from reindeer queue
                reindeer.remove_user(username);
            }
            
            //Repeat for elf2
            if(!elf2.is_empty()){
                elf2.get_all_of_user(username,temp_queue);

                while(!temp_queue.is_empty()){
                    Announcement temp_announcement(temp_queue.front().get_sender_name(), Rank::REINDEER, temp_queue.front().get_text());
                    reindeer.enqueue(temp_announcement);
                    temp_queue.dequeue();
                }
                elf2.remove_user(username);
            }

            //Repeat for elf1
            if(!elf1.is_empty()){
                elf1.get_all_of_user(username, temp_queue);

                while(!temp_queue.is_empty()){
                    Announcement temp_announcement(temp_queue.front().get_sender_name(), Rank::ELF2, temp_queue.front().get_text());
                    elf2.enqueue(temp_announcement);
                    temp_queue.dequeue();

                }
                
                elf1.remove_user(username);
            }

            //Repeat for snowman
            if(!snowman.is_empty()){
                snowman.get_all_of_user(username, temp_queue);

                while(!temp_queue.is_empty() ){
                    Announcement temp_announcement(temp_queue.front().get_sender_name(), Rank::ELF1, temp_queue.front().get_text());
                    elf1.enqueue(temp_announcement);
                    temp_queue.dequeue();
                }

                snowman.remove_user(username);
            }            

        }
};


int main(int argc, char *argv[])
{
    //Most of this code is from the getline_demo.cpp file from the lab


    // Check that the user provided a filename.
    
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        //
        // Returning a non-zero value from main indicates the program ended
        // abnormally. We don't care about main return values, but in some cases
        // they are useful. If this program was used as part of a shell script,
        // then the script might check this return value in an if-statement.
        //
        return 1; 
    }


    JingleNet lst;
    //
    // Read the contents of the file named by argv[1], and print each line.
    //
    string filename = argv[1];
    //cout << "Printing " << filename << " ..." << endl;
    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {
        
        size_t pos = line.find(' ');
        string command = line.substr(0, pos);
        line = line.substr(pos + 1);
        
        //cout << command << endl;        //Testing to see if command is correct
        
        
        //Checks which command is called
        if (command == "SEND") {
            Announcement input(line);
            lst.send(input);
        }
        else if (command == "ANNOUNCE") {
            int numOfAnnouce = stoi(line);
            lst.jingle_announce(numOfAnnouce);
        }
        else if (command == "REMOVE_ALL") {
            lst.remove_all(line);
        }
        else if (command == "PROMOTE_ANNOUNCEMENTS") {
            lst.promote(line);
        }
        else {
            throw std::runtime_error("main: Invalid command");
            return 1;
        }
    }
    return 0;
}
