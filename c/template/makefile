OUTPUT=MAIN
BASEADRS=0xA000
OBJECTS=start.o main.o
CFLAGS=-Os

PREFIX=m6809-unknown
CC=$(PREFIX)-gcc
AS=lwasm
#$(PREFIX)-as
LD=$(PREFIX)-ld
LN=lwlink
LIBPATH=~/coco/lib/gcc/m6809-unknown/4.6.1/
#/usr/local/gcc6809/lib/gcc/m6809-unknown-none/4.3.4/libgcc-cache
LIBOBJ=

all: $(OBJECTS)
	##aslink -mnwxsoz -b .text=$(BASEADRS) $(OBJECTS) $(LIBOBJ)
	$(LN) -b --section-base=SECT=$(BASEADRS $(OBJECTS) $(LIBOBJ)
	gcchex2bin -i$(OUTPUT).s19 -o$(OUTPUT).BIN
	rm -f $(OUTPUT).s19

clean:
	rm -f $(OUTPUT).BIN $(OUTPUT).map $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $< -r -o$@