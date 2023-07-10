CC = gcc

SRC = src
APP = pserver
C = pclient


all:
	$(CC) ./$(SRC)/*.c -o $(APP)
	$(CC) ./*.c -o $(C)
	./$(APP)




