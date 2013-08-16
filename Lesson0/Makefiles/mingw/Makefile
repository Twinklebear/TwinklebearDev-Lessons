CXX = g++
# Configure your dependency paths appropriately
SDLLIB = -LC:\SDL2-2.0.0-mingw\i686-w64-mingw32\lib -lSDL2main -lSDL2
SDLINCLUDE = -IC:\SDL2-2.0.0-mingw\i686-w64-mingw32\include
# For copying the dll to our output folder
SDLBIN = C:\SDL2-2.0.0-mingw\i686-w64-mingw32\bin\SDL2.dll
CFLAGS = -Wall -c -std=c++11 $(SDLINCLUDE)
# The -mwindows flag will build as a windows application, ie. no console
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDLLIB)
# The source code and build output directories
SRC = src
OUT = build
EXE = $(OUT)\Lesson0.exe

all: $(EXE) 

$(EXE): $(OUT)/main.o | $(OUT)/SDL2.dll
	$(CXX) $< $(LDFLAGS) -o $@

$(OUT)/main.o: $(SRC)/main.cpp | $(OUT)
	$(CXX) $(CFLAGS) $< -o $@

# Automate copying of the SDL dll to our output folder
$(OUT)/SDL2.dll:
	COPY $(SDLBIN) $(OUT)/SDL2.dll

# Make sure the build directory exists
$(OUT):
	mkdir -p $(OUT)

# Note that it's $(OUT)\*.o here to avoid some weird windows issue
clean:
	del $(OUT)\*.o && del $(EXE)
