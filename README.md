# Rover-Wheel-Differential-Motor-Control-UdeG-Space
> This is the Mars Rover Wheel Differential Control Arduino code for UdeG Space Team.

This repository has the ROS and arduino implementation.  
The `wheel_cotrol.ino` file is the arduino node-handle subscriber that recieves the serial messages from the **cmd_vel** topic,
make the kinematics equations to transform the linear and angular velocities to angular velocities of each wheel,
and controls the wheel motors.  

From the *linear* and *angular* velocities provided by the `msg.linear.x` and `msg.angular.z` messages, respectively,
the angular velocities of the wheels are calculated from the following equations:  
$$\omega_l = \frac{2v-L\omega}{2R},\quad \omega_r = \frac{2v+L\omega}{2R}$$
Where
- $\omega_l$: Left wheel angular velocity
- $\omega_r$: Left wheel angular velocity
- $R$: Wheel radius
- $L$: Lenght from the center of the robot to one of the wheels
- $\omega$: Angular velocity
- $v$: Linear velocity

Then, a linear equation is calculated to convert the angular velocities to PWM  
$$P_x = \frac{P_{xmax}*\omega_x}{\omega_{xmax}}$$
Where
- $P_x$: Pwm value of the $x$ wheel
- $P_{xmax}$: The maximum value the pwm can take
- $\omega_x$: Angular velocity of the $x$ wheel
- $\omega_{xmax}$: The maximum value the angular velocity of the $x$ wheel can take
