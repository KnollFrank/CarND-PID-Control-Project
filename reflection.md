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

<ol>
  <li>Ki := Kp := Kd := 0</li>
  <li>tune Kd:
    <ol>
      <li>Kp := some small value <= 1</li>
      <li>Kd := 100 * Kp</li>
      <li>Now start increasing Kd until you see oscillation, excessive noise, or excessive (more than 50%) overshoot on the drive or plant output</li>
      <li>I like to push the gain up until the system is on the verge of oscillation then back the gain off by a factor of two or four.</li>
    </ol>
  </li>
  <li>tune Kp:
    <ol>
      <li>Kp = 1/100 * Kd</li>
      <li> If you see oscillation, drop the proportional gain by factors of eight or 10 until the oscillation stops.
        If you don’t see oscillation, increase the proportional gain by factors of eight or 10 until you start seeing oscillation or excessive overshoot.
        I usually tune right up to the point of too much overshoot then reduce the gain by a factor of two or four.
        Once you are close, fine tune the proportional gain by factors of two until you like what you see.
      </li>
    </ol>
  </li>
  <li>tune Ki:
    <ol>
      <li>Ki := Kp * Kp/Kd</li>
      <li>If you see oscillation, decrease the integrator gain by steps of 8 or 10 until the oscillation goes away.
      If you don’t see oscillation, increase the integrator gain by steps of 8 or ten until you do.
      From this point, try to find the gain where the system just breaks into oscillation, and then back the gain off by a factor of 2 or 4.
      </li>
    </ol>
  </li>
</ol>
