/*
    Traffic Management System
    Master Program
    v 0.0.1 
    
    15 February 2016:::::Created repository and started basic code setup for the program.
*/

float wt;

void setup()  // setup() runs once at the start
{
    pinMode(13, OUTPUT);
    pinMode(A0, INPUT); // unsure if this works, will test once the prototype is complete.
}

void loop()   // will loop for the remainder of the program's runtime
{
    digitalWrite(13, LOW);  // set LED to off
    
    wt = analogRead(A0);  // unsure; trying to read the weight value detected by the load cell in pin A0.
}
