# Autonomous Drone Surveillance System

This project implements an autonomous drone surveillance system using C++. The system utilizes file handling, SFML for display, and vector for containers. It also employs inheritance for two types of drones: base drone and surveillance drone. Additionally, exception handling is implemented for robust error management.

## Features

- **File Handling**: The system reads input data from files to define the environment and mission parameters.
- **SFML Display**: A graphical interface built with SFML library displays the drone's movement and surveillance data in real-time.
- **Vector Containers**: Standard C++ vectors are used to store data efficiently, such as drone positions, waypoints, and surveillance data.
- **Inheritance**: The system implements inheritance to create two types of drones: base drone and surveillance drone. This allows for code reusability and modularity.
- **Shortest Path Finding**: Algorithms are implemented to calculate the shortest path for surveillance drones to cover the designated area efficiently.
- **Rescue Drone for Fire Extinguishing**: A specialized rescue drone is included in the system to respond to fire incidents and perform fire extinguishing operations.
- **Exception Handling**: Robust exception handling mechanisms are implemented to ensure the system gracefully handles errors and unexpected scenarios.

## Components

1. **Base Drone**: This is the basic drone class from which other specialized drones inherit. It contains essential functionalities such as movement and data collection.

2. **Surveillance Drone**: Inherits from the base drone class and adds functionalities specific to surveillance tasks, such as path planning and data analysis.

3. **Rescue Drone**: Inherits from the base drone class and is specialized for fire extinguishing operations. It includes additional capabilities for carrying and deploying firefighting equipment.

4. **FileHandler**: Manages reading input data from files and initializing the environment and mission parameters.

5. **DisplayManager**: Handles the graphical display using SFML library, showing the drone's movement and surveillance data.

6. **PathFinder**: Implements algorithms for calculating the shortest path for surveillance drones to cover the designated area efficiently.

7. **ExceptionHandler**: Provides robust exception handling mechanisms to ensure the system handles errors gracefully.

## Usage

1. Clone the repository.
2. Compile the code using a C++ compiler with SFML library linked.
3. Run the executable, providing necessary input files for environment setup and mission parameters.

## Dependencies

- C++ compiler with C++17 support
- SFML library


