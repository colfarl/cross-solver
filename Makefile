# ===== Project =====
APP        := cross-solver
SRC_DIR    := .
INC_DIR    := include
BUILD_DIR  := build
BIN        := $(APP)

# Sources / Objects
SRCS := \
  main.cpp \
  Cube.cpp \
  CubeManipulator.cpp \
  SolvingLogic.cpp

OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:.cpp=.o))
DEPS := $(OBJS:.o=.d)

# ===== Toolchain / Flags =====
CXX      ?= g++
MODE     ?= release

# C++17 is needed for inline constexpr variables in the generated table
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Wnull-dereference -Wdouble-promotion -Wformat=2 -MMD -MP
CPPFLAGS := -I$(INC_DIR)
LDFLAGS  :=

ifeq ($(MODE),debug)
  CXXFLAGS += -O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
  LDFLAGS  += -fsanitize=address,undefined
else
  CXXFLAGS += -O3 -DNDEBUG
endif

# ===== Targets =====
.PHONY: all release debug clean run

all: release

release: $(BIN)

debug: MODE := debug
debug: $(BIN)

$(BIN): $(OBJS)
	@echo "  LINK   $@"
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile .cpp -> build/*.o with depfiles
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "  CXX    $<"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Convenience: build then run (prompts for scramble)
run: $(BIN)
	@./$(BIN)

clean:
	@rm -rf $(BUILD_DIR) $(BIN)

# Include auto-generated depfiles
-include $(DEPS)

