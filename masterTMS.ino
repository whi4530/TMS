/*
    Traffic Management System
    Master Program
    Joshua Shields, Levi Whited, Roberto Roux
    v 0.0.1 
    
    15 February 2016:::::Created repository and started basic code setup for the program.
*/

/* 
    int timer()
        Precondition: N/A. 
        Postcondition: t is incremented and returned. Can be called to simply increment the time or grab the current time
        
    void receive()
        Precondition: Strain Gauges hooked up and working correctly.
        Postcondition: Any entity is detected by the Strain Gauges and their weight is tested. They are either put into the
                        Vehicle[] queue or thrown out (by way of error signalling)
                        
    void process()
        Precondition: receive() has detected at least a single Vehicle and placed it in the Vehicle[] queue
        Postcondition: Vehicle[] queue is processed, resulting in either an empty queue or one less element in the array.
        
    void error_signal()
        Precondition: An error is detected somewhere specific in the program
        Postcondition: LED is blinked rapidly to signify an error (or RED if more LEDs are purchased)
        
    void go_signal()
        Precondition: Vehicle has been taken from the queue and given the go ahead
        Postcondition: LED is shone without blinking to signify (or GREEN if more LEDs are purchased)
        
    void setup()
        Precondition: N/A. Runs once at start of program
        Postcondition: Corresponding pins are now set for their specific duties, Serial is ready to be used.
        
    void loop()
        Precondition: N/A. Runs continously throughout duration of the program.
        Postcondition: Program is running
*/

#include <stdio.h>
#include <thread.h>     // using threads

#include "HZ711.h"      // libraries for amplifier chip

#define D1 11
#define C1 12
#define D2 13
#define C2 14
#define D3 15
#define C3 16

#define QUEUESIZE 5
#define VALDELAY 3000   // delay in ms. Will cause the process complete signal to run for # of ms given (default 3000)
#define ERRDELAY 30     // must be VALDELAY / 100 for consistency reasons.

HX711 fsensors[4];  // array for sensors closest to stop sign
HX711 bsensors[4];  // array for sensors farther back

using namespace std;

class Entity
{
    float wt;
    int tm;
  // class for anything detected by sensor  
};

class Vehicle :: Entity
{
    // class for only Vehicles that have been verified. Inherits Entity
    // may not be needed actually
    int prec;   // optional precedence variable
};

int t = 0;  // global variable to be used as time.
float c_factor = -7050.0;   // used Calibration test to determine this.

Vehicle queue[QUEUESIZE] = {0};


void setup()  // setup() runs once at the start
{
    pinMode(D1, INPUT);
    pinMode(C1, INPUT);
    pinMode(D2, INPUT);
    pinMode(C2, INPUT);
    
    pinMode(13, OUTPUT);
    
    Serial.begin(9600); // Serial is used to output results to the Serial Monitor
}

void error_signal()
{
    // blinks LED rapidly for 3 seconds if an error has occured.
    int i;
    
    for(i = 0; i <= 30; i++)    // each loop delays for a total of 100ms (1/10s). 100ms * 30 loops = 3000ms = 3s.
    {
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        delay(50);
    }
}

void go_signal()
{
    // shines LED with no blinking for 3 seconds if process has completed.
    digitalWrite(13, HIGH);
    delay(SIGDELAY);
}

bool check_queue(Vehicle[] *q)
{
    // simple function to go through the Vehicle queue and see if it is empty or not
    bool empty = false;
    
    for(int i = 0; i <= QSIZE; i++)
    {
        if(q[i] == 0)   // look into better way to write this, like without a for loop. For now this is fine.
            empty = true;
        else
            empty = false;
    }
    
    return empty;   
}

void receive()
{
    // receive Entities, check weight, determine Vehicles, add to queue.
}

void process()
{
    // process queue by time of arrival, with error checks in place
    int time_since_last = 0;
    if(time_since_last > 120 && queue = 0)  // 120s since last process and no vehicles in queue, then reset t to 0 to avoid 
            timer(true);                    //possible overflow
        
}

int timer(bool reset)
{
    // funtion that keeps track of time from the beginning of the run. Resets after 120 seconds of no activity and an empty
    // queue.
    
    Serial.println("Time is: ");
    Serial.print(t);
    
    bool r = reset;
    
    if(reset)
        t = 0;
        
    delay(1000);    // increment timer every second. OPEN TO CHANGE AFTER TESTING
    t++;
    
    return t;
}

void loop()   // will loop for the remainder of the program's runtime
{
    thread rcv receive();   
    thread prc process();
    thread tmr timer();
    // Concurrently receives new Vehicles into the queue while the queue is processed, and increments the timer
}
