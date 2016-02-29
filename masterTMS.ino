/*
    Traffic Management System
    Master Program
    Joshua Shields, Levi Whited, Roberto Roux
    v 0.0.1 
    
    15 February 2016:::::Created repository and started basic code setup for the program.
    
    25 Feb 2016:::::Added con and decon for Entity, will add Vehicle's soon. Started real work on receive() to detect any weight at
                    all, next is to validate them and turn them into Vehicles.
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
#define D4 17
#define C4 18

#define D5 19
#define C5 20
#define D6 21
#define C6 22

#define D7 23
#define C7 24
#define D8 25
#define C8 26

#define QUEUESIZE 5
#define VALDELAY 3000   // delay in ms. Will cause the process complete signal to run for # of ms given (default 3000)
#define ERRDELAY 30     // must be VALDELAY / 100 for consistency reasons.
#define VALIDWT 100     // 100 is placeholder until we weigh the RC cars we will use. This is in lbs.

HX711 fsensors[4] = {(D1, C1), (D3, C3), (D5, C5), (D7, C7)};  // array for sensors closest to stop sign
HX711 bsensors[4] = {(D2, C2), (D4, C4), (D6, C6), (D8, C8)};  // array for sensors farther back

using namespace std;

class Entity
{
    public:
        float wt;
        int tm;
        
    private:
        Entity();       // constructor and deconstructor for nicer code
        ~Entity();
  // class for anything detected by sensor  
};

class Vehicle :: Entity
{
    // class for only Vehicles that have been verified. Inherits Entity
    // may not be needed actually
    int prec;   // optional precedence variable
};

unsigned long t = 0;  // global variable to be used as time.
float c_factor = -7050.0;   // used Calibration test to determine this.

Entity ents[10] = {0};  // probably needs to be dynamically allocated.
Vehicle queue[QUEUESIZE] = {0};


void setup()  // setup() runs once at the start
{
    pinMode(D1, INPUT);
    pinMode(C1, INPUT);
    pinMode(D2, INPUT);
    pinMode(C2, INPUT);
    
    pinMode(13, OUTPUT);
    
    Serial.begin(9600); // Serial is used to output results to the Serial Monitor
    
    fsensors.set_scale(c_factor);
    bsensors.set_scale(c_factor);   // set scales' calibration factors to use the data it gives us
    
    fsensors.tare();
    bsensors.tare();    // set scales to 0
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

void receive()
{
    // receive Entities, check weight, determine Vehicles, add to queue.
    int ctr = 0, detwt[4] = {0};
    
    if(detwt[0] = (fsensors[0].get_units) > TOOLIGHT)
    {
        ents[ctr] = new Entity(detwt[0], timer());
        ctr++;
    }
    if(detwt[1] = (fsensors[1].get_units) > TOOLIGHT)
    {
        ents[ctr] = new Entity(detwt[1], timer());
        ctr++;
    }
    if(detwt[2] = (fsensors[2].get_units) > TOOLIGHT)
    {
        ents[ctr] = new Entity(detwt[2], timer());
        ctr++;
    }
    if(detwt[3] = (fsensors[3].get_units) > TOOLIGHT)
    {
        ents[ctr] = new Entity(detwt[3], timer());
        ctr++;
    }
}

void process()
{
    // process queue by time of arrival, with error checks in place
    int time_since_last = 0;
    if(time_since_last > 120 && queue = 0)  // 120s since last process and no vehicles in queue, then reset t to 0 to avoid 
            timer(true);                    //possible overflow
        
}

unsigned long timer(bool reset)
{
    // funtion that keeps track of time from the beginning of the run. Resets after 120 seconds of no activity and an empty
    // queue.
    
    //Serial.println("Time is: ");
    //Serial.print(t);
    
    bool r = reset;
    
    if(reset)
        t = 0;
        
    delay(1000);    // increment timer every second. OPEN TO CHANGE AFTER TESTING
    t++;
    
    return t;
}

Entity::Entity(float f, unsigned long l)
{
    wt = f;
    tm = l;
}

Entity::~Entity()
{
    delete[] wt;
    delete[] tm;
}

void loop()   // will loop for the remainder of the program's runtime
{
    thread rcv receive();   
    thread prc process();
    thread tmr timer();
    // Concurrently receives new Vehicles into the queue while the queue is processed, and increments the timer
}

//so it goes from entity -> confirmed vehicles -> into the queue, then if the queue is > 0, process it, and because it will be threaded
//even though the queue is being processed, entities are still being verified and added to the queue. So vehicles entering the queue
//should be given a number (or time) that keeps the order.  Only to be trumped by precedence/long line at one of the four stop signs
// (tripped by constant pressure on second further back sensor).  So if the queue keeps the order, we'll have to be able to make
//manipulations to it to change the order.

//set up different variables (or just conditions to existing stop sign variables) to allow for atleast one priority stop sign that
//will account for the bulk of the traffic. For instance, the intersection in cal by Campy's coming from the light, the stop sign
//closest to DollarGeneral and the ATM would want to be our priority stop sign, because most of the traffic is coming from the 
//stop light. Once we have a "priority" stop sign, we could set it up so it just always HOPS up one spot in the queue. So that way
//if the intersection is full, the priority sign will get 2/5 instead of 1/4.  

//implement a way to save data for study collection

//once a car's pressure leaves the sensor, how long are we going to assume it takes to clear the intersection? waiting for testing?

//should we think to test/look at what it would weigh if a semi=truck or other such type vehicle was on the sensor? That way we can 
//plan accordingly with how long to wait before other cars can proceed

//once we start testing, we should test against how long stop sign intersections usually take without our TMS, (because people can
//see when others are taking left turns, so they can too.  Or someone is taking a right so you can go straight with no worry)
//that way if the timing is pretty inconsequential, we can say that with barely any addition in time the intersection is much safer
//etc, etc. And if it takes a decent amount of time longer, we just wont mention it, safety is the number once concern after all! 
