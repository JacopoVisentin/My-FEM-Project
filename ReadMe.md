# Finite Element Analysis Project

## Group 148

- Jacopo Visentin - NOMA: 50112100
- Thomas Leblanc - NOMA: ?

## Project Overview

This project involves the application of finite element analysis (FEA) techniques to solve and analyse a particular 2D linear elasticity problem.

## Project Structure

```bash
/group148-jvisentin-tleblanc/
│
├── build/
│   └── myFem.exe
│
├── data/
│   ├── mesh.txt                    # copy of the clean mesh
│   ├── mesh_fixed.txt              # cleaned connected mesh
│   ├── mesh_raw.txt                # raw unchecked mesh (may not be connected)
│   └── nodal_displacements.txt     # displacement vector output
│
├── src/
│   ├── glfw/                       # Graphical library
│   ├── gmsh/                       # Meshing and CAD library
│   ├── headers/                    # Header files
│   ├── fixmesh.py                  # Mesh cleanup script
│   ├── glfem.c                     # GUI functions
│   ├── fem.c                       # Computational functions
│   └── run.c                       # script that runs the entire project
│
├── README.md
└── CMakeLists.txt
```

- **/data**: Includes input data, data used to communicate between different scripts (pre, postprocessing and solver) as well as results.
- **/src**: Includes all the scripts and libraries as well as the `run.c` to run the entirety of the project.

## How to Run

>**IMPORTANT:** The script relies on the `fixmesh.py` module (located at `src/PreProcessor/src/fixmesh.py`), which in turn depends on the python NumPy library. Make sure to activate a python venv with the required dependencies installed before compiling.

1. Navigate to the `/build` directory
2. Remove any existing content if any
3. Compile and run the program:

    ```bash
    cmake ..
    make
    ./myFem
    ```

This version of the program does not allow for command line arguments. The geometry and problem parameters are fixed. For general code, use `/group148-jvisentin-tleblanc/` (non rapport version).

<!-- set correct repo link -->
[GitHub Repository](https://github.com/JacopoVisentin?tab=repositories)
