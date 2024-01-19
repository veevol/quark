SRC_DIR := src
INCLUDE_DIR := include

OBJ_DIR := obj
BIN_DIR := bin

CPP := g++

CPP_FLAGS := -Wall -Wextra -std=c++20 -O3 -c
LD_FLAGS := -llumencpp

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET := $(BIN_DIR)/quark
DEST_BIN_DIR := /usr/bin

all: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CPP) -o $@ $< $(LD_FLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CPP) -o $@ $< $(CPP_FLAGS)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

install: $(TARGET) | $(DEST_BIN_DIR)
	cp $< $(DEST_BIN_DIR)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean install
