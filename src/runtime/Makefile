# ==============================================================================
# maVIS Virtual Machine Smart Build System (Isolated Object Directories)
# ==============================================================================

# Automatically detect available CPU cores across Linux/macOS
NPROCS   := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)
MAKEFLAGS += -j$(NPROCS)

CXX      := clang++
CXXFLAGS := -std=c++23 -Wall -Wextra -Werror -MMD -MP
LDLIBS   := -lSDL3
TARGET   := maVM.out

# 1. Directory Isolation Setup
OBJ_DIR  := obj

# 2. Automated File Discovery (Recursive)
SRCS     := $(shell find . -name '*.cpp' -type f)
OBJS     := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Create necessary subdirectories in obj/
OBJ_SUBDIRS := $(sort $(dir $(OBJS)))

# ==============================================================================
# Build Rules
# ==============================================================================

all: $(TARGET)

# Linking Phase (LDLIBS comes after $(OBJS))
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

# Compilation Phase (Uses only CXXFLAGS)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create all obj subdirectories at once (order-only prerequisite)
$(OBJS): | $(OBJ_SUBDIRS)

$(OBJ_SUBDIRS):
	mkdir -p $@

test: $(TARGET)
	./$(TARGET) ../test/basicNOP.mabin

# Clean Phase
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all test clean

# Include generated dependency files
-include $(OBJS:.o=.d)