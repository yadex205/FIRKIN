RELEASE ?= 0

CC      := clang
CFLAGS  := -std=c11 -F./Syphon-Framework/build/Release -I./deps/vlc/include
LDLIBS  :=  -Wl,-rpath -Wl,@executable_path/../lib \
            -lGLEW -lglfw3 -lavcodec -lavformat -lswresample -lswscale -lavutil \
           -framework Foundation -framework Cocoa \
           -framework OpenGL -framework IOKit -framework CoreVideo \
           -F./Syphon-Framework/build/Release -framework Syphon \
           -L./deps/vlc/lib -lvlc

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
VENDORS := build/Frameworks/Syphon.framework \
           build/lib/libvlc.dylib \
           build/lib/libvlccore.dylib \
           build/lib/vlc

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
build: $(PROGRAM) $(VENDORS)

$(PROGRAM): $(OBJECTS)
	mkdir -p build/bin
	cp -r resources build/resources
	$(CC) $(LDLIBS) -o $@ $^

build/Frameworks/Syphon.framework: Syphon-Framework/build/Release/Syphon.framework
	mkdir -p build/Frameworks
	cp -r Syphon-Framework/build/Release/Syphon.framework build/Frameworks

build/lib/libvlc%: deps/vlc/lib/libvlc%
	mkdir -p build/lib
	cp $^ $@

build/lib/vlc: deps/vlc/lib/vlc
	cp -r $^ $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.m
	mkdir -p build/object
	$(CC) $(CFLAGS) -c $^ -o $@

Syphon-Framework/build/Release/Syphon.framework:
	cd Syphon-Framework; git checkout core-profile
	cd Syphon-Framework; xcodebuild -project Syphon.xcodeproj -target Syphon
