# Makefile for the 'obfuscator' GCC plugin

# Path to GCC plugin headers, adjust as necessary
GCC_PLUGIN_DIR := $(shell gcc-9 -print-file-name=plugin)

# Plugin source file
PLUGIN_SOURCE := obfuscator.cc

# Output file
PLUGIN_OUTPUT := obfuscator.so

# Compiler flags
CFLAGS := -I$(GCC_PLUGIN_DIR)/include -fPIC -O2

# Build the plugin
all: $(PLUGIN_OUTPUT)

$(PLUGIN_OUTPUT): $(PLUGIN_SOURCE)
	g++-9 $(CFLAGS) -shared $(PLUGIN_SOURCE) -o $(PLUGIN_OUTPUT)

# Clean up build artifacts
clean:
	rm -f $(PLUGIN_OUTPUT)

.PHONY: all clean
