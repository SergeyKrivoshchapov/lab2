CC=gcc
CFLAGS=-c -Wall -lm
LDFLAGS=-lm
OBJ_DIR=obj

all: lab2

lab2: $(OBJ_DIR)/main.o $(OBJ_DIR)/btree.o $(OBJ_DIR)/WIFI.o
	$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/btree.o $(OBJ_DIR)/WIFI.o $(LDFLAGS) -o lab2

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/btree.o: btree.c btree.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) btree.c -o $(OBJ_DIR)/btree.o

$(OBJ_DIR)/WIFI.o: WIFI.c WIFI.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) WIFI.c -o $(OBJ_DIR)/WIFI.o

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) lab2
