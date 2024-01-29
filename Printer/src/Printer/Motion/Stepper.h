#pragma once

#include <memory>
#include "GPIO/PinController.h"

namespace Printer::Motion{

  class Stepper {

    enum LeadScrewHandedness{
        Left,
        Right
    };

    public:
      explicit Stepper(std::shared_ptr<PinController> pinController,
                       const std::string& stepPin,
                       const std::string& dirPin,
                       const std::string& limitSwitchPin,
                       int stepsPerRevolution,
                       double leadScrewPitch);
                       
      virtual ~Stepper() = default;

      void Initialize();
      void Home();
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
      void MoveSteps(int steps, bool sense, unsigned int velocity);
      bool IsLimitSwitchPressed();
      bool IsWithinLimits(double targetPosition) const;
      
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
