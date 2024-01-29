 #pragma once

class LeadLagCompensator {

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

private:
    double m_LeadGain;
    double m_LagGain;
    double m_LeadTimeConstant;
    double m_LagTimeConstant;
    double m_Output{0.0}
};
