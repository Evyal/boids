# Boids

## Overview

This project simulates the behavior of flocks in a bidimentional space. The simulation models individual agents, called *boids*, that follow rules to create complex, collective behavior.

## Prerequisites

Build instructions are for **Ubuntu 22.04**.

Ensure you have the following installed:

- [SFML](https://github.com/SFML/SFML) (2.5): Library for graphic representation.
- [TGUI](https://github.com/texus/TGUI) (1.0): Library for graphic interface.

### SFML and TGUI Installation

```bash
sudo apt-get install libsfml-dev
```

```bash
sudo add-apt-repository ppa:texus/tgui
sudo apt update
sudo apt install libtgui-1.0-dev
```

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
- Real-time statistics display for each flock
- Interactive controls for adding or removing flocks
- Adjustable parameters for interactions between boids

![Interface](images/interface.png)

![Option1](images/option1.png)
![Option2](images/option2.png)
![Option3](images/option3.png)

### Option 1: Graphics and statistics

- **Background color button**: Changes the colour of the backgorund between black and white.
- **Red numbered buttons**: Delete the corresponding flock.

### Option 2: Create Flocks

- **Number of boids slider**: Selects the number of boids for a new flock.
- **Center of spawn sliders**: Select the spawn location of a new flock.
- **RGB sliders**: Select the color of a new flock. (Creating a white or black flock is disallowed because it would be invisible)
- **Create flock button**: Creates a new flock if there is enough space. (Max 250 boids; Max 5 flocks)

### Option 3: Simulation Parameters

- **Interaction parameters sliders**: Change the values of the parameters of the rules that determine the movement of *boids*.
- **Border mode button**: Changes the behaviour of *boids* at the borders, mirror and toroidal mode.
- **Click mode button**: Changes the interaction on click, attractive and repulsive mode.

### Key Controls

- **Left Click**: Interact with boids, attracting or repelling them to cursor.
- **Space Bar**: Pause/Resume simulation.
