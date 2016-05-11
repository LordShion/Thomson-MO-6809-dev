ASM=lwasm

LNK=lwlink

SRC= $(wildcard *.S)
OBJ= $(SRC:.S=.BIN)
BIN= $(OBJ:.O=.BIN)

EXEC=first


all: first 

first: 
	@echo "assembling"
	@$(ASM) -o $(OBJ) $(SRC)
	@echo "assembly finished"
	@#@echo "linking"
	@#@$(LNK) -o $(BIN) $(OBJ)
clean: 
	@echo "cleanning......."
	@rm -rf *.O
	@rm -rf *.out
	@rm -rf *.BIN
	@rm -rf *.sap
	@echo "cleanning finished"

run:
	@echo "creating sap file"
	@sap2 -c $(BIN:.BIN=.sap)
	@echo "adding binary to sap file"
	@sapfs -a $(BIN:.BIN=.sap) $(BIN)
	@echo "listing sap file"
	@sapfs -t $(BIN:.BIN=.sap)
	@echo "sap file fully created)"
	@mess mo6 -nomaximize -flop1 $(BIN:.BIN=.sap) -keymap -keymap_file /usr/share/games/mess/keymaps/km-fr.txt
