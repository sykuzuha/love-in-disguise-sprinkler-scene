#!/usr/bin/env bash
set -euo pipefail

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$project_dir"

if ! command -v c++ >/dev/null 2>&1; then
    echo "Error: a C++17 compiler (c++) is required." >&2
    exit 1
fi
if ! command -v ffmpeg >/dev/null 2>&1; then
    echo "Error: ffmpeg is required to save the video." >&2
    exit 1
fi

mkdir -p build results
c++ -std=c++17 -O2 src/main.cpp -o build/sprinkler_scene
# Stream RGB frames directly to FFmpeg so no display or temporary frames are needed.
./build/sprinkler_scene | ffmpeg -hide_banner -loglevel error -y \
    -f rawvideo -pixel_format rgb24 -video_size 960x540 -framerate 30 -i pipe:0 \
    -c:v libx264 -pix_fmt yuv420p -movflags +faststart results/sprinkler_scene.mp4

echo "Saved video to results/sprinkler_scene.mp4"
