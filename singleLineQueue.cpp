/* 
SINGLE QUEUE SIMULATION 
overall structure:
POSs are represented by arrays
the single line queue implements queue ADT
*/
#include <iostream>
#include "./queue.hpp"

#include <fstream> //remove error from making csv file idk how  
#include <chrono> // deals with date and time(precision timers)-> for steady clock 
#include <ctime> // c data structure which contains time(0) // not to be confused with CTime variable


using namespace std;
// defining POS/cashier class 
// define custom variable named POS with 'struct', with active and timeAt members

struct POS{
    bool active; // true -> POS is serving ; false -> is no longer serving and ready to serve 
    int timeAt; // time spent at POS 
};

int main(){
    // instantiating Queue ADT
    dsa::Queue myQueue;
    srand(time(0)); // randomize rand() output 

    // declaring variables 
    const int NUM_POS = 3; // number of cashiers
    int customerServed = 0; // number of customers served
    int range, startTime, simulationTime, arrivalTime;
    int cTime = 0; // counter

    /*range = how much time each customer need to be served 
    start time = ?
    simulationTime = how long the simulation will run (seconds)
    arrivalTime = how much time needed for each cutomer to get to the pos
    more arrival time => not alot of ppl waiting in queue*/

    // getting user inputs 
    cout << "Start of service time: (eg.50) ";
    cin>> startTime;

    cout<< "Range of service time: (eg.30) ";
    cin>> range;

    cout<< "Arrival time: ";
    cin>> arrivalTime;
    
    cout<< "Simulation time/secs: ";
    cin>> simulationTime;

    // std::ofstream - outfput file stream - part of iostream library - data type representing output file, create, write to files 
    // creating and opening new csv file to write 
    ofstream myFile;
    myFile.open("singleLineQueue.csv");

    myFile << "Service Time, Number of customers served\n";
    
    // POS SETUP
    // dynamically allocate an array for the POS structure
    POS* POSArray = new POS[NUM_POS];
    // set all POS to empty / initializing values 
    for(int i = 0; i< NUM_POS;i++){
        POSArray[i].active = false;
        POSArray[i].timeAt = 0;
    }

    // inserting 8 customers in the queue 
    for(int i = 0; i < 8; i++){
        myQueue.enqueue(rand() %range + startTime); // rand() %range + startTime -> random amount of time a customer needs to be served 

    }

    // START OF SIMULATION 
    // declaring variables for the timer 
    auto start = chrono::steady_clock::now(); // auto-> declares variable with complicated data type. 
    auto end = chrono::steady_clock::now(); // std::chrono
    int elapsedTime= int(std::chrono::duration_cast<chrono::seconds> (end-start).count());

    // main loop to keep simulation running 
    while(elapsedTime < simulationTime){
        if(cTime % arrivalTime == 0){
            // adding customer to queue
            myQueue.enqueue(rand()%range + startTime);
        }

        // SERVING CUSTOMERS  
        // 1. get customer to cashier 
        for(int i =  0; i< NUM_POS; i++){
            // check if POS is not serving anyone atm, and if queue is populated 
            if(POSArray[i].active == false && myQueue.getSize() != 0){
                
                POSArray[i].active = true; // occupied and serving cust 
                POSArray[i].timeAt = myQueue.peek(); // returns the random value of customer

                // dequeue
                myQueue.dequeue();

            }
        }

        // 2. customer being served 
        for(int i = 0; i <NUM_POS; i++){
            if(POSArray[i].active == true){
                // decrement time spent at POS 
                POSArray[i].timeAt--;
            }

            // 3. free up POS after customer has been served 
            // check if POS is done serving 
            if(POSArray[i].active == true && POSArray[i].timeAt ==0){
                // set cashier to open if the time limit is reached, increment number of customer served
                POSArray[i].active = false; 
                customerServed++; 
            }

        }

        
        int prevTime = elapsedTime;

        // calculating elapsed time  -> end-start 
        end = chrono::steady_clock::now();
        elapsedTime = int(chrono::duration_cast<chrono::seconds> (end-start).count());

        if(elapsedTime != prevTime){
            myFile<<elapsedTime<<","<<customerServed<<"\n";
            cout<<elapsedTime<<" ";
        }

        cTime++;
    }

    myFile.flush(); // to remove an error 
    myFile.close();
    cout<<"\nTotal number of customers served: "<< customerServed;

    // prevent memory leaks 
    delete POSArray;
    POSArray = NULL;

    myQueue.free();
}