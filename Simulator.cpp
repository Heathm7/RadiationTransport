#include "Simulator.h"
#include <cmath>

Simulator::Simulator(int numParticles_, double stepSize_)
	: numParticles(numParticles_), stepSize(stepSize_), survivedCount(0), absorbedCount(0)
{
	// RNG seeding
	std::random_device rd;
	rng.seed(rd());
	dist = std::uniform_real_distribution<double>(0.0, 1.0);
}

// Add a material to the simulation
void Simulator::addMaterial(const Material& material) {
	materials.push_back(material);
}

void Simulator::run() {
	absorbedCount = 0;
	survivedCount = 0;
	
	for (auto& mat : materials) {
		mat.stats.entered = 0;
		mat.stats.survived = 0;
	}

	// Loop over each particle
	for (int i = 0; i < numParticles; i++) {
		Particle particle;
		particle.alive = true;

		// Loop over each material
		for (auto& mat : materials) {
			if (!particle.alive) break;      // Stop if already absorbed

			++mat.stats.entered;              // Particle reaches this material

			int steps = static_cast<int>(mat.thickness / stepSize);

			for (int s = 0; s < steps; s++) {
				double r = dist(rng);
				if (r < mat.absorptionProb) {
					particle.alive = false;
					absorbedCount++;
					break;                     // stop this material
				}
				particle.move(stepSize);
			}

			if (particle.alive) {
				++mat.stats.survived;          // survived this material
			}
		}
	

		if (particle.alive)
			survivedCount++;	// Particle survived all materials
	}

}

// Statistical analysis
double Simulator::survivalProbability() const {
	return static_cast<double>(survivedCount) / numParticles;
}

double Simulator::standardDeviation() const {
	double p = survivalProbability();
	
	return (p == 0.0 || p == 1.0) ? 0.0 : std::sqrt(p * (1.0 - p));
}

double Simulator::standardError() const {
	double sigma = standardDeviation();

	return sigma / std::sqrt(numParticles);
}

//Print results
void Simulator::report() const {
	double p = survivalProbability();
	double sigma = standardDeviation();
	double stdError = standardError();

	double ci_low = p - 1.96 * stdError;
	double ci_high = p + 1.96 * stdError;


	std::cout << "Particles simulated: " << numParticles << '\n';
	std::cout << "Particles survived: " << survivedCount << '\n';
	std::cout << "Fraction survived: " << p << '\n';
	std::cout << "Standard deviation: " << sigma << '\n';
	std::cout << "Standard error: " << stdError << '\n';
	std::cout << "95% confidence interval: [" << ci_low << ", " << ci_high << "]\n";

	// Per-material survival statistics
	std::cout << "Material survival fractions and statistics: " << '\n';

	for (const auto& mat : materials) {
		double fraction = mat.stats.entered > 0 ? static_cast<double>(mat.stats.survived) / mat.stats.entered : 0.0;
		double matSigma = std::sqrt(fraction * (1.0 - fraction));
		double matStdError = matSigma / std::sqrt(mat.stats.entered);
		
		double ciLow = fraction - 1.96 * matStdError;
		double ciHigh = fraction + 1.96 * matStdError;

		std::cout << mat.name << '\n';
		std::cout << "Entered: " << mat.stats.entered << '\n';
		std::cout << "Survived: " << mat.stats.survived << '\n';
		std::cout << "Fraction Survived: " << fraction << '\n';
		std::cout << "Standard deviation: " << matSigma << '\n';
		std::cout << "Standard error: " << matStdError << '\n';
		std::cout << "95% confidence interval: [" << ciLow << ", " << ciHigh << "]\n";
	}

	// Theoretical comparison for a single material (simple case)
	if (!materials.empty()) {
		double mu = -std::log(1.0 - materials[0].absorptionProb) / stepSize;
		double theoretical = std::exp(-mu * materials[0].thickness);
		std::cout << "Theoretical fraction (first material only): " << theoretical << "\n";
	}

}
