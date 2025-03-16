# Boids

## Overview

This project simulates the behavior of flocks, such as birds or fish, using a particle-based system. The simulation models individual agents that follow simple rules to create complex, collective behavior.

### Prerequisites

Ensure you have the following installed:
- C++ compiler
- CMake
- [SFML](https://github.com/SFML/SFML) (2.5): Libreria per la rappresentazione grafica
- [TGUI](https://github.com/texus/TGUI) (1.0): Libreria per l'interfaccia grafica
- [doctest](https://github.com/doctest/doctest): Libreria per il testing

### Clone the Repository

```bash
git clone https://github.com/Evyal/boids.git
cd boids
```

### Build the Project

1. Create a build directory:

```bash
mkdir build
cd build
```

2. Configure CMake in Release mode:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

3. Build the project:

```bash
cmake --build .
```

### Running the program

```bash
./boids
```

## Features

- Real-time visualization of flock movement
- Adjustable parameters for interactions between boids
- Interactive controls for adding or removing flocks

![bottoni_evidenziati](images/interfaccia1.png)
![bottoni_evidenziati](images/interfaccia2.png)
![bottoni_evidenziati](images/interfaccia3.png)

## Controls

- **Left Click**: Interact with boids
- **Space Bar**: Pause/Resume simulation
