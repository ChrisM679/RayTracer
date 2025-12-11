# RayTracer

RayTracer is a C++20-based project designed to simulate realistic rendering of 3D scenes using ray tracing techniques. This project is built with modular components for handling materials, colors, planes, and scenes, making it a flexible and extensible framework for rendering.

## Features

- **Ray Tracing**: Simulates realistic lighting and shadows by tracing the path of light rays.
- **Scene Management**: Supports the creation and manipulation of 3D scenes.
- **Material System**: Allows for defining and applying materials to objects.
- **Color Handling**: Provides utilities for managing and manipulating colors.
- **Extensible Design**: Modular structure for easy addition of new features.

## Prerequisites

- **C++ Compiler**: Requires a compiler with C++20 support.
- **SDL3**: Utilizes SDL3 for handling I/O streams and storage.
- **Microsoft Visual Studio 2022**: Recommended for development and debugging.

## Installation

1. Clone the repository:

2. Open the project in Visual Studio 2022:
- Open `RayTracer.sln` or `RayTracer.vcxproj`.

3. Build the project:
- Use the __Build > Build Solution__ option in Visual Studio.

4. Run the application:
- Use the __Debug > Start Without Debugging__ option.

## Usage

1. Define your scene:
- Modify `Source\Scene.cpp` to add objects, materials, and lighting to your scene.

2. Customize materials:
- Use `Source\Material.h` and `Source\Material.cpp` to define new materials.

3. Run the ray tracer:
- Execute the application to render the scene.

## Project Structure

- `Source\Main.cpp`: Entry point of the application.
- `Source\Scene.cpp`: Handles scene creation and management.
- `Source\Material.*`: Defines materials and their properties.
- `Source\Plane.*`: Represents planes in the scene.
- `Source\Color.h`: Utilities for color manipulation.
- `ThirdParty\SDL3`: Includes SDL3 for I/O and storage handling.

## Contributing

Contributions are welcome! Feel free to fork the repository, create a new branch, and submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgments

- **SDL3**: For providing robust I/O and storage handling.
- **Microsoft Visual Studio**: For the development environment.
- **C++20**: For modern language features that enhance the project.

---
Happy ray tracing!