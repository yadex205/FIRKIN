CC      = clang
CFLAGS  = -g -Wall
LDLIBS  = -lGLEW -lglfw3 -framework Foundation -framework Cocoa \
          -framework OpenGL -framework IOKit -framework CoreVideo

DISTDIR = ./build
OBJDIR  = $(DISTDIR)/object
SRCDIR  = ./src

PROGRAM = build/firkin
SOURCES = $(wildcard ./src/*.m)
OBJECTS = $(patsubst ./src/%.m,./build/object/%.o,$(SOURCES))

.PHONY: all
all: $(PROGRAM)

.PHONY: run
run: $(PROGRAM)
	$(PROGRAM)

.PHONY: debug
debug: $(PROGRAM)
	lldb $(PROGRAM)

.PHONY: clean
clean:
	rm -rf build/*

$(PROGRAM): $(OBJECTS)
	mkdir -p build
	cp -r resources build/resources
	$(CC) $(LDLIBS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.m
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@
