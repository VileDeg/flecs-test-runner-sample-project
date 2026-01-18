# Flecs Test Runner Sample

This is a sample project using the **Flecs Test Runner (FTR)**.

It serves for demonstrational purposes of how a real project would use the **FTR**.

A real project would **include the FTR header(s)**, **register** the **testable modules** and be compiled to create a test executable that is supposed to connect to the **FTR web client**. (TODO maybe FTR will define the main function that will open the port?)

TODO

## Supported languages 

- C++ (at least C++17).
- TODO

## Build (C++)

`CMake` must be installed in order to build.

```ps
build.ps1 (-clean) (ModulesDir) (TestRunnerDir)
```

When using `build.ps1` to build, the script will **look for dependency folders locally**.

Otherwise when cmake is called directly, it will **fetch the content** from remote Git repositories, using `FetchContent`. 

```ps
cmake -S . -B build/
```

## Run

Run the executable.

The program will open a port `27750` for connection. This is the default port using by Flecs Rest API. See the documentation: 

https://www.flecs.dev/flecs/md_docs_2FlecsRemoteApi.html
