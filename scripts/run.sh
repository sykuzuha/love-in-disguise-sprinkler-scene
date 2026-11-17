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
./build/sprinkler_scene

# The scene is not implemented yet; create a blank placeholder video.
ffmpeg -hide_banner -loglevel error -y \
    -f lavfi -i 'color=c=0x17283b:s=1280x720:r=30:d=5' \
    -c:v libx264 -pix_fmt yuv420p -movflags +faststart results/sprinkler_scene.mp4

echo "Saved placeholder video to results/sprinkler_scene.mp4"
