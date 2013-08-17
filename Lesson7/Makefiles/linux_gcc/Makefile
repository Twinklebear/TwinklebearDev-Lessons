CXX = g++
# Set the SDLLIB and SDLINCLUDE paths to your install location of SDL
SDLLIB = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
SDLINCLUDE = -I/usr/local/include
# If your compiler is a bit old you may need to use -std=c++0x instead of -std=c++11
CFLAGS = -Wall -c -std=c++0x $(SDLINCLUDE)
LDFLAGS = $(SDLLIB)
# The source code and build output directories
SRC = src
BUILD = build
# Generate listing of all our source and object files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJS = $(addprefix $(BUILD)/, $(notdir $(SOURCES:.cpp=.o)))
# Executables will be written to top level of repo under out/
OUT = ../out
EXE = $(OUT)/Lesson6

all: $(EXE)

$(EXE): $(OBJS) | $(OUT)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CFLAGS) $< -o $@

# Make sure the build directory exists
$(BUILD):
	mkdir -p $(BUILD)

# Make sure the output directory exists
$(OUT):
	mkdir -p $(OUT)

clean:
	rm $(BUILD)/*.o && rm $(EXE)

