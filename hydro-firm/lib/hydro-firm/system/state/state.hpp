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
 *
 */

/*
 * @author: Arun C S
 * @email: aruncs009@gmail.com
 * @since: 09-09-2022
 */

#ifndef SYSTEM_STATE_STATE_HPP
#define SYSTEM_STATE_STATE_HPP

#include <sensors/read-sensors/read-sensors.hpp>

namespace System {

// TODO(aruncs009@gmail.com) Add options to override these values
// Maximum allowed water level
const int16_t WATER_LEVEL_MAX_ALLOWED = 10;

// Maximum allowed water level
const int16_t WATER_LEVEL_MIN_ALLOWED = 0;

// Minimum allowed moisture level
const int16_t MOISTURE_LEVEL_MIN_ALLOWED = 10;

class State {
private:
  bool valveClosed = false;
  bool pumpOn = false;
  bool wateringCycleState = false;
  bool activeState = false;
  bool coolDownState = false;
  Sensors::ReadSensors *readSensors;

public:
  /*
   * Constructor
   */
  explicit State(Sensors::ReadSensors &readSensors);

  /*
   * Checks if the current water level is greater than or equal to maximum
   * allowed water level.
   */
  virtual auto isWaterLevelMax() -> bool;

  /*
   * Checks if the current water level is less than or equal to minimum allowed
   * water level.
   */
  virtual auto isWaterLevelMin() -> bool;

  /*
   * Checks if the current moisture level is less than or equal to minimum
   * allowed moisture level.
   */
  virtual auto isMoistureLevelMin() const -> bool;

  /**
   * Checks if the system is in Cool down state. Cool Down state will be enabled
   * after completing watering cycle for a predefined period of time. During
   * this period a new watering cycle will not be started.
   */
  virtual auto isCoolDownState() const -> bool;

  /*
   * Checks if the system is in Active state. System moves to the active state
   * after completing the cool down period. In Active state system can start a
   * watering cycle provided all conditions are met.
   */
  virtual auto isActiveState() const -> bool;

  /*
   * Checks if the system is in Watering Cycle State. In Watering Cycle State
   * system will start moving water to plant containers and hold the water in
   * plant containers for a predefined amount of time.
   */
  virtual auto isWateringCycleState() const -> bool;

  /**
   * Set the pump on or off state
   */
  virtual void setPumpOn(bool state);

  /*
   * Checks if the pump is working.
   */
  virtual auto isPumpOn() const -> bool;

  /**
   * Set the valve on or off state
   */
  virtual void setValveClosed(bool state);

  /*
   * Checks if the valve is closed.
   */
  virtual auto isValveClosed() const -> bool;

  /*
   * Set system state to Watering Cycling State. In this state pump will be on
   * and valve will be closed.
   */
  virtual void setWateringCycleState();

  /*
   * Reset system state from Watering Cycling State. In this state pump will be
   * off and valve will be open.
   */
  virtual void resetWateringCycleState();

  /*
   * Set system state to Cool Down State. In this state pump should be off and
   * valve should be closed.
   */
  virtual void setCoolDownState();

  /*
   * Reset system state from Cool Down State. In this state watering cycle can
   * be started. Here system transition into Active state.
   */
  virtual void resetCoolDownState();

  /*
   * Set system state to Active State. In this state watering cycle can be
   * started.
   */
  virtual void setActiveState();

  /*
   * Reset system state from Active State. In this state watering cycle can be
   * started. Here system transition into Cool Down state.
   */
  virtual void resetActiveState();
};
} // namespace System

#endif