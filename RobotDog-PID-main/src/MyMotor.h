#include <Arduino.h>

#define MOT1_A 12 
#define MOT1_B 14 

#define MOT2_A 13 
#define MOT2_B 15

#define MOT3_A 18 
#define MOT3_B 19

#define MOT4_A 5 
#define MOT4_B 23

#define MOT1_Channel 0 
#define MOT2_Channel 1
#define MOT3_Channel 2
#define MOT4_Channel 3

#define PWM_FREQ 10000 // PWM Frequency: 10kHz refers to how fast the signal alternates between ON and OFF in one second
#define PWM_RES 8      // PWM resolution 255 - 8-bit resolution -> From 0 to 255 because we have 2^8 = 256 steps

double MOT1_cmd = 0; // MOT1 command [-255; 255]
double MOT2_cmd = 0;
double MOT3_cmd = 0;
double MOT4_cmd = 0;

// Prepare the communication to control the motor
void Init_Motor()
{
    pinMode(MOT1_A, OUTPUT);
    pinMode(MOT1_B, OUTPUT);
    ledcSetup(MOT1_Channel, PWM_FREQ, PWM_RES);

    pinMode(MOT2_A, OUTPUT);
    pinMode(MOT2_B, OUTPUT);
    ledcSetup(MOT2_Channel, PWM_FREQ, PWM_RES);

    pinMode(MOT3_A, OUTPUT);
    pinMode(MOT3_B, OUTPUT);
    ledcSetup(MOT3_Channel, PWM_FREQ, PWM_RES);

    pinMode(MOT4_A, OUTPUT);
    pinMode(MOT4_B, OUTPUT);
    ledcSetup(MOT4_Channel, PWM_FREQ, PWM_RES);
}

// Send signals to the motor to tell it how fast and which direction it should be rotating
void Send_PWM(int PINA, int PINB, double mot_cmd, int channel)
{
    
    if (mot_cmd < 0)
    {
        ledcAttachPin(PINB, channel);
        ledcDetachPin(PINA);
        digitalWrite(PINA, LOW);
        ledcWrite(channel, abs(mot_cmd));
    }
   
    else 
    {
        ledcAttachPin(PINA, channel);
        ledcDetachPin(PINB);
        digitalWrite(PINB, LOW);
        ledcWrite(channel, abs(mot_cmd));
    }
}

// Combines every function to operate the motor
void Run_Motor()
{
    Send_PWM(MOT1_A, MOT1_B, MOT1_cmd, MOT1_Channel);
    Send_PWM(MOT2_A, MOT2_B, MOT2_cmd, MOT2_Channel);
    Send_PWM(MOT3_A, MOT3_B, MOT3_cmd, MOT3_Channel);
    Send_PWM(MOT4_A, MOT4_B, MOT4_cmd, MOT4_Channel);
}
