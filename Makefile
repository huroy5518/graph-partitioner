
CC := g++
SRC_DIR = src
BUILD_DIR = build
BIND_DIR = bind

PYBIND11_INCLUDE := $(shell python3 -m pybind11 --include)
PYTHON_LDFLAGS := $(shell python3-config --includes --ldflags)

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
BIND_FILES := $(wildcard $(BIND_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

CPPFLAGS := -Wall -Wextra -std=c++17 -fPIC -O3 -shared -Iinclude
TARGET = GraphPartitioner.so

.PHONY: test all clean

all: $(TARGET)

clean:
	rm -f GraphPartitioner.so
	rm -r build/

test:
	python3 -m pytest -v test/ -r A

$(TARGET): $(OBJ_FILES) $(BIND_FILES)
	echo $(SRC_FILES)
	$(CC) $(CPPFLAGS) $(PYBIND11_INCLUDE) $^ $(PYTHON_LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(PYBIND11_INCLUDE) -c $< -o $@
