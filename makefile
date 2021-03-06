# Drakanopong
# Linux makefile
CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS = -lSDL -lSDL -lGLU -lGL -lm -lSDL_image -lglut -lSDL_ttf

APP_BIN = Drakanopong

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = -I include
BIN_PATH = bin
LIB_PATH = lib

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')
OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

all: $(APP_BIN)

$(APP_BIN): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	$(CC) -o $(BIN_PATH)/$(APP_BIN) $(OBJ_FILES) $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN_PATH)/$(APP_BIN) &"
	@echo "--------------------------------------------------------------"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $< -o $@ $(CFLAGS) $(INC_PATH)

clean:
	rm $(OBJ_FILES) $(BIN_PATH)/$(APP_BIN)
