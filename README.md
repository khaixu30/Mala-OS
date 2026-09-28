# MALA-OS
A linux-based dstribution, built over linux `kernel` and `grub`.
[*More information will be added as the project progresses.*]

## 1. Current Progress

### - First `init` application:
Currently, `init` doesn't do anything specific, other than printing a `hello message`.

Execution commands:
```bash
# Setting up and Compiling the init.c as statically linkable file.
mkdir -p src/init   # Create init directory in src, and write init.c in that directory.
gcc --static -o src/init/init src/init/init.c   # Compile init.c as statically linkable file.

# Confirming if it's static
file src/init/init
# Should report: statically linked

# Staging the initramfs (setting init.c or init as the first thing to execute after kernel)
mkdir -p build/initramfs_root  # Create a seperate folder for builds and executables, keep the code seperate from executables
cp src/init/init build/initramfs_root/init  # Move the newly compiled init from src directory to build directory
cd build/initramfs_root     # Go to directory `build/initramfs_root`
find . | cpio -o -H newc 2>/dev/null | gzip ../../build/initramfs.cpio.gz   # Compress the executable/initramfs_root folder as gzip
cd ../..    # Proceed back to project's root directory

sudo qemu-system-x86_64 \       # Run QEMU System x86_64 with sudo privileges
    --enable-kvm \              # Enable Virtual Machine (kvm)
    -kernel /boot/vimlinuz-linux \  # Set location to kernel, base kernel can be found in the directory
    -initrd build/initramfs.cpio.gz \   # Set the newly compressed file as initramfs (to be executed right after kernel)
    -nographic \                # No need for GUI
    -serial mon:stdio           # Pipe the input/output of the virtual machine to the current konsole/terminal
```

The output is expected to be the line, you wrote in `write(1, "Hello, World! I'm Mala-OS, and this is my root process, PID 1.\n", 63);`. In short, it should print `"Hello, World! I'm Mala-OS, and this is my root process, PID 1."`.


[*Project is under work, will add more stuff and format documentation as we progress.*]

