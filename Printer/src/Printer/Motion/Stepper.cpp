

#include "Stepper.h"

namespace Printer{

  Printer::Stepper(std::shared_ptr<PinController> pinController,
                   const std::string& stepPin,
                   const std::string& dirPin,
                   const std::string& limitSwitchPin,
                   int stepsPerRevolution,
                   double leadScrewPitch)
                    : m_pinController_(pinController),
                      m_stepPin_(stepPin),
                      m_dirPin_(dirPin),
                      m_limitSwitchPin_(limitSwitchPin),
                      m_currentPosition_(0),
                      m_isHoming_(false),
                      m_stepsPerRevolution_(stepsPerRevolution),
                      m_leadScrewPitch_(leadScrewPitch) {}

void Initialize() {
    // Additional initialization steps if needed
}

void Printer::Home() {
  // Approach home position with fixed velocity
  MoveWithFixedVelocity(true, 10000); // Example: Move clockwise with a velocity of 10m  
  // Touch the limit switch and move away
  MoveToLimitSwitch(true);
  MoveAwayFromLimitSwitch(false)  
  // Slowly approach the limit switch again and find the precise home position
  findHomePosition();
  }

void Printer::MoveWithFixedVelocity(bool clockwise, unsigned int velocity) {

  m_PinController->SetDirection(m_DirPin, clockwise);

  // Move the stepper motor until the limit switch is pressed or a certain number of steps is reached
  while (!isLimitSwitchPressed() && currentPosition_ < stepsPerRevolution_) {

    m_PinController->SendPulse(m_StepPin);

    // Add a delay to control the stepper motor velocity
    usleep(velocity);

    currentPosition_ += (clockwise ? 1 : -1);
    }

    Stop();
  }

void Stepper::MoveToLimitSwitch(bool clockwise) {
    // Move the stepper motor towards the limit switch
    moveWithFixedVelocity(clockwise, 10000); // Example: Move clockwise with a velocity of 10ms
}

void Stepper::MoveAwayFromLimitSwitch(bool clockwise) {
  // Move the stepper motor away from the limit switch
  MoveWithFixedVelocity(!clockwise, 10000); // Example: Move counterclockwise with a velocity of 10ms
}

void Stepper::FindHomePosition() {
  // Slowly approach the limit switch
  MoveWithFixedVelocity(true, 1000); // Example: Move clockwise with a very slow velocity of 1ms

  // Keep track of the rising edge
  int initialPosition = currentPosition_;
  while (!isLimitSwitchPressed() && currentPosition_ < stepsPerRevolution_) {

      m_PinController->SendPulse(stepPin_);
      usleep(1000); // Example: Delay for 1ms
      m_CurrentPosition++;
  }

  // Keep track of the falling edge
  int finalPosition = currentPosition_;
  while (isLimitSwitchPressed() && currentPosition_ < stepsPerRevolution_) {
    pinController_->SendPulse(stepPin_);
    usleep(1000); // Example: Delay for 1ms
    currentPosition_++;
  }

  // Calculate the middle position between the rising and falling edges
  int middlePosition = (initialPosition + finalPosition) / 2  
  // Move to the calculated home position
  moveSteps(middlePosition - currentPosition_, true, 1000); // Example: Move clockwise with a very slow velocity of 1m  
  // Set the home position
  m_CurrentPosition = 0  
  // Stop the motor
  stop();
  m_HasHomed = true;
}

  void Stepper::Stop() {
  // Stop the motor (if applicable)
  }
  
  double Stepper::GetCurrentPositionInUnits() const {
    // Calculate the current position in units (e.g., millimeters) based on lead screw pitch
    return m_CurrentPosition * m_LeadScrewPitch;
  }

  void Stepper::SetSoftLimits(double positiveLimit, double negativeLimit) {

    m_PositiveSoftLimit = positiveLimit;
    m_NegativeSoftLimit = negativeLimit;
  }

  void Stepper::MoveToPosition(double targetPosition, unsigned int velocity) {
    // Check if the target position is within the allowed range
    if (isWithinLimits(targetPosition)) {
        // Calculate the difference between the current position and the target position
        double positionDifference = targetPosition - getCurrentPositionInUnits();

        // Calculate the required number of steps to reach the target position
        int stepsToMove = static_cast<int>(std::round(positionDifference / leadScrewPitch_));

        // Set the direction based on the sign of the difference
        bool clockwise = (positionDifference >= 0);

        // Move the stepper motor to the target position
        moveSteps(std::abs(stepsToMove), clockwise, velocity);
    } else {
        std::cout << "Error: Target position is outside the allowed limits." << std::endl;
    }
}

  bool Stepper::IsLimitSwitchPressed() {

    return m_PinController->ReadLimitSwitch(m_LimitSwitchPin);
  }

 bool Stepper::IsWithinLimits(double targetPosition) const {

    return (targetPosition >= m_NegativeSoftLimit && targetPosition <= m_PositiveSoftLimit);
  }

}