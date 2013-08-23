CXX = g++
# Configure your dependency paths appropriately
SDL_LIB = -LC:\SDL2-2.0.0-mingw\i686-w64-mingw32\lib	-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE = -IC:\SDL2-2.0.0-mingw\i686-w64-mingw32\include
# For copying the dll to our output folder
SDL_BIN = C:\SDL2-2.0.0-mingw\i686-w64-mingw32\bin
# If your compiler is a bit old you may need to use -std=c++0x instead of -std=c++11
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
# The -mwindows flag will build as a windows application, ie. no console
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
# The source code and build output directories
SRC = src
BUILD = build
# Generate listing of all our source files and object  files
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJS = $(addprefix $(BUILD)/, $(notdir $(SOURCES:.cpp=.o)))
# Executable will be put in the top level of the repo under out/
OUT = ..\out
EXE = $(OUT)\Lesson7.exe

all: $(EXE) | copy_dlls

$(EXE): $(OBJS) | $(OUT)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

# Make sure the build directory exists
$(BUILD):
	mkdir $(BUILD)

# Automate copying of the SDL dlls into our ouput folder
.PHONY: copy_dlls
copy_dlls:
	copy $(SDL_BIN)\*.dll $(OUT)

# Make sure the exe output directory exists
$(OUT):
	mkdir $(OUT)

# Note that it's $(OUT)\*.o here to avoid some weird windows issue
.PHONY: clean
clean:
	del $(BUILD)\*.o && del $(EXE)
