ASM=lwasm

SRC= $(wildcard *.s)
OBJ= $(SRC:.s=.o)


EXEC=first


all: first

first: 
	@echo "assembling"
	@$(ASM) -o $(OBJ) $(SRC)
	@echo "assembly finished"
clean: 
	@echo "cleanning......."
	@rm -rf *.o
	@echo "cleanning finished"


