#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <block_number>"
    exit 1
fi

START_LINE=$(( ($1 * 3) - 2 ))
END_LINE=$(( $1 * 3 ))

sed -n "${START_LINE},${END_LINE}p" tastatura.txt | ./build/oop