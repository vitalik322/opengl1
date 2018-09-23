#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

if [ "$1" = "all" ]; then
    echo "From scratch"
    rm -rf "$SCRIPT_DIR/build"
    mkdir "$SCRIPT_DIR/build"
fi
pushd "$SCRIPT_DIR/build"
cmake ..
make -j4
popd
