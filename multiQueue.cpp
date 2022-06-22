/* more efficient multi line queue
Multi-line queue simulation
Structure:
arrays with queue ADT as elements 

2 arrays - one for POS // one for QUEUEs
actual simulation with queue ADT as elements 
customer finds shortest queue 
*/
#include <iostream>
#include "./queue.hpp"

#include <fstream> // for making csv file 
#include <chrono> // for timer
#include <ctime> // srand(time())

using namespace std;

// defining POS class
struct POS{
    bool active;
    int timeAt; // time customer spends at pos 

};

// function to identify shortest line 
// parameter (all three queues)
int shortestQueue(dsa::Queue queues[]){
    int shortest = 0; // shortest - stores index of the shortest queue
    // traversing each queue 
    for(int i = 0; i<3; i++){
        if(queues[i].getSize() < queues[shortest].getSize()){
            shortest = i;
        }
    }
    return shortest;
}

int main(){ 

    // declaring variables 
    const int NUM_POS = 3; // the number of POS
    int customerServed = 0; // number of customer served 
    int range, startTime, simulationTime, arrivalTime;
    int cTime = 0 ;// customer time 
    // range of service time (range) - range of time needed to process a new cust
    // start of service time - start time of processing each new customer 
    //                       - probability that a customer arrives in one tick (%):
    // simulation time = how long the simulation takes place 
    // arrivaltime = interval between one customer to another 


    // declaring array with queue adt as elements 
    dsa::Queue qArr[NUM_POS];


    srand(time(0)) ;// to randomize rand() output  // time(0) -> random number seed ->initialize a pseudorandom number generator.
    // time() returns current calendar time as object of type time_t
    

    // getting user inputs 
    cout << "Start of service time: (eg.50) "; 
    cin>> startTime;

    cout<< "Range of service time: (eg.30) ";
    cin>> range;

    cout<< "Arrival time: ";
    cin>> arrivalTime;

    cout<< "Simulation time/secs: ";
    cin>> simulationTime;


    // creating and opening csv file 
    ofstream myFile;
    myFile.open("multiLineQueue.csv");

    myFile << "Service Time, Number of customers served\n";
    
    // POS SETUP
    // allocating array for POS structure
    POS* POSArray = new POS[NUM_POS];
    // initializing POS values
    for(int i = 0; i < NUM_POS; i++){
        POSArray[i].active = false;
        POSArray[i].timeAt = 0;

    }

    // inserting 8 customers into each queue 
    for (int custIndex = 0 ; custIndex < 8; custIndex++){
        for (int qIndex = 0; qIndex < 3; qIndex++){
            qArr[qIndex].enqueue(rand() % range + startTime); // random amount of time the customer needs to be served 
        }
         
    }

    // START OF SIMULATION 
    // declaring variables for timer 
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    int elapsedTime = int (chrono::duration_cast<chrono::seconds> (end-start).count());

    // main loop 
    while(elapsedTime < simulationTime){
        // checks if interval between each customer is reached
        if(cTime % arrivalTime == 0 ){
           
            // add a customer the shortest of the queues
            int shortestQIndex = shortestQueue(qArr);
            qArr[shortestQIndex].enqueue(rand() % range + startTime);
            
        }

        // SERVING CUSTOMERS
        // 1. getting a customer to the cashier in each line 
        for(int i = 0; i< NUM_POS; i++){
            if(POSArray[i].active == false && qArr[i].getSize() != 0){
                POSArray[i].active = true; // serving customers
                POSArray[i].timeAt = qArr[i].peek();

                qArr[i].dequeue();

            }
        }

        // 2. customer spending time at POS
        for(int i = 0; i< NUM_POS; i++){
            if(POSArray[i].active == true){
                POSArray[i].timeAt --; // decrement time spent at POS
            }

            
            // 3. free up POS after customer is served
            // cheking if customer is done 
            if(POSArray[i].active == true && POSArray[i].timeAt == 0){
                POSArray[i].active = false; // open POS to new customer 

                customerServed++; // incrementing number of customer served 
            }


        }

        // just a temp variable for comparison :D
        int prevTime = elapsedTime;

        // calculating the time elapsed 
        end = chrono::steady_clock::now();
        elapsedTime = int(chrono::duration_cast<chrono::seconds> (end-start).count());//typecasting 

        if (elapsedTime != prevTime){
            myFile << elapsedTime<<","<<customerServed<<"\n";
            cout<<elapsedTime<<" ";
        }    

        cTime++;
    }

    myFile.flush();
    myFile.close();
    cout<<"\nTotal number of customers served: "<< customerServed;

    // prevent memory leaks 
    delete POSArray;
    POSArray = NULL;
    for (int i = 0 ; i < NUM_POS; i++){
        qArr[i].free();
    }
    delete qArr;
   


}