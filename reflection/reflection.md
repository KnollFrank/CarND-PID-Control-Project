# Reflection

## The effect of the P, I, D components

TODO:
- Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
- Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.

The formula for computing the output of the PID controller is:

${\displaystyle \mathrm{Controlleroutput}(t) = P * \mathrm {CTE}(t)+I * \int _{0}^{t}\mathrm {CTE}(\tau )\,d\tau +D * {\frac {d\mathrm {CTE}(t)}{dt}}}$, where CTE is the cross track error and P, I and D are the parameters of the PID controller.

P controller:
- overshoots (see "4. Implementing P controller", 1:20)
- oscillations: oscillates faster when Kp gets bigger.

P = 0.125, I = 0, D = 0

[P controller](https://github.com/KnollFrank/CarND-PID-Control-Project/raw/master/reflection/P_Controller.mp4)

PD controller: (7. PD Controller)
- avoids overshoot (oscillations)

P = 0.125, I = 0, D = 0.5

[PD controller](https://github.com/KnollFrank/CarND-PID-Control-Project/raw/master/reflection/PD_Controller.mp4)

Systematic Bias (steering drift) kann nicht durch PD controller gelöst werden.

PID controller:
- solves systematic bias problem.

![PID](PID.png)


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
Manually executing the function `tune()` with initial value P = 0.01 resulted in the final hyperparameters P = 0.125, I = 7.8125000000000023e-13 and D = 0.5.
