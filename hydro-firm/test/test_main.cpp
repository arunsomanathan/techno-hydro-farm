/*
 * MIT License
 *
 * Copyright (c) 2022 ARUN C S
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * @author: Arun C S
 * @email: aruncs009@gmail.com
 * @since: 01-10-2022
 */

#include "main.cpp" //NOLINT(bugprone-suspicious-include)
#include "test_data/test_process/mock-process.hpp"
#include "test_executor/mock-executor.hpp"
#include "test_sensors/mock-sensors.hpp"
#include "test_sensors/test_read-sensors/mock-read-sensors.hpp"
#include "test_system/test_controller/mock-controller.hpp"
#include "test_system/test_state/mock-state.hpp"
#include <gmock/gmock.h>
#include <memory>

#ifdef ARDUINO
#include <Arduino.h>
#include <cstdint>

const uint32_t BAUD_RATE = 115200;

// Delay in executing system loop
const uint32_t DELAY = 1000; // In milliseconds

void setup() {
  // should be the same value as for the `test_speed` option in "platformio.ini"
  // default value is test_speed=115200
  Serial.begin(BAUD_RATE);

  ::testing::InitGoogleMock();
}

void loop() {
  // Run tests
  RUN_ALL_TESTS();

  // sleep 1 sec
  delay(DELAY);
}

#else

using ::testing::Exactly;

TEST(MainTest, TestLoopAndSetup) {           // NOLINT
  std::list<Sensors::Sensor *> sensors = {}; // NOLINT(cppcoreguidelines-init-variables)
  MockReadSensors mockReadSensors(sensors);
  MockSystemState mockState(mockReadSensors);
  MockSystemController mockController(mockState);
  MockSystemProcess mockSystemProcess(mockController, mockState);
  MockDataProcess mockDataProcess;
  MockExecutor executor(mockReadSensors, mockSystemProcess, mockDataProcess);
  EXPECT_CALL(executor, loop()).Times(Exactly(1));
  EXPECT_CALL(executor, setup()).Times(Exactly(1));
  run(executor, 1);
}

auto main(int argc, char **argv) -> int {
  ::testing::InitGoogleMock(&argc, argv);
  RUN_ALL_TESTS();
  // Always return zero-code and allow PlatformIO to parse results
  return 0;
}
#endif