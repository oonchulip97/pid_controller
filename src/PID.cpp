#include "PID.h"

#include <cmath>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
  prev_error = 0.0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  p_error = cte;

  // Reset the integral term to prevent overcorrection when:
  // - cross-track-error is zero, i.e. vehicle is on the center of the lane
  // - previous cross-track-error is zero, i.e. vehicle is previously on the center of the lane
  // - corss-track-error changes sign, i.e. vehicle steer from one side of the lane to another
  if (cte == 0.0)
    i_error = 0.0;
  else if (prev_error == 0.0)
    i_error = cte;
  else if ((fabs(cte)/cte) != (fabs(prev_error)/prev_error))
    i_error = cte;
  else
    i_error += cte;

  d_error = cte - prev_error;

  prev_error = cte;
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return Kp * p_error + Ki * i_error + Kd * d_error;  // TODO: Add your total error calc here!
}
