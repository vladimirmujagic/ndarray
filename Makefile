# set non-optional compiler flags here
CXXFLAGS += -O3 -g

# set non-optional preprocessor flags here
# eg. project specific include directories
CPPFLAGS +=

# find cpp files in subdirectories
SOURCES := $(shell find src/ -name '*.cpp')
SOURCES += $(shell find tests/ -name '*.cpp')

# find headers
HEADERS := $(shell find src/ -name '*.hpp')
HEADERS += $(shell find tests/ -name '*.hpp')

OUTPUT := ndarray_test

# Everything depends on the output
all: $(OUTPUT)

# The output depends on sources and headers
$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	$(RM) $(OUTPUT)
