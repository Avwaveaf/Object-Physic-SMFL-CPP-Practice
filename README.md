# Physics Simulation Project

![](https://github.com/Avwaveaf/Object-Physic-SMFL-CPP-Practice/blob/master/sfml_physic_demo.gif)

This project is a simple physics simulation implemented using SFML (Simple and Fast Multimedia Library) in C++. The goal of the project is to create a windowed environment and simulate the movement and collision of different shapes, such as rectangles and circles, based on a provided configuration file.

## Project Overview

- **Language:** C++
- **Graphics Library:** SFML
- **Source Files:**
  - `main.cpp`: Contains the main logic for the physics simulation.
  - `config.txt`: Configuration file specifying window dimensions and shapes.

## Features

1. **Polymorphism and Dynamic Memory Allocation:**
   - Utilizes polymorphism to create a base class `PhysicObjectBase` with pure virtual functions for updating and drawing.
   - Implements two derived classes, `PhysicObjectRectangle` and `PhysicObjectCircle`, representing rectangles and circles.

2. **Configuration File Parsing:**
   - Reads configuration data from the `config.txt` file to set up the simulation.
   - Supports specifying window dimensions, rectangle properties, and circle properties.

3. **Dynamic Shape Rendering:**
   - Dynamically renders rectangles and circles based on the configuration file.
   - Utilizes smart pointers for automatic memory management.

4. **Physics Simulation:**
   - Implements simple physics logic, including collision detection and gravitation, for each shape.
   - Handles boundary collisions for both x and y axes.

5. **SFML Graphics:**
   - Uses SFML for creating a window and rendering graphics.
   - Utilizes SFML's `sf::RectangleShape` and `sf::CircleShape` for rendering shapes.

## How to Use

1. **Configuration File (`config.txt`):**
   - Specify window dimensions using the keyword "Window" followed by width and height.
   - Define rectangles using the keyword "Rectangle" followed by a name, initial position (X, Y), and initial speed (sX, sY).
   - Define circles using the keyword "Circle" followed by a name, initial position (X, Y), initial speed (sX, sY), and radius.

2. **Building and Running:**
   - Ensure you have SFML installed on your system.
   - Compile the source code using a C++ compiler (e.g., g++).
   - Run the executable.

3. **Interaction:**
   - The simulation window will display the rendered shapes.
   - The simulation will continue until the window is closed.

## Example Configuration

```plaintext
Window 800 600
Rectangle Rect1 100 100 5 3
Circle Circ1 200 300 7 2 50
```

In this example, the window dimensions are set to 800x600, and a rectangle (`Rect1`) and a circle (`Circ1`) are defined with their respective properties.

Feel free to modify the configuration file to create different scenarios for the physics simulation.

**Note:** Ensure the SFML library is properly linked and available in your build environment. 
all complete description available on description.txt file.
[go to description.txt](https://github.com/Avwaveaf/Object-Physic-SMFL-CPP-Practice/blob/master/SFML_Game/description.text)

## Contributors

- avwaveaf


## License
🤨
