# Filter
Script for filtering images in C, featuring basic filters - grayscale, blur, reflect, edge detection

Filter executable file is already compiled, but it is required to give it permission to execute: $ chmod +x filter

# Usage

Usage:
./filter -[flag] infile outfile

For example to blur (-b) an image:
./filter -b images/courtyard.bmp images/out.bmp 

# Flags

-Blur: -b

-Grayscale: -g

-Reflect: -r

-Edges detection: -e
