RELEASE ?= 0

CC      := clang
CFLAGS  := -std=c11 -F./Syphon-Framework/build/Release
LDLIBS  := -lGLEW -lglfw3 -lavcodec -lavformat -lswresample -lswscale -lavutil \
           -framework Foundation -framework Cocoa \
           -framework OpenGL -framework IOKit -framework CoreVideo \
           -F./Syphon-Framework/build/Release -framework Syphon \

ifeq ($(RELEASE), 0)
  CFLAGS := -g -Wall $(CFLAGS)
else
  CFLAGS := -O2 $(CFLAGS)
endif


DISTDIR := ./build
OBJDIR  := $(DISTDIR)/object
SRCDIR  := ./src

PROGRAM := build/bin/firkin
SOURCES := $(wildcard ./src/*.c) $(wildcard ./src/*.m)
OBJECTS := $(patsubst ./src/%.c,./build/object/%.o,$(filter ./src/%.c,$(SOURCES))) \
           $(patsubst ./src/%.m,./build/object/%.o,$(filter ./src/%.m, $(SOURCES)))

.PHONY: all
all: build

.PHONY: run
run: build
	$(PROGRAM)

.PHONY: debug
debug: build
	lldb $(PROGRAM)

.PHONY: clean
clean:
	rm -rf build/*

.PHONY: build
build: $(PROGRAM) build/Frameworks/Syphon.framework

$(PROGRAM): $(OBJECTS)
	mkdir -p build/bin
	cp -r resources build/resources
	$(CC) $(LDLIBS) -o $@ $^

build/Frameworks/Syphon.framework:
	mkdir -p build/Frameworks
	cp -r Syphon-Framework/build/Release/Syphon.framework build/Frameworks

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.m
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@
