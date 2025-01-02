#include <Arduino.h>

/*Number of encoders*/
#define NUM_ENCODERS 4

/*Encoder 1st*/
#define ENC1_A 32    // MOT 1A
#define ENC1_B 33   // MOT 1B

/*Encoder 2nd*/
#define ENC2_A 25
#define ENC2_B 26

/*Encoder 3rd*/
#define ENC3_A 34
#define ENC3_B 35

/*Encoder 4rd*/
#define ENC4_A 27
#define ENC4_B 4

const int ENC_A[NUM_ENCODERS] = {ENC1_A, ENC2_A, ENC3_A, ENC4_A};
const int ENC_B[NUM_ENCODERS] = {ENC1_B, ENC2_B, ENC3_B, ENC4_B};

#define ENC_RES 330 // Encoder resolution*Gearbox ratio: 11*30 -> 330 pulses per revolution

volatile long int cnt1 = 0; // Volatile as it changed during interrupt
volatile long int cnt2 = 0;
volatile long int cnt3 = 0;
volatile long int cnt4 = 0;

double th1 = 0; // Position angle in degrees
double th2 = 0;
double th3 = 0;
double th4 = 0;

void readEncoder1()
{
    int b1 = digitalRead(ENC1_B);
    cnt1 = (b1 > 0) ? (cnt1 + 1) : (cnt1 - 1);
}

void readEncoder2()
{
    int b2 = digitalRead(ENC2_B);
    cnt2 = (b2 > 0) ? (cnt2 + 1) : (cnt2 - 1);
    
}

void readEncoder3()
{
    int b3 = digitalRead(ENC3_B);
    cnt3 = (b3 > 0) ? (cnt3 + 1) : (cnt3 - 1);
}

void readEncoder4()
{
    int b4 = digitalRead(ENC4_B);
    cnt4 = (b4 > 0) ? (cnt4 + 1) : (cnt4 - 1);
}

void Init_Encoder()
{
    // Initialize all pins for the encoders
    for (int i = 0; i < NUM_ENCODERS; i++)
    {
        pinMode(ENC_A[i], INPUT);
        pinMode(ENC_B[i], INPUT);
    }

    attachInterrupt(digitalPinToInterrupt(ENC1_A), readEncoder1, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC2_A), readEncoder2, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC3_A), readEncoder3, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC4_A), readEncoder4, RISING);
}

void Get_Angle()
{
    th1 = cnt1 * 360 / ENC_RES; // Conversion between encoder count and degree
    th2 = cnt2 * 360 / ENC_RES;
    th3 = cnt3 * 360 / ENC_RES;
    th4 = cnt4 * 360 / ENC_RES;
}