PROJECT  := bird

CXX      := clang++
CXXFLAGS := -Wall -std=c++17
LDFLAGS  := -L/usr/local/Cellar/glfw/3.3/lib -lglfw -L/usr/local/Cellar/glew/2.1.0_1/lib -lGLEW -L/System/Library/Frameworks/OpenGL.framework/Versions/Current/Libraries -lGL
INCLUDE  := -I./src

TMP_DIR  := ./temp
SRC_DIR  := ./src
BIN_DIR  := $(TMP_DIR)/bin
OBJ_DIR  := $(TMP_DIR)/obj

SRC      :=               \
	gl_util/camera.cpp    \
	gl_util/globject.cpp  \
	gl_util/mesh.cpp      \
	gl_util/model.cpp     \
	gl_util/shader.cpp    \
	gl_util/vao.cpp       \
	gl_util/texture.cpp   \
	gl_util/window.cpp    \
	game.cpp              \
	main.cpp              ;

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

debug: CXXFLAGS   += -g
debug: build $(BIN_DIR)/$(PROJECT)

release: CXXFLAGS += -O3
release: build $(BIN_DIR)/$(PROJECT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

$(BIN_DIR)/$(PROJECT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$(PROJECT) $(OBJECTS)

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(BIN_DIR)/*
	-@rm -rvf $(OBJ_DIR)/*

run:
	$(BIN_DIR)/$(PROJECT)

.PHONY: all release debug  clean run
