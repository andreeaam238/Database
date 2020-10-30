CC = gcc
CFLAG = -Wall -Wextra -g 
EXE = tema1
CODE = structures.c

build: $(EXE)

$(EXE): $(CODE) 
	$(CC) $(CFLAG) $(CODE) -o $(EXE)

clean: $(EXE)
	rm -f $(EXE)
