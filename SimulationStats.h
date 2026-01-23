#pragma once
#include <vector>
#include <string>
#include "Material.h"

struct MaterialStatsSnapshot {
	std::string name;
	int entered = 0;
	int survived = 0;
};

struct SimulationStats {
	int numParticles = 0;	// Total particles simulated
	int survived = 0;		// Total particles survived
	int absorbed = 0;			// Total partcles absorbed
	double theoreticalFirstMaterial = 0.0;

	std::vector<MaterialStatsSnapshot> materials;

	double survivalFraction() const {
		return (numParticles > 0) ? static_cast<double>(survived) / numParticles : 0.0;
	}
};