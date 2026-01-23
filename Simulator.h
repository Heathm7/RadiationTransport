#pragma once
#include "Particle.h"
#include "Material.h"
#include "SimulationStats.h"
#include <vector>
#include <random>
#include <iostream>
#include <functional>


struct ThreadStats {
	int absorbed = 0;
	int survived = 0;
	std::vector<MaterialStats> matStats;
};

class Simulator {
public:
	Simulator(int numParticles, double stepSize, unsigned int numThreads_ = 0);

	// Add a material to the simulation
	void addMaterial(const Material& material);

	// Run the simulation
	void run();

	/*
	// Print results and compare theoretical prediction
	void reportPerMaterial() const; 
	void report() const;
	*/

	SimulationStats getStats() const;

	// Statistical analysis
	double survivalProbability() const;
	double standardDeviation() const;
	double standardError() const;

	void setNumThreads(unsigned int n) {
		numThreads = n;
	}

	using UpdateCallback = std::function<void(const SimulationStats&)>;
	void setUpdateCallback(UpdateCallback cb);

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
	unsigned int numThreads = 1;

	// Random number generator for absorption trials
	std::mt19937 rng;							// seed generator
	std::uniform_real_distribution<double> dist;

	// Track results
	int absorbedCount = 0;

	void simulateParticles(
		int numParticles,
		ThreadStats& stats,
		unsigned int seed
	);

	UpdateCallback updateCallback;
};
