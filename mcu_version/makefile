CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

SRCDIR = .
BUILDDIR = build

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRC))

TARGET = $(BUILDDIR)/muc_firmware

all: $(TARGET)

$(TARGET): $(OBJ) | $(BUILDDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

