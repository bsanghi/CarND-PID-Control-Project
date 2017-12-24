#ifndef PID_H
#define PID_H

#include <fstream>
using namespace std;

class PID {
public:
  
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double pre_cte;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  int count,count_opt,count_it;
  double ave_error;
  double max_error;

  bool use_twiddle=false;
  double best_error = 999.9;
  double tol = 0.2;
  int last_index = 0;
  int next_state = 0;
  int num_steps=1260*3;
  double PrevAveError = 0.0;

  double p[2] = { 0.20, 1.5}; 
  double dp[2] = { 0.05,  0.3}; 

  /*
  * Constructor
  */
  PID();

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

  double Throttle(double max_throttle);

  double AveError();

  int Count();
  int CountOpt();

  void Twiddle(double AveError);
};

#endif /* PID_H */
