RELEASE ?= 0

VLC_DIR := ./deps/vlc/build/vlc_install_dir

CC      := clang
CFLAGS  := -std=c11 -F./Syphon-Framework/build/Release -I$(VLC_DIR)/include
LDLIBS  :=  -Wl,-rpath -Wl,@executable_path/../lib \
            -lGLEW -lglfw3 \
           -framework Foundation -framework Cocoa \
           -framework OpenGL -framework IOKit -framework CoreVideo \
           -F./Syphon-Framework/build/Release -framework Syphon \
           -L$(VLC_DIR)/lib -lvlc

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
build: $(PROGRAM) build/Frameworks/Syphon.framework vlc_libs

$(PROGRAM): $(OBJECTS)
	mkdir -p build/bin
	cp -r resources build/resources
	$(CC) $(LDLIBS) -o $@ $^

build/Frameworks/Syphon.framework: Syphon-Framework/build/Release/Syphon.framework
	mkdir -p build/Frameworks
	cp -r Syphon-Framework/build/Release/Syphon.framework build/Frameworks

.PHONY:vlc_libs
vlc_libs:
	mkdir -p ./build/lib
	cp -r $(VLC_DIR)/lib/* ./build/lib

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.m
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@
