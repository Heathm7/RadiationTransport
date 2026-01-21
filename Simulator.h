#pragma once
#include "Particle.h"
#include "Material.h"
#include <vector>
#include <random>
#include <iostream>


class Simulator {
public:
	Simulator(int numParticles, double stepSize);

	// Add a material to the simulation
	void addMaterial(const Material& material);

	// Run the simulation
	void run();

	// Print results and compare theoretical prediction
	void reportPerMaterial() const; 
	void report() const;

	// Statistical analysis
	double survivalProbability() const;
	double standardDeviation() const;
	double standardError() const;

private:
	int numParticles;								// Number of particles in simulation
	int survivedCount;								// Number of survived particles
	double stepSize;								// Step size in cm
	std::vector<Material> materials;				// List of materials
	std::vector<int> absorbedPerMaterial;
	std::vector<int> survivedPerMaterial;			// number of particles survived per material
	std::vector<double> survivalProbPerMaterial;	// fraction survived per material
	std::vector<double> stdDevPerMaterial;			// standard deviation per material
	std::vector<double> stdErrorPerMaterial;		// standard error per material

	// Random number generator for absorption trials
	std::mt19937 rng;							// seed generator
	std::uniform_real_distribution<double> dist;

	// Track results
	int absorbedCount = 0;

	void simulateParticles(
		int numParticlesLocal,
		std::vector<Material>& materials,
		int& survivedLocal,
		std::vector<MaterialStats>& localStats,
		unsigned int seedOffset
	);
};
