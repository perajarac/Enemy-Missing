# Targets
OBJS_ASS  = src/common.o src/assembler.o src/parser.o src/flex.o src/mainass.o 
OBJS_LINKER = src/common.o src/assembler.o src/linker.o src/linkermain.o

all: asembler linker
	@echo "Build complete."

# Link executable
asembler: $(OBJS_ASS)
	@echo "Building assembler..."
	@g++ -o $@ $(OBJS_ASS)

linker: $(OBJS_LINKER)
	@echo "Building linker..."
	@g++ -o $@ $(OBJS_LINKER)

# Compile .cpp files to object files
src/assembler.o: src/assembler.cpp inc/assembler.hpp
	@g++ -c -o $@ $<

src/linker.o: src/linker.cpp inc/linker.hpp
	@g++ -c -o $@ $<

# Generate .cpp files from .l and .y files
src/flex.cpp: misc/flex.l
	@flex --outfile=$@ $<

src/parser.cpp: misc/parser.y
	@bison -v --defines=inc/parser.hpp --output=$@ $<

# Compile .cpp files from flex and bison to object files
src/flex.o: src/flex.cpp
	@g++ -c -o $@ $<

src/parser.o: src/parser.cpp
	@g++ -c -Iinc -o $@ $<

src/common.o: src/common.cpp inc/common.hpp
	@g++ -c -o $@ $<

src/mainass.o: src/mainass.cpp
	@g++ -c -o $@ $<

src/linkermain.o: src/linkermain.cpp
	@g++ -c -o $@ $<

# Clean target
clean:
	@echo "Cleaning up..."
	@rm -f asembler linker src/*.o src/flex.cpp src/parser.cpp src/parser.output assout.txt *.o
