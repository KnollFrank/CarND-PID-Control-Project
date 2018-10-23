#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

#include <gtest/gtest.h>
#include "tests/PIDtest.h"

// for convenience
using json = nlohmann::json;

// For converting back and forth between radians and degrees.
constexpr double pi() {
  return M_PI;
}
double deg2rad(double x) {
  return x * pi() / 180;
}
double rad2deg(double x) {
  return x * 180 / pi();
}

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  } else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main(int argc, char **argv) {
  if (argc > 1 && strcmp(argv[1], "test") == 0) {
    testing::InitGoogleTest(&argc, argv);
    // see https://stackoverflow.com/questions/7208070/googletest-how-to-skip-a-test
    // testing::GTEST_FLAG(filter) = "-PathPlannerTest.should_drive_with_max_50_mph";
    // testing::GTEST_FLAG(filter) = "ParametricSplineTest.*";
    // testing::GTEST_FLAG(filter) = "CoordsConverterTest.*";
    // testing::GTEST_FLAG(filter) = "PathPlannerTest.*";
    return RUN_ALL_TESTS();
  }

  uWS::Hub h;

  // https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops
  /*
   * PID Without a PhD, by Tim Wescott
   *
   * Ki = Kp = Kd = 0
   *
   * adjusting differential gain:
   * 1. Set proportional gain to some small value (one or less)
   * 2. Start with about 100 times more differential gain than proportional gain: Kd := 100 * Kp
   * 3. Now start increasing the differential gain until you see oscillation, excessive noise, or excessive (more than 50%) overshoot on the drive or plant output
   * 4. I like to push the gain up until the system is on the verge of oscillation then back the gain off by a factor of two or four.
   *
   * tune proportional gain:
   * 1. set the proportional gain to a starting value between 1 and 100: 1 / 100 of the derivative gain value: Kp = 1.0/100.0 * Kd
   * 2. If you see oscillation, drop the proportional gain by factors of eight or 10 until the oscillation stops.
   *    If you don’t see oscillation, increase the proportional gain by factors of eight or 10 until you start seeing oscillation or excessive overshoot.
   *    I usually tune right up to the point of too much overshoot then reduce the gain by a factor of two or four.
   *    Once you are close, fine tune the proportional gain by factors of two until you like what you see.
   *
   * increasing integral gain:
   * 1a. setze integral gain Ki so, daß: Kp/Kd = Ki/Kp, also Ki := Kp/Kd * Kp = Kp^2/Kd
   * 1b. If you are not using derivative gain, a good starting value for the integrator gain will be around 1 / 100 of the proportional gain.
   * 2. If you see oscillation, decrease the integrator gain by steps of 8 or 10 until the oscillation goes away.
   *    If you don’t see oscillation, increase the integrator gain by steps of 8 or ten until you do.
   *    From this point, try to find the gain where the system just breaks into oscillation, and then back the gain off by a factor of 2 or 4.
   */
// Version 1:
  // adjusting differential gain:
//  const double dt = 1.0;
//  const double Kp = 0.01;
//  const double Ki = 0;
//  const double Kd = (100 * Kp) / 2;
  // tune proportional gain:
//  const double dt = 1.0;
//  const double Kp = 1.0 / 100.0 * ((100 * 0.01) / 2) * 10 * 10 / 4;
//  const double Ki = 0;
//  const double Kd = (100 * 0.01) / 2;
  // increasing integral gain:
//  const double dt = 1.0;
//  const double Kp = 1.0 / 100.0 * ((100 * 0.01) / 2) * 10 * 10 / 4;
//  const double Ki = 0; // (Kp * Kp / (100 * 0.01) / 2) / 10 / 10 / 10 / 10 / 10 / 10 / 10 / 10 / 10 / 10;
//  const double Kd = (100 * 0.01) / 2;
  // Version 2:
  // adjusting differential gain:
//  const double dt = 1.0;
//  const double Kp = 0.01;
//  const double Ki = 0;
//  const double Kd = 100 * Kp;
  // tune proportional gain:
//  const double dt = 1.0;
//  const double Kp = 1.0 / 100.0 * (100 * 0.01) * 10 * 10 / 2 / 2 / 2 / 2;
//  const double Ki = 0;
//  const double Kd = 100 * 0.01;
  // increasing integral gain:
  const double dt = 1.0;
  const double Kp = 1.0 / 100.0 * (100 * 0.01) * 10 * 10 / 2 / 2 / 2 / 2;
  const double Kd = 100 * 0.01;
  const double Ki = Kp * Kp / Kd;
  PID pid(dt, Kp, Ki, Kd);

  h.onMessage(
      [&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
        // "42" at the start of the message means there's a websocket message event.
        // The 4 signifies a websocket message
        // The 2 signifies a websocket event
        if (length && length > 2 && data[0] == '4' && data[1] == '2')
        {
          auto s = hasData(std::string(data).substr(0, length));
          if (s != "") {
            auto j = json::parse(s);
            std::string event = j[0].get<std::string>();
            if (event == "telemetry") {
              // j[1] is the data JSON object
              double cte = std::stod(j[1]["cte"].get<std::string>());
              double speed = std::stod(j[1]["speed"].get<std::string>());
              double angle = std::stod(j[1]["steering_angle"].get<std::string>());
              double steer_value;
              /*
               * TODO: Calcuate steering value here, remember the steering value is
               * [-1, 1].
               * NOTE: Feel free to play around with the throttle and speed. Maybe use
               * another PID controller to control the speed!
               */
              pid.UpdateError(cte);
              steer_value = -pid.TotalError();

              // DEBUG
              std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

              json msgJson;
              msgJson["steering_angle"] = steer_value;
              msgJson["throttle"] = 0.3;
              auto msg = "42[\"steer\"," + msgJson.dump() + "]";
              std::cout << msg << std::endl;
              ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
          } else {
            // Manual driving
            std::string msg = "42[\"manual\",{}]";
            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          }
        }
      });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest(
      [](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
        const std::string s = "<h1>Hello world!</h1>";
        if (req.getUrl().valueLength == 1)
        {
          res->end(s.data(), s.length());
        }
        else
        {
          // i guess this should be done more gracefully?
          res->end(nullptr, 0);
        }
      });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection(
      [&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
        ws.close();
        std::cout << "Disconnected" << std::endl;
      });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  h.run();
}
