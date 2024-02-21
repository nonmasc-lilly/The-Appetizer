all: main.asm
	fasm main.asm drive/BOOTX64.EFI

test: all
	qemu-system-x86_64 -bios OVMF.fd -net none -drive format=raw,file=fat:rw:drive/
