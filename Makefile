CC=arm-none-eabi-gcc
CP=arm-none-eabi-g++
OC=arm-none-eabi-objcopy 
LD=arm-none-eabi-ld

CFLAGS=-c -mcpu=arm946e-s -march=armv5te -mlittle-endian
# No linker flags yet, but here if you need it
LDFLAGS=-nostartfiles

all:
	$(CC) -g source/*.c $(CFLAGS)
	$(CC) -g source/*.s $(CFLAGS)
	mkdir -p obj
	cp *.o ./obj
	$(CC) -T 3ds.ld *.o $(LDFLAGS)
	cp a.out ./bin/homebrew.elf
	$(OC) -O binary a.out payload.bin
	cat lib/p3ds/exp.bin payload.bin lib/p3ds/pad.bin > Launcher.dat
	echo "Launcher.dat successfully generated"
	rm *.o *.out

clean:
	echo "Omnomnomnom files"
	rm *.o *.out payload.bin
