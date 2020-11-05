PROJECT  := bird

CXX      := clang++
CXXFLAGS := -Wall -std=c++17
LDFLAGS  := -L/usr/local/Cellar/glfw/3.3/lib -lglfw -L/usr/local/Cellar/glew/2.1.0_1/lib -lglew -L/System/Library/Frameworks/OpenGL.framework/Libraries -lGL
INCLUDE  :=

TMP_DIR  := ./temp
SRC_DIR  := ./src
BIN_DIR  := $(TMP_DIR)/bin
OBJ_DIR  := $(TMP_DIR)/obj

SRC      :=     \
	camera.cpp  \
	GLutil.cpp  \
	main.cpp    \
	mesh.cpp    \
	model.cpp   \
	shader.cpp  \
	texture.cpp \
	vao.cpp     \
	window.cpp  ;

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

test:
	@echo $(OBJECTS)

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
