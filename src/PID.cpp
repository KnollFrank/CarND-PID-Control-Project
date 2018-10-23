#include "PID.h"

using namespace std;

/*
 * TODO: Complete the PID class.
 */

PID::PID(double _dt, double _Kp, double _Ki, double _Kd)
    : dt(_dt),
      Kp(_Kp),
      Ki(_Ki),
      Kd(_Kd),
      p_error(0.0),
      i_error(0.0),
      d_error(0.0) {
}

PID::~PID() {
}

void PID::UpdateError(double cte) {
  d_error = (cte - p_error) / dt;
  i_error += cte * dt;
  p_error = cte;
}

double PID::TotalError() {
  return Kp * p_error + Ki * i_error + Kd * d_error;
}

