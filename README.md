Monte Carlo Radiation Transport Simulator

A high-performance C++ Monte Carlo radiation transport simulator that models particle attenuation through multiple shielding materials.
This project demonstrates systems-level C++ design, probabilistic modeling, and statistical analysis applied to a physically meaningful problem.

Overview

This simulator estimates particle transmission and absorption through one or more shielding materials using a stochastic (Monte Carlo) approach.

Each particle is tracked individually as it propagates through a stack of materials. Absorption is modeled probabilistically, allowing the simulation to approximate the exponential attenuation law:

𝐼
(
𝑥
)
=
𝐼
0
𝑒
−
𝜇
𝑥
I(x)=I
0
	​

e
−μx

where:

𝐼
(
𝑥
)
I(x) — particle intensity after traveling distance 
𝑥
x

𝐼
0
I
0
	​

 — initial particle intensity

𝜇
μ — macroscopic absorption coefficient

The simulator also computes statistical uncertainty (standard deviation, standard error, confidence intervals), allowing results to be interpreted rigorously.

Key Features

Modular C++ design with clear separation of responsibilities

Monte Carlo particle transport through multiple materials

Physically accurate particle termination (absorption is irreversible)

Per-material statistics tracking (entered vs survived particles)

Binomial uncertainty estimation and confidence intervals

Runtime measurement using std::chrono

Scales to hundreds of millions to billions of particles

Simulation Model
Particle Transport

Particles move in discrete spatial steps.

At each step, a Bernoulli trial determines absorption.

Once absorbed, a particle is permanently removed from the simulation.

Only particles that survive one material are allowed to enter the next.

Multi-Material Propagation

Each particle is simulated sequentially through all materials:

The particle enters the first material.

It advances step-by-step through the material thickness.

If absorbed, the particle is terminated immediately.

If it survives the entire material, it proceeds to the next layer.

A particle survives the simulation only if it passes through all materials.

This ensures that downstream materials receive only physically surviving particles, correctly modeling cumulative attenuation.

Per-Material Statistics

Each material records:

Entered — number of particles that reached the material

Survived — number of particles that fully traversed the material

From these values, the following are computed:

Survival fraction:

𝑝
=
survived
entered
p=
entered
survived
	​


Standard deviation (binomial):

𝜎
=
𝑝
(
1
−
𝑝
)
σ=
p(1−p)
	​


Standard error:

𝜎
𝑁
N
	​

σ
	​


95% confidence interval:

𝑝
±
1.96
×
standard error
p±1.96×standard error

Materials later in the stack naturally exhibit larger uncertainty due to reduced particle counts, which is statistically and physically expected.

Interactive Simulation

The simulator runs interactively and prompts the user for:

Number of particles to simulate

Step size (cm)

Number of materials

For each material:

Name

Thickness (cm)

Absorption probability per step (0–1)

This enables realistic shielding configurations such as layered lead, concrete, and polymer systems.

Example Output
High-Statistics Run (1,000,000,000 particles)
Particles simulated: 1000000000
Particles survived: 316558334
Fraction survived: 0.316558
Standard deviation: 0.465133
Standard error: 1.47088e-05
95% confidence interval: [0.31653, 0.316587]

Per-Material Statistics
Lead
Entered: 1000000000
Fraction Survived: 0.606547
Standard error: 1.54482e-05

Concrete
Entered: 606546925
Fraction Survived: 0.60636
Standard error: 1.98373e-05

Polyethylene
Entered: 367786000
Fraction Survived: 0.860713
Standard error: 1.80545e-05


Although Lead and Concrete exhibit similar survival fractions, Concrete has higher statistical uncertainty due to fewer particles entering the layer.

Monte Carlo Convergence

As the number of simulated particles increases, the Monte Carlo estimate converges toward the analytical solution predicted by exponential attenuation theory.

This behavior is demonstrated through:

Shrinking confidence intervals

Stable survival fractions

Correct propagation of uncertainty through multiple materials

File Structure
/Header Files
  Particle.h
  Material.h
  Simulator.h

/Source Files
  Simulator.cpp
  MonteCarloRadiationTransport.cpp

README.md
MonteCarloRadiationTransport.sln
.gitignore

Technologies Used

C++17

Visual Studio 2022 (MSVC)

Git / GitHub

Standard Library random number generation and timing utilities

Future Improvements

Analytical multi-material attenuation comparison

Optional data export and plotting

Parallelization (OpenMP / std::thread) with scaling benchmarks

Energy-dependent cross sections

Variance reduction techniques

Why This Project Matters

This project demonstrates:

Careful modeling of stochastic physical processes

Correct statistical reasoning under uncertainty

Performance-aware C++ programming

Engineering-level interpretation of simulation results

It is representative of real-world Monte Carlo methods used in radiation transport, shielding design, and nuclear engineering.