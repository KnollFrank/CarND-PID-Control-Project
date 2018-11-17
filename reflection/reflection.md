# Reflection

## The effect of the P, I, D components

The formula for computing the output of the [PID controller](https://en.wikipedia.org/wiki/PID_controller) is:
$${\displaystyle \mathrm{Controlleroutput}(t) = P * \mathrm {CTE}(t)+I * \int _{0}^{t}\mathrm {CTE}(\tau )\,d\tau +D * {\frac {d\mathrm {CTE}(t)}{dt}}}$$
, where CTE is the cross track error and P, I and D are the parameters of the PID controller.

### P Controller

When setting the I and D parameters to zero and retaining only the P parameter value of 0.125, the car drives like this in the simulator: [P controller](https://github.com/KnollFrank/CarND-PID-Control-Project/raw/master/reflection/P_Controller.mp4).

As expected, the car overshoots and oscillates around the middle of the lane line.

## PD Controller

When setting only the I parameter to zero and retaining the P = 0.125 and D = 0.5 parameter values, the car drives like this in the simulator:
[PD controller](https://github.com/KnollFrank/CarND-PID-Control-Project/raw/master/reflection/PD_Controller.mp4).

As expected, the car drives close to the middle of the lane line, and doesn't overshoot or oscillate.

## PID Controller

AS there is no systematic bias (e.g. steering drift), there is no need for a non-zero I parameter.

## How the final hyperparameters were chosen

The Tuning section of the document [PID Without a PhD](https://www.wescottdesign.com/articles/pid/pidWithoutAPhd.pdf) by Tim Wescott describes a method for manually tuning the hyperparameters of a PID controller which can be expressed in pseudo code like this:

```
function find_param_where_system_just_breaks_into_oscillation(param):
  factor := 8 or 10
  if "oscillation":
    While "oscillation":
      param := param / factor
    param := param * factor
  else:
    While "no oscillation":
      param := param * factor

  fine_tuning_factor := 2 or 4
  While "oscillation":
    param := param / fine_tuning_factor

  return param

function tune():
  P := some small value <= 1
  I := 0
  D := 0

  D := find_param_where_system_just_breaks_into_oscillation(100 * P)
  P := find_param_where_system_just_breaks_into_oscillation(D / 100)
  I := find_param_where_system_just_breaks_into_oscillation(P * P / D)

  return P, I, D
```
Manually executing the function `tune()` with initial value P = 0.01 resulted in the final hyperparameters P = 0.125, I = 7.8125000000000023e-13 which is almost 0 and D = 0.5.
