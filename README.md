# Sprinkler Scene

Starter project for a C++ particle simulation and visualization using OpenMP and OpenGL.

## Build

Requirements: CMake 3.16 or newer and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
./scripts/run.sh
```

OpenMP and OpenGL integration can be enabled independently when their development libraries are available:

```sh
cmake -S . -B build -DSPRINKLER_ENABLE_OPENMP=ON -DSPRINKLER_ENABLE_OPENGL=ON
cmake --build build
```

On macOS, Apple Clang may require a separate OpenMP installation and a compiler configured to find it. OpenGL windowing and model loading dependencies have not yet been selected.

## Layout

- `src/` and `include/`: application source and headers
- `assets/models/`: character and scene models
- `assets/shaders/`: rendering shaders
- `benchmarks/`: future performance evaluation code
- `results/`: future benchmark output

The current prototype renders one sprinkler with two ballistic streams sweeping uniformly in opposite directions, projected into 2D. OpenGL rendering, 3D characters, OpenMP particle updates, and benchmarks are not implemented yet.

## Run and save a video

With a C++17 compiler and FFmpeg installed, run:

```sh
./scripts/run.sh
```

The script builds and runs the sprinkler prototype and writes a five-second video to `results/sprinkler_scene.mp4`. It streams generated frames directly to FFmpeg and does not require a display. Running the script again replaces the previous video. FFmpeg must include the `libx264` encoder.

## Submit a job on USC Discovery

Copy the project to Discovery, and make sure a C++17 compiler and FFmpeg with `libx264` are available in your environment. Use `module spider gcc` and `module spider ffmpeg` to check available modules, and load the appropriate modules before submission. If FFmpeg is not available as a module, it must be provided separately. The job inherits your environment by default.

From the project directory, submit the job with:

```sh
./scripts/submit.sh
```

To use a specific project account, run `./scripts/submit.sh --account=YOUR_PROJECT_ID`. Additional `sbatch` options can also be passed to the script. The job requests one CPU on the `main` partition, 2 GB of memory, and ten minutes. Once it finishes, the video is saved to `results/sprinkler_scene.mp4`; job output and errors are saved to `results/slurm-JOBID.out`. Check progress with `squeue --me`. Each run replaces the same video, so avoid running multiple jobs at once in the same project directory.

Discovery execution has not been tested from this environment. See [USC's running jobs guide](https://www.carc.usc.edu/user-guides/hpc-systems/using-our-hpc-systems/running-jobs) for accounts and job monitoring.
