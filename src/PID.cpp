#include "PID.h"
#include <iostream>
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
}

PID::~PID() {
}

void PID::Init(double k_p, double k_i, double k_d) {


  	Kp = k_p;
  	Ki = k_i;
  	Kd = k_d;

  	p_error = 0.0;
  	i_error = 0.0;
  	d_error = 0.0;
  	pre_cte = 0.0;
  	
  	count = 0;
  	count_opt= 0;
  	count_it = 0;

  	ave_error = 0;
  	max_error = 0;

}

void PID::UpdateError(double cte) {

  	p_error  = cte;
  	i_error += cte;
  	d_error  = cte - pre_cte;
  	pre_cte = cte;

  	count ++;
  	count_opt ++;
  	ave_error += cte*cte;

  	if (count_opt > num_steps){
  		count_opt = 0;
  		ave_error = 0;
  		count_it ++;
  	}
}

double PID::TotalError() {
	return p_error * Kp + i_error * Ki + d_error * Kd;
}

double PID::AveError() {
  return ave_error/count_opt;
}

int PID::Count() {
  return count;
}

int PID::CountOpt() {
  return count_opt;
}

void PID::Twiddle(double AveError ){

  double sum_dp = fabs(dp[0])+fabs(dp[1]);
  if ( sum_dp <= tol ) {
    std::cout << "Reached the precision we wanted"<< std::endl;
		std::cout << "Sum_dp="<< sum_dp << std::endl;
	}

  if ( sum_dp > 0.2 and count_opt == 0) {
    std::cout << "********************* Iter="<< count_it<<"******************************"<<std::endl;
    std::cout << "From State=" << next_state << " , last_index=" << last_index << std::endl;
    switch (next_state) {
      case 0:{
        p[last_index] += dp[last_index];
        next_state = 1;
        break;
      }
      case 1:{
        if (AveError < fabs(best_error)) {
            best_error = AveError;
            dp[last_index] *= 1.1;
            next_state = 0;
            last_index = (last_index + 1) % 2;  
        } else {
            p[last_index] -= 2 * dp[last_index];
            next_state = 2;
        }
        break;
      }
      case 2: {
        if (AveError < fabs(best_error)) {
          best_error = AveError;
          dp[last_index] *= 1.1;
        } else {
          p[last_index] += dp[last_index];
          dp[last_index] *= 0.9;
        }
        next_state = 0;
        last_index = (last_index + 1) % 2;
        break;
      }        
    }

    std::cout << "To State =" << next_state << " , last_index=" << last_index << std::endl;
    std::cout << "AveError =" << AveError<<std::endl;
    std::cout << "dP values =" << dp[0] << " "<< dp[1]  << ",    Sum="<< dp[0]+dp[1]<<std::endl;

    Kp=p[0];
    Kd=p[1];
    std::cout << "Kp=" << Kp << " , Ki="<< Ki <<" , Kd="<< Kd << std::endl;
  }
  
}
