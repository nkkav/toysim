CP=cp

BIN_TOY=/cygdrive/e/projects/toysim-tools
AS_TOY=$(BIN_TOY)/toy-elf-as
LD_TOY=$(BIN_TOY)/toy-elf-ld
DUMP_TOY=$(BIN_TOY)/toy-elf-objdump

# Default target : elaborate
all : ${BENCH}.toyx

# Generate hex dump for the program memory contents

${BENCH}.toyx:
#	$(AS_TOY) -o ac_start.o ac_start.s
	$(AS_TOY) -o ${BENCH}.o ${BENCH}.asm
#	$(LD_TOY) -Ttext 0x0100 -Tdata 0x1000 -eentry -Map ${BENCH}.map -s -N -o ${BENCH}.axf ac_start.o ${BENCH}.o
	$(LD_TOY) -Ttext 0x0100 -Tdata 0x1000 -eentry -Map ${BENCH}.map -s -N -o ${BENCH}.axf ${BENCH}.o
	$(CP) -f ${BENCH}.axf ${BENCH}.toyx
	-@$(DUMP_TOY) --disassemble ${BENCH}.toyx > ${BENCH}.toy

tidy:
	rm -rf *.toy *.axf *.map *.o

clean:
	rm -rf *.toy *.axf *.map *.o *.toyx
