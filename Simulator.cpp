#include "Simulator.h"
#include <cmath>

Simulator::Simulator(int numParticles_, double stepSize_)
	: numParticles(numParticles_), stepSize(stepSize_), rng(std::random_device{}()), dist(0.0, 1.0)
{

}

// Add a material to the simulation
void Simulator::addMaterial(const Material& material) {
	materials.push_back(material);
}

void Simulator::run() {
	absorbedCount = 0;
	survivedCount = 0;
	survivedPerMaterial.resize(materials.size(), numParticles);

	for (int i = 0; i < numParticles; i++) {
		Particle particle;

		// Loop over each material
		for (size_t m = 0; m < materials.size(); m++) {
			const auto& mat = materials[m];
			int steps = static_cast<int>(mat.thickness / stepSize);

			for (int s = 0; s < steps; s++) {
				if (!particle.alive) break;

				// Bernoulli trial: particle absorption
				double r = dist(rng);
				if (r < mat.absorptionProb) {
					particle.alive = false;
					absorbedCount++;
				}
				else {
					particle.move(stepSize);
				}
			}

			// Update per-material survival
			if (!particle.alive) {
				survivedPerMaterial[m]--;	// Particle didnt survive this material
				break;						// Particle stops moving to next material
			}

		
			if (!particle.alive)
				break;
		}
	}

	survivedCount = numParticles - absorbedCount;
}

// Statistical analysis
double Simulator::survivalProbability() const {
	return static_cast<double>(survivedCount) / numParticles;
}

double Simulator::standardDeviation() const {
	double p = survivalProbability();
	
	return std::sqrt(p * (1.0 - p));
}

double Simulator::standardError() const {
	return standardDeviation() / std::sqrt(numParticles);
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

	// Theoretical comparison for a single material (simple case)
	if (!materials.empty()) {
		double mu = -std::log(1.0 - materials[0].absorptionProb) / stepSize;
		double theoretical = std::exp(-mu * materials[0].thickness);
		std::cout << "Theoretical fraction (first material only): " << theoretical << "\n";
	}

}
