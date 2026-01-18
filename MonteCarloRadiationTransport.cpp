// MonteCarloRadiationTransport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "Simulator.h"
#include "Material.h"


int main()
{
    // Number of particles and step size
    int numParticles;
    std::cout << "Enter number of particles to simulate: ";
    std::cin >> numParticles;

    double stepSize;
    std::cout << "Enter step size in cm: ";
    std::cin >> stepSize;


    // Create the simulator
    Simulator sim(numParticles, stepSize);

    // Add materials
    int numMaterials;
    std::cout << "Enter number of materials: ";
    std::cin >> numMaterials;

    for (int i = 0; i < numMaterials; i++) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        std::string name;
        std::cout << "Material " << i + 1 << " name: ";
        std::getline(std::cin, name);

        double thickness;
        std::cout << "Thickness in cm: ";
        std::cin >> thickness;

        double absorptionProb;
        std::cout << "Absorption probability per step (0-1): ";
        std::cin >> absorptionProb;

        sim.addMaterial(Material(name, thickness, absorptionProb));

    } 

    // Timing start
    auto start = std::chrono::high_resolution_clock::now();

    // Run sim
    sim.run();

    auto end = std::chrono::high_resolution_clock::now();
    // Timing end

    // Print results
    sim.report();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Simulation runtime: " << elapsed.count() << "seconds" << "\n";

    return 0;
}

