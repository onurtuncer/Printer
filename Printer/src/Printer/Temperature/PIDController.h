#include <iostream>

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

int main() {
    // PID Controller parameters
    double kp = 1.0;
    double ki = 0.1;
    double kd = 0.01;

    // Lead-Lag Compensator parameters
    double leadGain = 2.0;
    double lagGain = 0.5;
    double leadTimeConstant = 0.1;
    double lagTimeConstant = 1.0;

    // Create PID controller and Lead-Lag Compensator
    PIDController pidController(kp, ki, kd);
    LeadLagCompensator compensator(leadGain, lagGain, leadTimeConstant, lagTimeConstant);

    // Simulation loop
    for (int time = 0; time < 100; ++time) {
        // Simulated process variable (replace with actual process measurement)
        double processVariable = 5.0;

        // Setpoint (desired value)
        double setpoint = 10.0;

        // Calculate PID control output
        double pidOutput = pidController.calculate(setpoint, processVariable);

        // Cascade with lead-lag compensator
        double finalControlOutput = compensator.calculate(pidOutput);

        std::cout << "Time: " << time << ", Control Output: " << finalControlOutput << std::endl;
    }

    return 0;
}
