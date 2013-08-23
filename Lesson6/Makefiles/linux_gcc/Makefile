CXX = g++
# Set the SDL_LIB and SDL_INCLUDE paths to your install location of SDL
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
# If your compiler is a bit old you may need to use -std=c++0x instead of -std=c++11
CXXFLAGS = -Wall -c -std=c++0x $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
# The source code and build output directories
SRC = src
BUILD = build
# Executables will be written to top level of repo under out/
OUT = ../out
EXE = $(OUT)/Lesson6

all: $(EXE)

$(EXE): $(BUILD)/main.o | $(OUT)
	$(CXX) $< $(LDFLAGS) -o $@

$(BUILD)/main.o: $(SRC)/main.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

# Make sure the output directory exists
$(OUT):
	mkdir -p $(OUT)

clean:
	rm $(BUILD)/*.o && rm $(EXE)

