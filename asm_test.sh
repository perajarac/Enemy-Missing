#!/bin/bash

# Build the project
make clean
make

# List of assembly files to process
assembly_files=(
    "test/handler.s"
    "test/isr_terminal.s"
    "test/isr_timer.s"
    "test/isr_software.s"
    "test/main.s"
    "test/math.s"
)

# Loop through each assembly file and process it
for file in "${assembly_files[@]}"; do
    # Extract the base name of the file (without extension)
    base_name=$(basename "$file" .s)

    # Run the assembler command
    ./asembler -o "${base_name}.o" "$file"
done
