/* 
SINGLE QUEUE SIMULATION 
overall structure:
POS are arrays 
the single line queue implements queue ADT
*/
#include <iostream>
#include "./queue.hpp"

#include <fstream> //remove error from making csv file idk how  
#include <chrono> // deals with date and time(precision timers)-> for steady clock 

using namespace std;
// defining POS/cashier class 
// define custom variable named POS with 'struct', with active and timeAt members
struct POS{
    bool active; // can melayani or not? true -> is serving ; false -> is no longer serving and ready to serve 
    int timeAt; // time spent at POS 
};

int main(){
    // instantiating Queue ADT
    dsa::Queue<int> myQueue;

    // declaring variables 
    const int NUM_POS = 3; // number of cashiers
    int customerServed = 0; // number of customers served
    int range, startTime, simulationTime, arrivalTime;
    /*range = how much time each customer need to be served 
    start time = ?
    simulationTime = how long the simulation will run (seconds)
    arrivalTime = how much time needed for each cutomer to get to the pos
    more arrival time => not alot of ppl waiting in queue*/
    int cTime = 0;//what is c time ? -> customer time?
    
    // test 
    range = 20;
    startTime = 50;
    simulationTime = 10;
    arrivalTime = 5;


    // std::ofstream - outfput file stream - part of iostream library - data type representing output file, create, write to files 
    ofstream myFile;
    myFile.open("singleQueue.csv");

    myFile << "Service Time; Number of customers served\n";
    
    // POS SETUP
    // dynamically allocate an array for the cashier strutcure
    POS* POSArray = new POS[NUM_POS];
    // set all cashiers to empty / initializing values 
    for(int i = 0; i< NUM_POS;i++){
        POSArray[i].active =  false;
        POSArray[i].timeAt = 0;
    }

    // inserting 8 customers in the queue as a start
    for(int i = 0; i < 8; i++){
        myQueue.enqueue(i);//what is the value supposed to be ?

    }

    // START OF SIMULATION 
    // declaring variables for the timer 
    auto start = chrono::steady_clock::now(); // auto to declare variable with complicated data type. 
    auto end = chrono::steady_clock::now(); // std::chrono
    int elapsedTime= int(std::chrono::duration_cast<chrono::seconds> (end-start).count());

    // main loop to keep simulation running 
    while(elapsedTime < simulationTime){
        if(cTime % arrivalTime==0){
            // add customer to queue
            myQueue.enqueue(3);// what is it supposed to enqueue?
        }

        // SERVING CUSTOMERS  
        for(int i =  0; i< NUM_POS; i++){
            // =>if POS is not serving anyone atm, and queue is populated 
            if(POSArray[i].active == false && myQueue.getSize() != 0){
                

                POSArray[i].active = true; // occupied and serving cust 
                POSArray[i].timeAt = myQueue.peek(); // returns the random value of customer

                // dequeue
                myQueue.dequeue();

            }
        }


        for(int i = 0; i <NUM_POS; i++){
            // =>timer for if POS is serving cust atm 
            // make sure not too long 
            if(POSArray[i].active == true){
                // decrement time spent at cashier 
                POSArray[i].timeAt--;
            }

            // cashier is done serving -> timeTaken = 0
            if(POSArray[i].active == true && POSArray[i].timeAt ==0){
                // set cashier to open if the time limit is reached, increment number of customer served
                POSArray[i].active = false; 
                customerServed++;
            }

        }

        // initializing another variable -> what for?
        int prevTime = elapsedTime;

        // recording the end time of processsing?? -> calculating elapsed time 
        end = chrono::steady_clock::now();
        elapsedTime = int(chrono::duration_cast<chrono::seconds> (end-start).count());

        if(elapsedTime != prevTime){
            myFile<<elapsedTime<<";"<<customerServed<<"\n";
            cout<<elapsedTime<<" ";
        }

        cTime++;
    }

    myFile.close();
    cout<<"Total number of customers served: "<< customerServed;

}