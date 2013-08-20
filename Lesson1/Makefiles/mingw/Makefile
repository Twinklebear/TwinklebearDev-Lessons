CXX = g++
# Configure your dependency paths appropriately
SDLLIB = -LC:\SDL2-2.0.0-mingw\i686-w64-mingw32\lib -lSDL2main -lSDL2
SDLINCLUDE = -IC:\SDL2-2.0.0-mingw\i686-w64-mingw32\include
# For copying the dll to our output folder
SDLBIN = C:\SDL2-2.0.0-mingw\i686-w64-mingw32\bin
# If your compiler is a bit old you may need to use -std=c++0x instead of -std=c++11
CFLAGS = -Wall -c -std=c++11 $(SDLINCLUDE)
# The -mwindows flag will build as a windows application, ie. no console
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDLLIB)
# The source code and build output directories
SRC = src
BUILD = build
# Executable will be put in the top level of the repo under out/
OUT = ..\out
EXE = $(OUT)\Lesson1.exe

all: $(EXE) | copy_dlls

$(EXE): $(BUILD)\main.o | $(OUT)
	$(CXX) $< $(LDFLAGS) -o $@

$(BUILD)\main.o: $(SRC)\main.cpp | $(BUILD)
	$(CXX) $(CFLAGS) $< -o $@

# Make sure the build directory exists
$(BUILD):
	mkdir $(BUILD)

# Automate copying of the SDL dlls into our ouput folder
.PHONY: copy_dlls
copy_dlls:
	copy $(SDLBIN)\*.dll $(OUT)

# Make sure the exe output directory exists
$(OUT):
	mkdir $(OUT)

# Note that it's $(OUT)\*.o here to avoid some weird windows issue
.PHONY: clean
clean:
	del $(BUILD)\*.o && del $(EXE)
