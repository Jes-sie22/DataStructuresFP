/*Queue ADT file*/
// Queue implementation with linked lists -> REFERENCE TO: FabioSebs/DataStructureTA
#include <iostream>


// DECLARATION
namespace dsa{

    // defining node class of linked list
    class Node{
    public:
        // PROPERTIES
        int data;
        Node* next;
        // OPERATIONS n CONSTRUCTORS
        Node():data(),next(NULL){};
        Node(int element): data (element), next(NULL){};
    };


    // defining queue class
    class Queue{
        private:
            int size;
        public:
            // PROPERTIES 
            Node *head; // aka queuefront
            Node * tail; // aka queuerear       

            // methods
            // constructor
            Queue(): head(NULL), tail(NULL), size(0){};
            
            // getter and setter functions
            int getSize();
            void incrementSize();
            void decrementSize();
            
            // queue operations
            void enqueue(int element);
            int dequeue();
            void display (); // do we actually need this?
            int peek(); // returns the first in queue
            void free(); // deletes queue from memory 

    };
}

// IMPLEMENTATION
int dsa::Queue::getSize(){
    return this->size;
}

void dsa::Queue::incrementSize(){
    this->size ++;
    return;

}
void dsa::Queue::decrementSize(){
    this->size --;
    return;

}

void dsa::Queue::enqueue(int element){
    // creating new node 
    dsa::Node *newNode = new dsa::Node(element);

    // link to linked list 
    // checking if linked list is empty
    if(dsa::Queue::getSize() == 0){
        this->head = newNode;
        this->tail  = newNode;

        dsa::Queue::incrementSize();

        return;

    }
    // if not empty
    else{
        this->tail->next = newNode;
        this->tail = newNode;

        // setting new node pointer to NULL
        this->tail ->next = NULL;

        // increment size 
        dsa::Queue::incrementSize();

    }
};

int dsa::Queue::dequeue(){
    // temporary pointer points to head of list 
    dsa::Node* temp = this->head;

    // move head pointer to next element 
    this->head = this->head->next;

    // update queue size 
    dsa::Queue::decrementSize();

    // remove first element in the list
    return temp->data;


}

int dsa::Queue::peek(){
    // check if queue is empty
    if(dsa::Queue::getSize() == 0){
        std::cout<< "queue is empty" <<std::endl;
        return -1;
    }
    else{
        return this->head->data;
    }
}

void dsa::Queue::free(){
    delete this->head;
    head = NULL;
}
