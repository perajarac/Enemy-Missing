# Targets
# OBJS = src/assembler.o src/main.o src/flex.o src/parser.o
OBJS_ASS  = src/assembler.o src/parser.o src/flex.o src/mainass.o
OBJS_LINKER = src/linker.o src/linkermain.o

all: asembler linker
# Link executable
asembler: $(OBJS_ASS)
	g++ -o $@ $(OBJS_ASS)

linker: $(OBJS_LINKER)
	g++ -o $@ $(OBJS_LINKER)


src/mainass.o: src/mainass.cpp
	g++ -c -o $@ $<

src/linkermain.o: src/linkermain.cpp
	g++ -c -o $@ $<


# Compile .cpp files to object files
src/assembler.o: src/assembler.cpp inc/assembler.hpp
	g++ -c -o $@ $<

src/linker.o: src/linker.cpp inc/linker.hpp
	g++ -c -o $@ $<

# src/main.o: src/main.cpp inc/parser.hpp
#     g++ -c -o $@ $<

# Generate .cpp files from .l and .y files
src/flex.cpp: misc/flex.l
	flex --outfile=$@ $<

src/parser.cpp: misc/parser.y
	bison -v --defines=inc/parser.hpp --output=$@ $<

# Compile .cpp files from flex and bison to object files
src/flex.o: src/flex.cpp
	g++ -c -o $@ $<

src/parser.o: src/parser.cpp
	g++ -c -Iinc -o $@ $<

# Clean target
clean:
	rm -f asembler linker src/*.o src/flex.cpp src/parser.cpp src/parser.output assout.txt *.o
