#!/bin/bash
if [ $# -eq 0 ]; then
    echo "No arguments supplied"
else
    count=0
    for arg in "$@"; do
        if [ $count -ge 3 ]; then
            break
        fi
        echo "$arg"
        ((count++))
    done
fi

