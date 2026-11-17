#!/usr/bin/env bash
set -euo pipefail

project_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if ! command -v sbatch >/dev/null 2>&1; then
    echo "Error: sbatch is required; run this script on a Slurm login node." >&2
    exit 1
fi
mkdir -p "$project_dir/results"
cd "$project_dir"
sbatch --chdir="$project_dir" --output="$project_dir/results/slurm-%j.out" "$@" scripts/discovery.job
