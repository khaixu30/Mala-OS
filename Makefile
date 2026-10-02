compile_init:
	gcc -static src/init/init.c -o build/initramfs_root/init

compile_child_process-experiment:
	gcc -static src/experiments/child_program.c -o build/initramfs_root/bin/child_program

make_gz:
	cd build/initramfs_root ; find . | cpio -o -H newc 2>/dev/null | gzip > ../../build/initramfs.cpio.gz ; cd ../..

run_qemu:
	qemu-system-x86_64 --enable-kvm -kernel /boot/vmlinuz-linux -initrd build/initramfs.cpio.gz -append "console=ttyS0 rdinit=/init" -nographic -serial mon:stdio


compile_shell:
	mkdir -p build/shell ; gcc -o build/shell/shell src/shell/shell.c

run_shell:
	./build/shell/shell