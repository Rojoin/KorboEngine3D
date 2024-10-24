# KorboEngine3D

KorboEngine3D is a C++ game engine built on **OpenGL**, designed to support both **3D and 2D assets**. With a strong emphasis on performance, flexibility, and rendering techniques, the engine provides a wide array of features such as model and texture importing, custom shader support, collision systems, and efficient rendering through techniques like **BSP (Binary Space Partitioning)** and **frustum culling**. The engine also includes a **debugger interface** built with **ImGui**, allowing for real-time insights into your scene, assets, and performance.

## Key Features

### 1. **3D and 2D Asset Support**
- Full support for importing and rendering both 3D models and 2D assets.
- Seamless integration of multiple file formats for assets using the engine's built-in model and texture importers.

### 2. **Model and Texture Importer**
- Import models in popular formats like `.obj`, `.fbx`, and more.
- Texture importing for common formats like `.png` and `.jpg`.
- Support for various texture mapping techniques, including normal maps, specular maps, and more.

### 3. **Custom Shader Support**
- Write and integrate your own **GLSL shaders**.
- Real-time shader reloading for fast iterations during development.
- Includes default shader support for basic lighting, texturing, and shadow mapping.

### 4. **Efficient Rendering Techniques**
- **BSP (Binary Space Partitioning)**: Optimize your scene for efficient rendering by organizing assets in a spatial hierarchy.
- **Frustum Culling**: Efficiently determine which objects are visible to the camera and skip unnecessary rendering.

### 5. **Hierarchy System**
- Full hierarchical scene management.
- Parent-child relationships between entities allow for complex scene construction.
- Transformation inheritance ensures that child objects move and rotate relative to their parent.

### 6. **Debugger Interface with ImGui**
- The engine includes an in-built **debugger interface** powered by **ImGui**.
- Inspect and modify game objects, entities, shaders, and scenes in real-time.
- Access debug views for assets, frustum culling, BSP trees, and more.

## Getting Started

### Prerequisites

Before you can use KorboEngine3D, you will need:

- **C++17** or higher
- **OpenGL 4.0** or higher


### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/YourUsername/KorboEngine3D.git
   cd KorboEngine3D
```
