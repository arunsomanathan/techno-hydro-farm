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
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/*
 * @author: Arun C S
 * @email: aruncs009@gmail.com
 * @since: 08-09-2022
 */

#ifndef SENSORS_WATER_LEVEL_WATER_LEVEL_HPP
#define SENSORS_WATER_LEVEL_WATER_LEVEL_HPP

#include <sensors/sensor.hpp>

namespace Sensors {

static const std::string WATER_LEVEL_SENSOR = "Water Level Sensor";
static const SENSOR_TYPE WATER_LEVEL_TYPE = ANALOG;

class WaterLevelSensor : public Sensors::Sensor {

public:
  /*
   * Constructor for Water Level Sensor
   */
  explicit WaterLevelSensor(uint8_t readPin, uint8_t powerPin);
};

} // namespace Sensors

#endif