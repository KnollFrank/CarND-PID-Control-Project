#ifndef PID_H
#define PID_H

class PID {
 public:
  /*
   * Constructor
   */
  PID(double dt, double Kp, double Ki, double Kd);

  /*
   * Destructor.
   */
  virtual ~PID();

  /*
   * Update the PID error variables given cross track error.
   */
  void UpdateError(double cte);

  /*
   * Calculate the total PID error.
   */
  double TotalError();

 private:
  /*
   * Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /*
   * Coefficients
   */
  const double Kp;
  const double Ki;
  const double Kd;
  const double dt;
};

#endif /* PID_H */
