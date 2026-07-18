# ============================================================
# Makefile - Bus Escape: Traffic Jam
# Estructura:
#   include/  -> headers (.h)
#   src/      -> implementaciones (.cpp)
#   levels/   -> archivos de nivel (.txt)
#   tests/    -> tests con GoogleTest
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O0 -Iinclude
LDFLAGS  =

# Directorios
SRC_DIR   = src
BUILD_DIR = build
TEST_DIR  = tests

# Ejecutables
TARGET     = main
TEST_BIN   = test_runner

# Fuentes del juego (excluye tests)
SRCS  = $(wildcard $(SRC_DIR)/*.cpp)
OBJS  = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Objetos del juego SIN main.o (para tests)
MAIN_OBJ   = $(BUILD_DIR)/main.o
GAME_OBJS  = $(filter-out $(MAIN_OBJ),$(OBJS))

# Fuentes de tests (GoogleTest)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/test_%.o,$(TEST_SRCS))

# GoogleTest flags (requiere libgtest-dev instalada)
GTEST_LIBS = -lgtest -lgtest_main -pthread

# ============================================================
# Reglas principales
# ============================================================

.PHONY: all run debug gdbserver clean google-test dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR)

# Linkeo del ejecutable principal (juego)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilación de objetos del juego
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Ejecución / Debug
# ============================================================

run: all
	./$(TARGET)

debug: all
	gdb ./$(TARGET)

gdbserver: all
	@echo "Iniciando gdbserver en puerto :2345"
	gdbserver :2345 ./$(TARGET)

# ============================================================
# Tests unitarios con GoogleTest
# ============================================================

google-test: dirs $(TEST_BIN)
	./$(TEST_BIN)

# test_runner usa GAME_OBJS (sin main.o) + TEST_OBJS
$(TEST_BIN): $(GAME_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS) $(LDFLAGS)

# Compilación de objetos de tests
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Limpieza
# ============================================================

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_BIN)