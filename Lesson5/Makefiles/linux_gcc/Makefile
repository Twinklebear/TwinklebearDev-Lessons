CXX = g++
# Set the SDLLIB and SDLINCLUDE paths to your install location of SDL
SDLLIB = -L/usr/local/lib -lSDL2 -lSDL2_image
SDLINCLUDE = -I/usr/local/include
# If your compiler is a bit old you may need to use -std=c++0x instead of -std=c++11
CFLAGS = -Wall -c -std=c++0x $(SDLINCLUDE)
LDFLAGS = $(SDLLIB)
# The source code and build output directories
SRC = src
BUILD = build
# Executables will be written to top level of repo under out/
OUT = ../out
EXE = $(OUT)/Lesson5

all: $(EXE)

$(EXE): $(BUILD)/main.o | $(OUT)
	$(CXX) $(LDFLAGS) $< -o $@

$(BUILD)/main.o: $(SRC)/main.cpp | $(BUILD)
	$(CXX) $(CFLAGS) $< -o $@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

# Make sure the output directory exists
$(OUT):
	mkdir -p $(OUT)

clean:
	rm $(BUILD)/*.o && rm $(EXE)

