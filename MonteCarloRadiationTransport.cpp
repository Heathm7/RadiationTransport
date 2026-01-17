// MonteCarloRadiationTransport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
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

    // Run sim
    sim.run();

    // Print results
    sim.report();

    return 0;
}

