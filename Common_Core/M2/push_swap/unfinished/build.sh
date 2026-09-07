#!/bin/bash
set -e

BUILD_DIR="cmake_build"
PROJECT_NAME="push_swap"

if [ -z "$PROJECT_NAME" ]; then
    echo "Error: PROJECT_NAME is not defined. Set PROJECT_NAME in build.sh."
    exit 1
fi
if [[ ! "$PROJECT_NAME" =~ ^[A-Za-z0-9_.-]+$ ]]; then
    echo "Error: PROJECT_NAME contains invalid characters. Only letters, numbers, underscore, dash, and dot are allowed."
    exit 1
fi

if [ "$1" = "clean" ]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    if [ -n "$PROJECT_NAME" ] && [ -f "$PROJECT_NAME" ]; then
        echo "Removing executable $PROJECT_NAME..."
        rm -f "$PROJECT_NAME"
    fi
    exit 0
fi

mkdir -p "$BUILD_DIR"
cmake -S . -B "$BUILD_DIR" -DPROJECT_NAME="$PROJECT_NAME"
cmake --build "$BUILD_DIR"
# Create CMakePresets.json
cat > CMakePresets.json <<EOF
{
  "version": 3,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 28,
    "patch": 3
  },
  "configurePresets": [
    {
      "name": "default",
      "description": "Auto-generated preset for ${PROJECT_NAME}",
      "generator": "Unix Makefiles",
      "binaryDir": "\${sourceDir}/${BUILD_DIR}",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",
        "PROJECT_NAME": "${PROJECT_NAME}"
      }
    }
  ],
  "buildPresets": [
    {
      "name": "default",
      "description": "Build using the default configure preset",
      "configurePreset": "default",
      "targets": [],
      "jobs": 4
    }
  ]
}
EOF
