# VARIABLES
CXX = g++
CXXFLAGS = -std=c++17 $(INCLUDES) -Wall
TARGET = huffman
SRCDIR = src
INCDIR = headers
OBJDIR = obj
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/huffman.cpp $(SRCDIR)/utilities.cpp
INCLUDES = -I$(INCDIR)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# RULE TO BUILD
$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# RULE TO CREATE OBJS 
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)  # Create the obj directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# CLEANING BUILD ARTIFACTS
clean:
	rm -rf $(OBJDIR) $(TARGET)
