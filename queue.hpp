/*Queue ADT file*/
// Queue implementation with linked lists -> REFERENCE TO: FabioSebs/DataStructureTA
#include <iostream>


// DECLARATION
namespace dsa{

    // defining node class of linked list
    template <typename T>
    class Node{
        // PROPERTIES
        T data;
        Node* next;
        // OPERATIONS n CONSTRUCTORS
        Node():data(),next(NULL){};
        Node(T element): data (element),next(NULL);

    };


    // defining queue class
    template <typename T>
    class Queue{
        private:
            int size;
        public:
            // PROPERTIES 
            Node<T> *head; // aka queuefront
            Node<T> * tail; // aka queuerear       

            // methods
            // constructor
            Queue(): head(NULL), tail(NULL), size(0){};
            
            // getter and setter function
            int getSize();
            void incrementSize();
            
            // queue operations
            void enqueue(T element);
            T dequeue();
            void display ();
            T peek(); // returns the first in queue

    };
}

// IMPLEMENTATION
template <typename T>
int dsa::Queue<T>::getSize(){
    return this->size;
}

template <typename T>
void dsa::Queue<T>::incrementSize(){
    this->size ++;
    return;

}

template <typename T>
void dsa::Queue<T>::enqueue(T element){
    // creating new node 
    dsa::Node *newNode = new dsa::Queue::Node(element);

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
}

template <typename T>
T dsa::Queue<T>::dequeue(){
    // temporary pointer points to head of list 
    dsa::Node* temp = this->head;

    // move head pointer to next element 
    this->head = this->head->next;

    // remove first element in the list
    return temp->data;


}

// template <typename T>
// void dsa::Queue<T>::display(){
//     dsa::queue
// }