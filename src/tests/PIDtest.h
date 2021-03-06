#ifndef TESTS_PIDTEST_H_
#define TESTS_PIDTEST_H_

#include "../PID.h"

#include <gtest/gtest.h>

double getNewProcessVariable(const double PV, double output) {
  return PV + output * 0.20 - PV * 0.10;
}

TEST(PIDTest, shouldGetOutput) {
  // GIVEN
  PID pid(1.0, 0, 0, 0);

  // WHEN

  // THEN
  ASSERT_EQ(3, 1 + 2);
}

#endif /* TESTS_PIDTEST_H_ */
