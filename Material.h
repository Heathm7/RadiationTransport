#pragma once
#include <string>

struct MaterialStats {
	int entered = 0;
	int survived = 0;
};

struct Material {
	std::string name;		// Name of the material (eg. Lead, Water)
	double thickness;		// Thickness in cm
	double absorptionProb;  // Probability of absorption per step (0 <= p <= 1)
	MaterialStats stats;

	Material() : name(""), thickness(1.0), absorptionProb(0.01) {}
	Material(const std::string& n, double t, double p)
		: name(n), thickness(t), absorptionProb(p) {}
					
	// I(x) = I_0e^mux ~ Monte Carlo average of particle survival
};
