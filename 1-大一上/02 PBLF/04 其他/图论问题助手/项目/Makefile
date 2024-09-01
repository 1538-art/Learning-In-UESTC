# 编译器设置
CXX := g++
CXXFLAGS := -std=c++11 -Wall -I/usr/include -g -rdynamic

# 目标文件夹和文件
TARGET := program
SRCDIR := src
INCDIR := include
BUILDDIR := build

# 源文件和头文件
SRCEXT := cpp
HDREXT := h
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
HEADERS := $(wildcard $(INCDIR)/*.$(HDREXT))
OBJECTS := $(addprefix $(BUILDDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.o)))

# 构建规则
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILDDIR) $(TARGET)