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
/* #include <thread.h>     // using threads */

#include "HX711.h"      /* libraries for amplifier chip */

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
#define ERRDELAY 30     // shoul be VALDELAY / 100 for consistency reasons.
#define VALIDWT 100     // 100 is placeholder until we weigh the RC cars we will use. This is in lbs.
#define TOOLGT 40.0     // 40 is placeholder until we establish a value that we deem "too light" to even be considered a Vehicle.
#define SIGDELAY 10     // 10 is placeholder until we establish the correct amount to wait
#define OFFSET 20

HX711 fsensor1(D1, C1);
HX711 fsensor2(D2, C2);

/* HX711 fsensors[4] = {(D1, C1), (D3, C3), (D5, C5), (D7, C7)};  // array for sensors closest to stop sign
HX711 bsensors[4] = {(D2, C2), (D4, C4), (D6, C6), (D8, C8)};  // array for sensors farther back */

float c_factor = -7050.0;   // used Calibration test to determine this.



/* NOTE for queue[QUEUESIZE]: Be VERY careful when working with this global array. It will need to be accessed by receive() and 
process(), so we need to make sure that we have safeguards in place to prevent any issues that could occur from both functions 
accessing the data at once. */

using namespace std;

class Entity
{
    public:
        unsigned long wt;
        int tm;
        Entity();
        ~Entity();
        Entity(float, unsigned long);       // constructor and deconstructor for nicer code
        
    private:
  // class for anything detected by sensor  
};

class Vehicle : Entity
{
    // class for only Vehicles that have been verified. Inherits Entity
    // may not be needed actually
    public:
        int prec;   // optional precedence variable
        Vehicle();
        ~Vehicle();
        Vehicle(Entity);
        Vehicle(Entity, int);
        
    private:
};

Entity ents[10];  // probably needs to be dynamically allocated.
Vehicle queue[10];

void setup()  // setup() runs once at the start
{
    pinMode(D1, INPUT);
    pinMode(C1, INPUT);
    pinMode(D2, INPUT);
    pinMode(C2, INPUT);
    
    pinMode(13, OUTPUT);
    
    Serial.begin(9600); // Serial is used to output results to the Serial Monitor
    
    fsensor1.set_scale(c_factor);
    fsensor2.set_scale(c_factor);
    // bsensors.set_scale(c_factor);   // set scales' calibration factors to use the data it gives us
    
    fsensor1.tare();
    fsensor2.tare();
    // bsensors.tare();    // set scales to 0
}

void addToQueue(Vehicle tba, int loc)   // tba = to be added
{
    // adds Vehicle to the overall queue.
    queue[loc] = tba;
}

void removeFromQueue(int loc)
{
    // removes Vehicle from the overall queue
    delete[] queue;
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
    int ctr = 0;
    float detwt1 = 0, detwt2 = 0;;
    
    if((detwt1 = (fsensor1.get_units())) > TOOLGT)
    {
        Serial.println("Weight detected 1: ");
        Serial.print(detwt1);  // check for valid weight
        ents[ctr].wt = detwt1;
        queue[ctr].wt = detwt1 + 1000;          //assuming what we are weighing for testing is way less than 1000 for 
        ctr++;                                  //processing to know which sensor it came from
    }
    if((detwt2 = (fsensor2.get_units())) > TOOLGT)
    {
        Serial.println("Weight detected 2: ");
        Serial.print(detwt2);  // check for valid weight
        ents[ctr].wt = detwt2;
        queue[ctr].wt = detwt2 + 2000;
        ctr++;
    }/*
    if(detwt[2] = (fsensors[2].get_units) > TOOLIGHT)
    {
        ents[ctr] = new Entity(detwt[2], millis());
        ctr++;
    }
    if(detwt[3] = (fsensors[3].get_units) > TOOLIGHT)
    {
        ents[ctr] = new Entity(detwt[3], millis());
        ctr++;
    }*/

    //entityCheck();
}

void entityCheck()
{
    Vehicle *tq;
    // validates each Entity's weight.
    for(int i = 0; i < QUEUESIZE; i++)
    {
        while(ents[i].wt < VALIDWT - OFFSET || ents[i].wt > VALIDWT + OFFSET)
            error_signal(); // for now, this infinite loop is fine.
        
        tq = new Vehicle(ents[i]);    
    }
    
}

void processEnts()
{
    
    //for processing multiple at a time
    queuecounter = 0;
    while (queuecounter < ctr)
    
    if(ents[queuecounter] > 1000 && < 2000)
    queue[queuecounter] = stopsignA;
    queuecounter = queuecounter + 1;                  //moves to next spot in queue
    else
    if{queue[queuecounter] > 2000 && < 3000]
    queue[queuecounter] = stopsignB;
    queuecounter = queuecounter + 1;
    else 
    if{queue[queuecounter] > 3000 && < 4000]
    queue[queuecounter] = stopsignC;
    queuecounter = queuecounter + 1;
    else
    if{queue[queuecounter] > 4000 && < 5000]
    queue[queuecounter] = stopsignD;
    queuecounter = queuecounter + 1;
    else
    endif
    endwhile
}
void processQueue()
{
    while (queue[ctr] > 0) 
    queue[0] = processSign
    if(processSign = stopsignA)
    fsensor1.GOSIGNAL**                     //set flag that executes go signal for that stop sign
    else
    if(processSign = stopsignB)
    fsensor2.GOSIGNAL**                     //set flag that executes go signal for that stopsign
    else
    //..and so on
    
    
}
}
Entity::Entity()
{
  wt = 1;
  tm = 0;
}

Vehicle::Vehicle()
{
  wt = 0;
  tm = 0;
}
Vehicle::Vehicle(Entity e)
{
    wt = e.wt;
    tm = e.tm;
    prec = 0;
}

Vehicle::Vehicle(Entity e, int p)
{
    wt = e.wt;
    tm = e.tm;
    prec = p;
}

Vehicle::~Vehicle()
{
  
}

Entity::Entity(float f, unsigned long l)
{
    wt = f;
    tm = l;
}

Entity::~Entity()
{
  
}

void loop()   // will loop for the remainder of the program's runtime
{
    receive();   
    //thread prc process();
    //thread tmr timer();
    // Concurrently receives new Vehicles into the queue while the queue is processed, and increments the timer
}
