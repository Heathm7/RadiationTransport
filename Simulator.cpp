#include "Simulator.h"
#include <cmath>
#include <random>
#include <thread>


Simulator::Simulator(int numParticles_, double stepSize_, unsigned int numThreads_)
	: numParticles(numParticles_), stepSize(stepSize_), survivedCount(0), absorbedCount(0)
{
	// RNG seeding
	std::random_device rd;
	rng.seed(rd());
	dist = std::uniform_real_distribution<double>(0.0, 1.0);

	numThreads = (numThreads_ > 0) ? numThreads_ : std::thread::hardware_concurrency();
	if (numThreads == 0)
		numThreads == 1;
}

// Add a material to the simulation
void Simulator::addMaterial(const Material& material) {
	materials.push_back(material);
}

void Simulator::simulateParticles(int localParticles, ThreadStats& stats, unsigned int seed) {
	std::mt19937 rng(std::random_device{}() + seed);
	std::uniform_real_distribution<double> dist(0.0, 1.0);

	for (int i = 0; i < localParticles; i++) {
		Particle particle;
		particle.alive = true;

		for (size_t m = 0; m < materials.size(); m++) {
			if (!particle.alive) break;

			const auto& mat = materials[m];
			auto& matStats = stats.matStats[m];
			++matStats.entered;

			int steps = static_cast<int>(mat.thickness / stepSize);

			for (int s = 0; s < steps; s++) {
				double r = dist(rng);
				if (r < mat.absorptionProb) {
					particle.alive = false;
					stats.absorbed++;
					break;
				}
				particle.move(stepSize);
			}

			if (particle.alive) {
				++matStats.survived;
			}
		}

		if (particle.alive)
			stats.survived++;
		
		if (updateCallback && i % 100 == 0)
			updateCallback(getStats());
	}
}

void Simulator::run() {
	absorbedCount = 0;
	survivedCount = 0;
	
	for (auto& mat : materials) {
		mat.stats.entered = 0;
		mat.stats.survived = 0;
	}

	// Determine number of threads in users system
	std::vector<ThreadStats> threadStats(numThreads);
	std::vector<std::thread> threads;

	int particlesPerThread = numParticles / numThreads;
	int remainder = numParticles % numThreads;

	for (unsigned int t = 0; t < numThreads; t++) {
		threadStats[t].matStats.resize(materials.size());

		int localParticles = particlesPerThread + (t < remainder ? 1 : 0);

		threads.emplace_back(
			&Simulator::simulateParticles,
			this,
			localParticles,
			std::ref(threadStats[t]),
			static_cast<unsigned int>(t)
		);
	}

	for (auto& th : threads)
		th.join();

	// Add together
	for (const auto& ts : threadStats) {
		absorbedCount += ts.absorbed;
		survivedCount += ts.survived;

		for (size_t m = 0; m < materials.size(); m++) {
			materials[m].stats.entered += ts.matStats[m].entered;
			materials[m].stats.survived += ts.matStats[m].survived;
		}
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

SimulationStats Simulator::getStats() const {
	SimulationStats stats;
	stats.numParticles = numParticles;
	stats.survived = survivedCount;
	stats.absorbed = absorbedCount;
	
	for (const auto& mat : materials) {
		MaterialStatsSnapshot m;
		m.name = mat.name;
		m.entered = mat.stats.entered;
		m.survived = mat.stats.survived;
		stats.materials.push_back(m);
	}

	if (!materials.empty()) {
		double mu = -std::log(1.0 - materials[0].absorptionProb) / stepSize;
		stats.theoreticalFirstMaterial = std::exp(-mu * materials[0].thickness);
	}

	return stats;
}

