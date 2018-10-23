#include "PID.h"

using namespace std;

/*
 * TODO: Complete the PID class.
 */

PID::PID(double _dt)
    : dt(_dt) {
}

PID::~PID() {
}

// TODO: Init als Teil des Konstruktors durchführen?
void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->i_error = 0;
}

void PID::UpdateError(double cte) {
  d_error = (cte - p_error) / dt;
  i_error += cte * dt;
  p_error = cte;
}

double PID::TotalError() {
  return Kp * p_error + Ki * i_error + Kd * d_error;
}

