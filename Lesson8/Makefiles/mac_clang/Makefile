CXX = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
CFLAGS = -Wall -c -std=c++11 -stdlib=libc++
LDFLAGS = -stdlib=libc++ $(SDL)
# The source and build output directories
SRC = src
BUILD = build
# Generate listing of all our source and object files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJS = $(addprefix $(BUILD)/, $(notdir $(SOURCES:.cpp=.o)))
# Executables will be written to the top level of the repo under out/
OUT = ../out
EXE = $(OUT)/Lesson8

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

