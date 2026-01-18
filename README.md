## Monte Carlo Radiation Transport Simulator

A C++ Monte Carlo simulation that models particle attenuation through shielding materials.
This project highlights both **C++ Programming** and **Mathematical Modeling** skills.

--

## Overview

This simulation estimates the transmission and absorbtion of particles through a material slab using a probabilistic approach:

- Each particle moves in discrete steps through the material.
- At each step, the particle has a probability of being absorbed. 
- The simulation approximates the **Exponential Attenuation Law**

\[
I(x) - I_0 e^{-\mu x}
\]

where: 

- \(I(x)\) = particle intensity after traveling distance \(x\)
- \(I_0\)  = initial intensity 
- \(\mu\)  = material's macroscopic absorption coefficient

--

## Current Implementation

- Particle.h - defines particles with position, energy, and alive status
- Material.h - defines shielding materials with thickness and absorption probability
- Simulator.h / Simulator.cpp - Monte Carlo loop that moves particles through materials and records absorptions
- MonteCarloRadiationTransport.cpp - example fun of the simulator

--

## Example Output

Running the simulator with 10,000 particles, Lead (2cm, 5% absorption per step) and Water (5cm, 1% absorption per step):

Particles simulated: 10000
Particles survived: 2142
Fraction survived: 0.2142
Theoretical fraction (first material only): 0.358486

*> Monte Carlo simulation is stochastic, so results vary slightly.
*> Increasing particle count or decreasing step size improves accuracy.


## Key Features

- Modular C++ code structure
- Clear separation of **Particle**, **Material**, and **Simulator**
- Monte Carlo simulation loop
- Comparison of simulation results against theoretical predictions
- Statiscal uncertainty estimation
- Runtime measurement using std::chrono

--

## Interactive Simulation

The simulator now allows the user to:

1. Input the **number of particles** to simulate
2. Input the **step size** in cm
3. Input the **number of materials**
4. For each material, input:
	- Names
	- Thickness (cm)
	- Absorption probability per step (0-1)
	
This allows the user to simulate realistic shielding scenarios with multiple materials.

---

## Monte Carlo Convergence Demonstration

Monte Carlo radiation transport relies on statisical sampling. As the number of simulated particles increases, the numerical result should converge toward the analytical solution predicted by the exponential attenuation theory.

To demonstrate correct Monte Carlo behavior, the simulator was run with increasing particle counts using the same material configuration.

---

## Example Realistic Run

To demonstrate statistical convergence, the simulation was run with 500,000,000

Enter number of particles to simulate: 1000000000
Enter step size in cm: .1
Enter number of materials: 3
Material 1 name: Lead
Thickness in cm: 5
Absorption probability per step (0-1): .00995
Material 2 name: Concrete
Thickness in cm: 50
Absorption probability per step (0-1): .001
Material 3 name: Polyethylene
Thickness in cm: 30
Absorption probability per step (0-1): .0005
Particles simulated: 1000000000
Particles survived: 316535237
Fraction survived: 0.316535
Theoretical fraction (first material only): 0.606536
Simulation runtime: 11666.4seconds

*> The analytical prediction for this configuration is approximately **0.315**. As the number of particles increases, the Monte Carlo result converges toward the theoretical value, demonstrating correct stochastic behavior and numerical stability. This convergence behavior is a direct consequence of the Law of Large Numbers,
which governs Monte Carlo sampling methods.

## File Structure

/Header Files
Particle.h
Material.h
Simulator.h
/Source Files
simulator.cpp
MonteCarloRadiationTransport.cpp
.gitignore
README.md
MonteCarloRadiationTransport.sln

--

## Technologies

- C++17
- Visual Studio 2022 (MSVC)
- Git + Github for version control

--

## Next Steps

- Implement statistical analysis of surviving particles
- Add multi-material attenuation comparision
- Include optional plotting and simulated vs theoretical results
- include parallelization, show scaling from 2, 4 and 8 cores 
