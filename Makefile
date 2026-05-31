TARGET = aci_server

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -static -O3
LIBS += -lssl -lcrypto -lgdi32 -lcrypt32 -lws2_32 -lwsock32
LIBS += -static icon.res

SOURCES = main.cpp
SOURCES += src/server.cpp

OBJDIR = obj
OBJS = $(SOURCES:.cpp=.o)
OBJS := $(OBJS:.c=.o)
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

.PHONY: all clean rebuild

all: $(TARGET)
	@echo Build complete.

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/%.cpp src/%.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

rebuild: clean all

clean:
	rm -f $(TARGET) $(OBJDIR)/*.o
