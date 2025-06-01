# Boids

## Overview

This project simulates the behavior of flocks in a bidimentional space. The simulation models individual agents, called *boids*, that follow rules to create complex, collective behavior.

## Prerequisites

Build instructions are for **Ubuntu 24.04**.

Ensure you have the following installed:

- [SFML](https://github.com/SFML/SFML) (2.5): Library for graphic representation.
- [TGUI](https://github.com/texus/TGUI) (1.0): Library for graphic interface.

### SFML and TGUI Installation

```bash
sudo apt install libsfml-dev
```

```bash
sudo add-apt-repository ppa:texus/tgui
sudo apt update
sudo apt install libtgui-1.0-dev
```

### Cloning the Repository

```bash
git clone --depth=1 https://github.com/Evyal/boids.git
cd boids
```

### Build the Project

1. Create a build directory:

```bash
mkdir build
```

2. Configure CMake with Ninja Multi-Config:

```bash
cmake -S . -B build -G "Ninja Multi-Config"
```

3. Build the project:

Debug Mode:
```bash
cmake --build build --config Debug
```

Release Mode:
```bash
cmake --build build --config Release
```

### Running the program

Debug Mode:
```bash
cd build/Debug
./boids
```

Release Mode:
```bash
cd build/Release
./boids
```

### Running the tests

Assuming you are in the program's build directory, enter the testing directory:

```bash
cd testing/Release
```

```bash
./testboid
./testflock
./testrandom
./teststatistics
```

Or eventually, it is possible to check if the tests are successful all at once, from the project's main directory, using:

```bash
cmake --build build --config Debug --target test
cmake --build build --config Release --target test
```

## Interface

### Features

- Random generation of flocks at the beginning of the simulation 
- Different modes for behaviour at borders
- Statistics display for each active flock
- Interactive controls for adding or removing flocks
- Adjustable parameters for interactions between *boids*

<p align="center">
<img src="images/interface.png" alt="Interface">
</p>

<p align="center">
<img src="images/option1.png" alt="Option1">
<img src="images/option2.png" alt="Option2">
<img src="images/option3.png" alt="Option3">
</p>

### Option 1: Graphics and statistics

- **Background color button**: Changes the colour of the backgorund between black and white.
- **Red numbered buttons**: Delete the corresponding flock.

### Option 2: Create Flocks

- **Number of boids slider**: Selects the number of *boids* for a new flock.
- **Center of spawn sliders**: Select the spawn location of a new flock.
- **RGB sliders**: Select the color of a new flock. (Creating a white or black flock is disallowed because it would be invisible)
- **Create flock button**: Creates a new flock if there is enough space. (Max 250 *boids*; Max 5 flocks)

### Option 3: Simulation Parameters

- **Interaction parameters sliders**: Change the values of the parameters of the rules that determine the movement of *boids*.
- **Border mode button**: Changes the behaviour of *boids* at the borders, mirror and toroidal mode.
- **Click mode button**: Changes the interaction on click, attractive and repulsive mode.

### Key Controls

- **Left Click**: Interact with *boids*, attracting or repelling them to cursor.
- **Space Bar**: Pause/Resume simulation.
