/*
Multi-line queue simulation
Structure:
arrays with queue ADT as elements 
*/

#include <iostream>
#include "./queue.hpp"

#include <fstream> // for making csv file 
#include <chrono> // for timer


using namespace std;

// defining POS class
struct POS{
    bool active;
    int timeAt; // time spent at pos 

};


int main(){
    // instantiating 3 queues 
    dsa::Queue<int> Queue1;
    dsa::Queue<int> Queue2;
    dsa::Queue<int> Queue3;

    // declaring variables 
    const int NUM_POS = 3;
    int customerServed = 0; 
    int range, startTime, simulationTime, arrivalTime;
    int cTime = 0 ;// customer time 

    // getting user inputs 
    cout << "Start of service time: ";
    cin>> startTime;

    cout<< "Range of service time: ";
    cin>> range;

    cout<< "Simulation time(seconds): ";
    cin>> simulationTime;

    cout<< "Arrival time: ";
    cin>> arrivalTime;

    // creating and opening csv file 
    ofstream myFile;
    myFile.open("multiLineQueue.csv");

    myFile << "Service Time; Number of customers served"<<endl;
    
    // POS SETUP
    // allocating array for each line 
    POS* POSArray = new POS[NUM_POS];
    // initializing POS values
    for(int i = 0; i < NUM_POS; i++){
        POSArray[i].active = false;
        POSArray[i].timeAt = 0;

    }

    // inserting 8 customers into each queue 
    for (int i = 0 ; i < 8; i++){
        Queue1.enqueue(rand() % range + startTime);// rand() -> generates random numbers in range [0, RAND_MAX ~ 32767] 
        Queue2.enqueue(rand() % range + startTime); // random amount of time the customer needs to be served 
        Queue3.enqueue(rand() % range + startTime);
    }

    // START OF SIMULATION 
    // declaring variables for timer 
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    int elapsedTime = int (chrono::duration_cast<chrono::seconds> (end-start).count());

    // main loop 
    while(elapsedTime < simulationTime){
        if(cTime % arrivalTime == 0 ){
            // keep adding customers to queue 
            Queue1.enqueue(rand()%range + startTime);
            Queue2.enqueue(rand()%range + startTime);
            Queue3.enqueue(rand()%range + startTime);

        }

        // SERVING CUSTOMERS
        // 1. getting a customer to the cashier in each line 
        // queue 1 
        if(POSArray[0].active == false && Queue1.getSize() != 0 ){
            POSArray[0].active = true; // occupied and serving customers 
            POSArray[0].timeAt = Queue1.peek();

            Queue1.dequeue();
        }
        // queue 2
        if(POSArray[1].active == false && Queue2.getSize() != 0 ){
            POSArray[1].active = true; // occupied and serving customers 
            POSArray[1].timeAt = Queue2.peek();

            Queue2.dequeue();
        }
        // queue 3
        if(POSArray[2].active == false && Queue3.getSize() != 0 ){
            POSArray[2].active = true; // occupied and serving customers 
            POSArray[2].timeAt = Queue3.peek();

            Queue3.dequeue();
        }

        // 2. customer spending time at POS
        for(int i = 0; i< NUM_POS; i++){
            if(POSArray[i].active == true){
                POSArray[i].timeAt --; // decrement time spent at POS
            }

            
            // 3. free up POS after customer is done 
            // cheking if customer is done 
            if(POSArray[i].active == true && POSArray[i].timeAt == 0){
                POSArray[i].active = false; // reset POS 

                customerServed++; // incrementing number of customer served 
            }


        }

        // just a temp variable for comparison :D
        int prevTime = elapsedTime;

        // calculating the time elapsed 
        end = chrono::steady_clock::now();
        elapsedTime = int(chrono::duration_cast<chrono::seconds> (end-start).count());//typecasting 

        if (elapsedTime != prevTime){
            myFile<<elapsedTime<<";"<<customerServed<<"\n";
            cout<<elapsedTime<<" ";
        }    

        cTime++;
    }

    myFile.close();
    cout<<"Total number of customers served: "<< customerServed;



    


}