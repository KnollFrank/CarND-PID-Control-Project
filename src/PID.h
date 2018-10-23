#ifndef PID_H
#define PID_H

class PID {
 public:
  /*
   * Constructor
   */
  PID(double dt);

  /*
   * Destructor.
   */
  virtual ~PID();

  /*
   * Initialize PID.
   */
  void Init(double Kp, double Ki, double Kd);

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
  double prevCte;

  /*
   * Coefficients
   */
  double Kp;
  double Ki;
  double Kd;

  const double dt;
};

#endif /* PID_H */
