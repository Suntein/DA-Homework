CXX = g++                     # 定义编译器
CXXFLAGS = -std=c++20 -MMD -MP # 编译器选项，包括C++标准和依赖生成
TARGET = SingleLinkedList      # 输出目标
SRC = SingleLinkedList.cpp     # 源文件列表
OBJ = $(SRC:.cpp=.o)           # 对象文件列表
DEP = $(OBJ:.o=.d)             # 依赖文件列表

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

# 编译源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 包含自动生成的依赖
-include $(DEP)

# 清理目标
clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

.PHONY: all clean
