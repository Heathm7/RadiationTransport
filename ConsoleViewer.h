#pragma once
#include <iostream>
#include <iomanip>
#include "SimulationStats.h"

class ConsoleViewer {
public:
	// Display the simulation results in the console
	static void report(const SimulationStats& stats) {
		double p = stats.survivalFraction();
		double sigma = std::sqrt(p * (1.0 - p));
		double stdError = sigma / std::sqrt(stats.numParticles);

		double ci_low = p - 1.96 * stdError;
		double ci_high = p + 1.96 * stdError;


		std::cout << "Particles simulated: " << stats.numParticles << '\n';
		std::cout << "Particles survived: " << stats.survived << '\n';
		std::cout << "Fraction survived: " << p << '\n';
		std::cout << "Standard deviation: " << sigma << '\n';
		std::cout << "Standard error: " << stdError << '\n';
		std::cout << "95% confidence interval: [" << ci_low << ", " << ci_high << "]\n";

		// Per-material survival statistics
		std::cout << '\n' << "Material survival fractions and statistics: " << '\n';

		for (const auto& mat : stats.materials) {
			double fraction = (mat.entered > 0) ? static_cast<double>(mat.survived) / mat.entered : 0.0;
			double matSigma = std::sqrt(fraction * (1.0 - fraction));
			double matStdError = (mat.entered > 0) ? matSigma / std::sqrt(mat.entered) : 0.0;

			double ciLow = fraction - 1.96 * matStdError;
			double ciHigh = fraction + 1.96 * matStdError;

			std::cout << mat.name << '\n';
			std::cout << "Entered: " << mat.entered << '\n';
			std::cout << "Survived: " << mat.survived << '\n';
			std::cout << "Fraction Survived: " << fraction << '\n';
			std::cout << "Standard deviation: " << matSigma << '\n';
			std::cout << "Standard error: " << matStdError << '\n';
			std::cout << "95% confidence interval: [" << ciLow << ", " << ciHigh << "]\n";
		}


		// Theoretical comparison for a single material (simple case)
		if (!stats.materials.empty()) {
			std::cout << "Theoretical fraction (first material only): " << stats.theoreticalFirstMaterial << "\n";
		}
	}
};

