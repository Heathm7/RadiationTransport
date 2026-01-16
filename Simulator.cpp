#include "Simulator.h"

Simulator::Simulator(int numParticles_, double stepSize_)
	: numParticles(numParticles_), stepSize(stepSize_), rng(std::random_device{}()), dist(0.0, 1.0)
{

}

// Add a material to the simulation
void Simulator::addMaterial(const Material& material) {
	materials.push_back(materials);
}

void Simulator::run() {
	absorbedCount = 0;

	for (int i = 0; i < numParticles; i++) {
		Particle particle :

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
