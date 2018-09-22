#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

rm -rf "$SCRIPT_DIR/build"
mkdir "$SCRIPT_DIR/build"
pushd "$SCRIPT_DIR/build"
cmake ..
make -j4
popd
