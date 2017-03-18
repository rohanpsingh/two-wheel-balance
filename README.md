# two-wheel-balance
Arduino code for a two-wheeled self balancing robot: employs a PID controller to achieve stable balance.

Tune parameters are hard coded in the control loop.

Uses the MPU 6050 IMU and a Kalman filter to calculate the values of tilt angles in real time.
