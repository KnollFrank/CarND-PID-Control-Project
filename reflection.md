# Reflection

## The effect of the P, I, D components

TODO:
- Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
- Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.

## How the final hyperparameters were chosen

TODO:
- Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

The final hyperparameters were chosen through manual tuning.
The Tuning section of the document [PID Without a PhD](https://www.wescottdesign.com/articles/pid/pidWithoutAPhd.pdf) by Tim Wescott describes a manual method for tuning the hyperparameters of a PID controller:

- Ki = Kp = Kd = 0  
- adjusting differential gain:
  1. Set proportional gain to some small value (one or less)
  2. Start with about 100 times more differential gain than proportional gain: Kd := 100 * Kp
  3. Now start increasing the differential gain until you see oscillation, excessive noise, or excessive (more than 50%) overshoot on the drive or plant output
  4. I like to push the gain up until the system is on the verge of oscillation then back the gain off by a factor of two or four.
   
   tune proportional gain:
   1. set the proportional gain to a starting value between 1 and 100: 1 / 100 of the derivative gain value:
      Kp = 1.0/100.0 * Kd
   2. If you see oscillation, drop the proportional gain by factors of eight or 10 until the oscillation stops.
      If you don’t see oscillation, increase the proportional gain by factors of eight or 10 until you start seeing oscillation or excessive overshoot.
      I usually tune right up to the point of too much overshoot then reduce the gain by a factor of two or four.
      Once you are close, fine tune the proportional gain by factors of two until you like what you see.
   
   increasing integral gain:
   1a. setze integral gain Ki so, daß: Kp/Kd = Ki/Kp, also Ki := Kp/Kd * Kp = Kp^2/Kd
   1b. If you are not using derivative gain, a good starting value for the integrator gain will be around 1 / 100 of the proportional gain.
   2. If you see oscillation, decrease the integrator gain by steps of 8 or 10 until the oscillation goes away.
      If you don’t see oscillation, increase the integrator gain by steps of 8 or ten until you do.
      From this point, try to find the gain where the system just breaks into oscillation, and then back the gain off by a factor of 2 or 4.
