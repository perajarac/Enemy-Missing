#!/bin/bash

# Build the project
make clean
make

# List of assembly files to process
assembly_files=(
    "test/nivo-a/handler.s"
    "test/nivo-a/isr_terminal.s"
    "test/nivo-a/isr_timer.s"
    "test/nivo-a/isr_software.s"
    "test/nivo-a/main.s"
    "test/nivo-a/math.s"
)

# Loop through each assembly file and process it
for file in "${assembly_files[@]}"; do
    # Extract the base name of the file (without extension)
    base_name=$(basename "$file" .s)

    # Run the assembler command
    ./asembler -o "${base_name}.o" "$file"
done

./linker -hex \
  -place=my_code@0x40000000 -place=math@0xF0000000 \
  -o program.hex \
  handler.o math.o main.o isr_terminal.o isr_timer.o isr_software.o


./emulator program.hex