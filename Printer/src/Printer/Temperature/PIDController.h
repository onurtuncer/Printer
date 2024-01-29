#include <iostream>

namespace Printer::Temperature{


}

class LeadLagCompensator {
private:
    double leadGain;
    double lagGain;
    double leadTimeConstant;
    double lagTimeConstant;

public:
    LeadLagCompensator(double leadGain, double lagGain, double leadTimeConstant, double lagTimeConstant)
        : leadGain(leadGain), lagGain(lagGain), leadTimeConstant(leadTimeConstant), lagTimeConstant(lagTimeConstant) {}

    double Update(double input) {
        // Lead Compensator
        double leadCompensation = leadGain * (1 + leadTimeConstant * input);

        // Lag Compensator
        double lagCompensation = lagGain / (1 + lagTimeConstant * input);

        return leadCompensation * lagCompensation;
    }
};

class PIDController {
private:
    double kp;  // Proportional gain
    double ki;  // Integral gain
    double kd;  // Derivative gain

    double prevError;
    double integral;

public:
    PIDController(double kp, double ki, double kd)
        : kp(kp), ki(ki), kd(kd), prevError(0.0), integral(0.0) {}

    double Update(double setpoint, double processVariable) {
        double error = setpoint - processVariable;

        double proportional = kp * error;

        integral += ki * error;

        double derivative = kd * (error - prevError);
        prevError = error;

        return proportional + integral + derivative;
    }
};


