#include "Simulator.h"

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

	for (int i = 0; i < numParticles; i++) {
		Particle particle;

		// Loop over each material
		for (const auto& mat : materials) {
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

			if (!particle.alive)
				break;
		}
	}
}

//Print results
void Simulator::report() const {
	int survived = numParticles - absorbedCount;
	double survivalFraction = static_cast<double>(survived) / numParticles;

	std::cout << "Particles simulated: " << numParticles << "\n";
	std::cout << "Particles survived: " << survived << "\n";
	std::cout << "Fraction survived: " << survivalFraction << "\n";

	// Theoretical comparison for a single material (simple case)
	if (!materials.empty()) {
		double mu = -std::log(1.0 - materials[0].absorptionProb) / stepSize;
		double theoretical = std::exp(-mu * materials[0].thickness);
		std::cout << "Theoretical fraction (first material only): " << theoretical << "\n";
	}

}
