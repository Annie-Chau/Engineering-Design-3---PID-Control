#include <Arduino.h>
#include <PID_v1.h>

extern double th1_ref; 
extern double th2_ref; 
extern double th3_ref; 
extern double th4_ref; 
double kp = 10.0, ki = 5.0, kd = 0.05;

// Input, output, reference
PID MOT1_PID(&th1, &MOT1_cmd, &th1_ref, kp, ki, kd, DIRECT);
PID MOT2_PID(&th2, &MOT2_cmd, &th2_ref, kp, ki, kd, DIRECT);
PID MOT3_PID(&th3, &MOT3_cmd, &th3_ref, kp, ki, kd, DIRECT);
PID MOT4_PID(&th4, &MOT4_cmd, &th1_ref, kp, ki, kd, DIRECT);

// Set up the PID controller
void Init_PID()
{
  MOT1_PID.SetMode(AUTOMATIC);
  MOT1_PID.SetOutputLimits(-255, 255);
  MOT1_PID.SetSampleTime(10);

  MOT2_PID.SetMode(AUTOMATIC);
  MOT2_PID.SetOutputLimits(-255, 255);
  MOT2_PID.SetSampleTime(10);

  MOT3_PID.SetMode(AUTOMATIC);
  MOT3_PID.SetOutputLimits(-255, 255);
  MOT3_PID.SetSampleTime(10);

  MOT4_PID.SetMode(AUTOMATIC);
  MOT4_PID.SetOutputLimits(-255, 255);
  MOT4_PID.SetSampleTime(10);
}

// Run the controller
void Compute_PID()
{
  MOT1_PID.SetTunings(kp, ki, kd);
  MOT1_PID.Compute();

  MOT2_PID.SetTunings(kp, ki, kd);
  MOT2_PID.Compute();

  MOT2_PID.SetTunings(kp, ki, kd);
  MOT2_PID.Compute();

  MOT2_PID.SetTunings(kp, ki, kd);
  MOT2_PID.Compute();
}

