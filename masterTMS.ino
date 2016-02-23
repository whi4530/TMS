/*
    Traffic Management System
    Master Program
    v 0.0.1 
    
    15 February 2016:::::Created repository and started basic code setup for the program.
*/

#include <stdio.h>
#include <thread.h>     // using threads
#define DOUT 11
#define CLK 12

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
};

void receive()
{
    // receive Entities, check weight, determine Vehicles, add to queue.
}

void process()
{
    // process queue by time of arrival, with error checks in place
}



float c_factor = -7050.0;   // used Calibration test to determine this.

void setup()  // setup() runs once at the start
{
    pinMode(DOUT, INPUT);
    pinMode(CLK, INPUT);
    pinMode(13, OUTPUT);
}

void loop()   // will loop for the remainder of the program's runtime
{
    thread
}
