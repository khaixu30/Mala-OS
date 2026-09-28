# MALA-OS
A Linux-based distribution, working with Linux Kernel and GRUB under-the-hood.
[*More information will be added as the project progresses.*]

## 1. Current Progress

### - First `init` application:
Currently, `init` doesn't do anything specific, other than printing a `hello message`.

Execution commands:
```bash
# Setting up and Compiling the init as statically linkable file.
mkdir -p src/init   # Create init directory in src, and write init.c in that directory.
gcc --static -o src/init/init src/init/init.c   # Compile init.c as statically linkable file.

# Confirming if it's static
file src/init/init
# Should report: statically linked

# Staging the initramfs (setting up init as PID 1)
mkdir -p build/initramfs_root  # Create a seperate folder for builds and executables, keep the code seperate from executables
cp src/init/init build/initramfs_root/init  # Move the newly compiled init from src directory to build directory
cd build/initramfs_root     # Go to directory `build/initramfs_root`
find . | cpio -o -H newc 2>/dev/null | gzip ../../build/initramfs.cpio.gz   # Create a cpio archive
cd ../..    # Proceed back to project's root directory

qemu-system-x86_64 \       # Run QEMU System x86_64 with sudo privileges
    --enable-kvm \              # Enable Virtual Machine (kvm)
    -kernel /boot/vmlinuz-linux \   # Set location to kernel, base kernel can be found in the directory
    -initrd build/initramfs.cpio.gz \   # Set the newly compressed file as initramfs
    -nographic \                # No need for GUI
    -serial mon:stdio           # Pipe the input/output of the virtual machine to the current konsole/terminal
```

The output is expected to be the line, you wrote in `write(1, "Hello, World! I'm Mala-OS, and this is my root process, PID 1.\n", 63);`. In short, it should print `"Hello, World! I'm Mala-OS, and this is my root process, PID 1."`.


## 2. Project Progress
- [x] Development Environment
- [x] Git Repository
- [x] Linux kernel boot
- [x] Basic Initramfs
- [ ] Proper inital ram filesystem (initramfs)
- [ ] Shell
- [ ] Core Utilities
- [ ] Root filesystem


[*Project is under work, will add more stuff and format documentation as we progress.*]

