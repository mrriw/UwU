#!/bin/bash

# thanks to chatGPT for writing this file (except for this line i wrote this line :3)

# Stop on errors, but print diagnostics first
set -Eeuo pipefail

# DXC configuration
DXC="../../../tuls/UuU/DXC/bin/dxc"
export LD_LIBRARY_PATH="../../../tuls/UuU/DXC/lib:${LD_LIBRARY_PATH:-}"

ENTRY="main"
SHADER="${1:-}"
TYPE="${2:-}"

# Error handler
trap 'echo ""; echo "[ERROR] Command failed at line $LINENO"; echo "[ERROR] Exit code: $?"; exit 1' ERR

echo "================================"
echo "       SHADER COMPILER"
echo "================================"

# Check arguments
if [[ -z "$SHADER" || -z "$TYPE" ]]; then
    echo "[ERROR] Missing arguments."
    echo "Usage: ./cnvrt.sh <shader.hlsl> <vs|ps|cs>"
    exit 1
fi

# Check shader
if [[ ! -f "$SHADER" ]]; then
    echo "[ERROR] Shader file not found: $SHADER"
    exit 1
fi

# Check shader type
case "$TYPE" in
    vs|ps|cs|gs|hs|ds) ;;
    *)
        echo "[ERROR] Invalid shader type: $TYPE"
        exit 1
        ;;
esac

# Check tools
echo "[CHECK] Checking dependencies..."

for TOOL in "$DXC" spirv-cross spirv-val; do
    if [[ "$TOOL" == "$DXC" ]]; then
        if [[ ! -x "$TOOL" ]]; then
            echo "[ERROR] DXC not found or not executable: $TOOL"
            exit 1
        fi
    elif ! command -v "$TOOL" >/dev/null 2>&1; then
        echo "[ERROR] Missing dependency: $TOOL"
        exit 1
    fi
    echo "[OK] $TOOL"
done

NAME="${SHADER%.*}"

echo ""
echo "[INFO] Shader: $SHADER"
echo "[INFO] Type: $TYPE"
echo "[INFO] Entry point: $ENTRY"
echo ""

# DXIL
echo "[1/4] Compiling DXIL..."

"$DXC" -T "${TYPE}_6_0" -E "$ENTRY" \
    "$SHADER" -Fo "${NAME}.dxil"

echo "[OK] Generated ${NAME}.dxil"

# SPIR-V
echo ""
echo "[2/4] Compiling SPIR-V..."

"$DXC" -spirv \
    -fspv-target-env=vulkan1.2 \
    -T "${TYPE}_6_0" \
    -E "$ENTRY" \
    "$SHADER" \
    -Fo "${NAME}.spv"

echo "[OK] Generated ${NAME}.spv"

# Validation
echo ""
echo "[3/4] Validating SPIR-V..."

spirv-val --target-env vulkan1.2 "${NAME}.spv"

echo "[OK] SPIR-V is valid"

# MSL
echo ""
echo "[4/4] Converting to MSL..."

spirv-cross "${NAME}.spv" \
    --msl \
    --output "${NAME}.msl"

echo "[OK] Generated ${NAME}.msl"

# Finished
echo ""
echo "================================"
echo "       COMPILATION SUCCESS"
echo "================================"
echo "DXIL: ${NAME}.dxil"
echo "SPIR-V: ${NAME}.spv"
echo "MSL: ${NAME}.msl"
echo "================================"