#pragma once
#include <string>

// Particle represents a single particle moving through material
struct Particle {
	double position = 0.0;	// x in the material [cm]
	double energy = 1.0;	// normalized energy
	bool alive = true;		// true if particle hasnt been absorbed

	// Move particle by dx
	void move(double dx) {
		position += dx;
	}

	// Absorb particle with probability p (0 <= p <= 1)
	void absorb(double p) {
		// Random number comparison in Simulator.cpp
		// This represents a Bernoulli trial with probability p
		// P_survival = 1 - p
		// E[Transmission] ~ e^(-mu * x)
	}
};
