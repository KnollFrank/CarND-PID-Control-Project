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

```
function find_param_where_system_just_breaks_into_oscillation(param):
  factor := 8 or 10
  if "oscillation":
    While "oscillation"
      param := param / factor
    param := param * factor
  else:
    While "no oscillation"
      param := param * factor

  fine_tuning_Factor := 2 or 4
  While "oscillation"
    param := param / fine_tuning_Factor

  return param

function tune():
  Ki := 0
  Kp := some small value <= 1
  Kd := 0

  Kd := find_param_where_system_just_breaks_into_oscillation(100 * Kp)
  Kp := find_param_where_system_just_breaks_into_oscillation(Kd / 100)
  Ki := find_param_where_system_just_breaks_into_oscillation(Kp * Kp / Kd)

  return Ki, Kp, Kd
```
