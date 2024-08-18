make: test

clean:
	rm -f src/flex.cpp src/parser.cpp test

test: src/flex.cpp src/parser.cpp
	g++ -o $(@) $(^)

src/flex.cpp: misc/flex.l
	flex --outfile=$(@) $(^)

src/parser.cpp: misc/parser.y
	bison -v --defines=inc/parser.hpp --output=$(@) $(^)