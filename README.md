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

For a simulation with N amount of particles and multiple shielding materials (Lead, Concrete, Polyethylene, etc.), the following statistics can be retrieved:

- Surival fraction: N_survived / N
- Standard deviation: sqrt(survivalFraction(1 - survivalFraction))
- Standard error: sigma / sqrt(N)
- 95% confidence interval: [(sigma - stdError), (sigma + stdError)]

The reported confidence interval demonstates converge as athe number of simulated particles increases. The Monte Carlo survival fraction is expected to be lower than the analytical solution for a single material due to additional attenuation from multiple shielding layers. 

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
Particles survived: 316558334
Fraction survived: 0.316558
Standard deviation: 0.465133
Standard error: 1.47088e-05
95% confidence interval: [0.31653, 0.316587]

Material survival fractions and statistics:
Lead
Entered: 1000000000
Survived: 0.606547
Fraction Survived: 0.606547
Standard deviation: 0.488516
Standard error: 1.54482e-05
95% confidence interval: [0.316528, 0.316589]
Concrete
Entered: 606546925
Survived: 0.60636
Fraction Survived: 0.60636
Standard deviation: 0.488557
Standard error: 1.98373e-05
95% confidence interval: [0.316519, 0.316597]
Polyethylene
Entered: 367786000
Survived: 0.860713
Fraction Survived: 0.860713
Standard deviation: 0.346245
Standard error: 1.80545e-05
95% confidence interval: [0.316523, 0.316594]
Theoretical fraction (first material only): 0.606536
Simulation runtime: 10214.3seconds

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

- Add multi-material attenuation comparision
- Include optional plotting and simulated vs theoretical results
- include parallelization, show scaling from 2, 4 and 8 cores 
