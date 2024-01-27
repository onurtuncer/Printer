#pragma once

#include <memory>
#include "GPIO/PinController.h"

namespace Printer{

  class Stepper {

    enum LeadScrewHandedness{
        Left,
        Right
    }

    public:
      explicit Stepper(std::shared_ptr<PinController> pinController,
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
                         m_IsHoming_(false),
                         m_StepsPerRevolution(stepsPerRevolution),
                         m_LeadScrewPitch(leadScrewPitch);

      virtual ~Stepper() = default;

      void Initialize() 
      void Home() 
      void MoveWithFixedVelocity(bool clockwise, unsigned int velocity); 
      void MoveToLimitSwitch(bool clockwise);
      void MoveAwayFromLimitSwitch(bool clockwise);
      void FindHomePosition();
      void Stop();
      double GetCurrentPositionInUnits() const;
      double GetPositioningAccuracy() const;
      void SetSoftLimits(double positiveLimit, double negativeLimit);
      void MoveToPosition(double targetPosition, unsigned int velocity);

    private:
      bool IsLimitSwitchPressed();
      bool IsWithinLimits(double targetPosition) const {

        return (targetPosition >= negativeSoftLimit_ && targetPosition <= positiveSoftLimit_);
    }
      
    private:
      std::shared_ptr<PinController> m_PinController;
      std::string m_StepPin;
      std::string m_DirPin;
      std::string m_LimitSwitchPin;
      long int    m_CurrentPosition{0};
      bool        m_IsHoming{false};
      bool        m_HasHomed{false};
      int         m_StepsPerRevolution;
      double      m_LeadScrewPitch;
      double      m_PositiveSoftLimit{10000.0};
      double      m_NegativeSoftLimit{-10000.0}; 
  };
} 