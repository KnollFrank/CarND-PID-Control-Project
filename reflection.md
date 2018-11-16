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

  While "oscillation"
    param := param / 2

  return param
```
<ol>
  <li>Ki := Kp := Kd := 0</li>
  <li>tune Kd:
    <ol>
      <li>Kp := some small value <= 1</li>
      <li>Kd := 100 * Kp</li>
      <li>
        <pre>
          <code>
While "no oscillation and no excessive overshoot"
begin
  increase Kd
end
Kd := Kd / 2 or Kd := Kd / 4</code>
        </pre>
    </ol>
  </li>
  <li>tune Kp:
    <ol>
      <li>Kp = Kd / 100</li>
      <li>
      <pre>
        <code>
While "oscillation"
begin
  Kp := Kp / 8 or Kp := Kp / 10
end
While "no oscillation"
begin
  Kp := Kp * 8 or Kp := Kp * 10
end
While "oscillation"
begin
  Kp := Kp / 2
end</code>
      </pre>
      </li>
    </ol>
  </li>
  <li>tune Ki:
    <ol>
      <li>Ki := Kp<sup>2</sup>/Kd</li>
      <li>
      <pre>
        <code>
While "oscillation"
begin
  Ki := Ki / 8 or Ki := Ki / 10
end
While "no oscillation"
begin
  Ki := Ki * 8 or Ki := Ki * 10
end
Ki := Ki / 2 or Ki := Ki / 4
</code>
      </pre>
      </li>
    </ol>
  </li>
</ol>
