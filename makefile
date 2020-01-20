CC = gcc
CFLAGS = -Wall

SOURCEDIR = src
BUILDDIR = bin

EXECUTABLE = Poker
SOURCES = $(wildcard $(SOURCEDIR)/*.c) $(wildcard $(SOURCEDIR)/*/*.c)
OBJECTS := $(SOURCES:%.c=$(BUILDDIR)/%.o)

all: build $(EXECUTABLE)

build:
	@echo "MAKING BUILD DIRECTORY..."
	mkdir -p $(BUILDDIR)

$(EXECUTABLE): $(OBJECTS)
	@echo "\nBUILDING EXECUTABLE..."
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.c
	@echo "\nCOMPILING SOURCE $< INTO OBJECT $@..."
	@echo "MAKE DIRECTORY $(@D) IF NEEDED..."
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)
	rm -f $(EXECUTABLE)
	rm log.txt
