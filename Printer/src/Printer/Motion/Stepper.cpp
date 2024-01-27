
#include <cmath>
#include "Stepper.h"

namespace Printer{

  Stepper::Stepper(std::shared_ptr<PinController> pinController,
                   const std::string& stepPin,
                   const std::string& dirPin,
                   const std::string& limitSwitchPin,
                   int stepsPerRevolution,
                   double leadScrewPitch)
                    : m_PinController(pinController),
                      m_StepPin(stepPin),
                      m_DirPin(dirPin),
                      m_LimitSwitchPin(limitSwitchPin),
                      m_CurrentPosition(0),
                      m_IsHoming(false),
                      m_StepsPerRevolution(stepsPerRevolution),
                      m_LeadScrewPitch(leadScrewPitch) {}

  void Stepper::Initialize() {
    // Additional initialization steps if needed
  }

  void Stepper::Home() {
    // Approach home position with fixed velocity
    MoveWithFixedVelocity(true, 10000); // Example: Move clockwise with a velocity of 10m  
    // Touch the limit switch and move away
    MoveToLimitSwitch(true);
    MoveAwayFromLimitSwitch(false);
    // Slowly approach the limit switch again and find the precise home position
    FindHomePosition();
  }

  void Stepper::MoveWithFixedVelocity(bool sense, unsigned int velocity) {

    m_PinController->WriteValueToPin(m_DirPin, sense);
  
    // Move the stepper motor until the limit switch is pressed or a certain number of steps is reached
    while (!IsLimitSwitchPressed() && m_CurrentPosition < m_StepsPerRevolution) {
  
      m_PinController->SendPulse(m_StepPin);
  
      // Add a delay to control the stepper motor velocity
      usleep(velocity);
  
      m_CurrentPosition += (sense ? 1 : -1);
    }

    Stop();
  }

  void Stepper::MoveToLimitSwitch(bool clockwise) {
    // Move the stepper motor towards the limit switch
    MoveWithFixedVelocity(clockwise, 10000); // Example: Move clockwise with a velocity of 10ms
  }

  void Stepper::MoveAwayFromLimitSwitch(bool clockwise) {
    // Move the stepper motor away from the limit switch
    MoveWithFixedVelocity(!clockwise, 10000); // Example: Move counterclockwise with a velocity of 10ms
  }

  void Stepper::FindHomePosition() {
    // Slowly approach the limit switch
    MoveWithFixedVelocity(true, 1000); // Example: Move clockwise with a very slow velocity of 1ms
  
    // Keep track of the rising edge
    int initialPosition = m_CurrentPosition;
    while (!IsLimitSwitchPressed() && m_CurrentPosition < m_StepsPerRevolution) {
  
        m_PinController->SendPulse(m_StepPin);
        usleep(1000); // Example: Delay for 1ms
        m_CurrentPosition++;
    }

    // Keep track of the falling edge
    int finalPosition = m_CurrentPosition;
    while (IsLimitSwitchPressed() && m_CurrentPosition < m_StepsPerRevolution) {
      m_PinController->SendPulse(m_StepPin);
      usleep(1000); // Example: Delay for 1ms
      m_CurrentPosition++;
    }

    // Calculate the middle position between the rising and falling edges
    int middlePosition = (initialPosition + finalPosition) / 2; 
    // Move to the calculated home position
    MoveSteps(middlePosition - m_CurrentPosition, true, 1000); // Example: Move clockwise with a very slow velocity of 1m  
    // Set the home position
    m_CurrentPosition = 0;  
    // Stop the motor
    Stop();
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
    if (IsWithinLimits(targetPosition)) {
        // Calculate the difference between the current position and the target position
        double positionDifference = targetPosition - GetCurrentPositionInUnits();

        // Calculate the required number of steps to reach the target position
        int stepsToMove = static_cast<int>(std::round(positionDifference / m_LeadScrewPitch));

        // Set the direction based on the sign of the difference
        bool sense = (positionDifference >= 0);

        // Move the stepper motor to the target position
        MoveSteps(std::abs(stepsToMove), sense, velocity);
    } else {
        std::cout << "Error: Target position is outside the allowed limits." << std::endl;
    }
  }

  void Stepper::MoveSteps(int steps, bool sense, unsigned int velocity) {

    m_PinController->WriteValueToPin(m_DirPin, sense);

    for (int i = 0; i < steps; ++i) {

      m_PinController->SendPulse(m_StepPin);

      // Add a delay to control the stepper motor velocity
      usleep(velocity);
    }

    // Assuming you want to update the current position after moving
    m_CurrentPosition += (sense ? steps : -steps);
  }

  bool Stepper::IsLimitSwitchPressed() {

    return m_PinController->ReadPin(m_LimitSwitchPin);
  }

  bool Stepper::IsWithinLimits(double targetPosition) const {

    return (targetPosition >= m_NegativeSoftLimit && targetPosition <= m_PositiveSoftLimit);
  }

}