![MALA-OS logo](https://res.cloudinary.com/drko1uhot/image/upload/v1791050830/file_00000000f9e08246a441f216522de1b8_spfgva.png)

# MALA-OS

MALA-OS is a Linux-based distribution built on the Linux kernel, with GRUB as its bootloader. It is a learning project, developed in small, testable stages and booted in QEMU.

> Status: early development. This document is updated as the project progresses.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Current Progress](#current-progress)
3. [Roadmap](#roadmap)
4. [Known Issues](#known-issues)

## Prerequisites

- A Linux host with `gcc`, `cpio`, `gzip`, and `qemu-system-x86_64`
- Read access to a Linux kernel image (see Known Issues)

## Current Progress

### 1. Init (PID 1)

`init` is the first user-space process started by the kernel. The current version:

- Mounts the virtual filesystems `/proc` and `/sys`
- Launches a child program
- Reaps terminated child processes using a SIGCHLD handler

Build and boot:

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

qemu-system-x86_64 \
    --enable-kvm \
    -kernel /boot/vmlinuz-linux \
    -initrd build/initramfs.cpio.gz \
    -nographic \
    -serial mon:stdio
```

Expected output: messages from `init` showing startup, the mounts, the child launch, and the reaping of the child.

### 2. Root Filesystem

The root filesystem follows the Filesystem Hierarchy Standard (FHS), with directories such as `/bin`, `/sbin`, `/etc`, `/proc`, `/sys`, `/dev`, and `/tmp`. It is currently created by hand with `scripts/filesystem_setup.sh`, which will be replaced by an automated build step.

### 3. Shell

A shell has been written and works on the host machine. It has not yet been integrated into the MALA-OS root filesystem.

## Roadmap

- [x] Development environment
- [x] Git repository
- [x] Linux kernel boots in QEMU
- [x] Initramfs with a custom init
- [x] Shell (host only)
- [ ] Shell integrated into the target system
- [ ] Core utilities
- [ ] Root filesystem
- [ ] Automated filesystem creation

## Known Issues

- The build commands above are documented as written and have not all been verified end to end.
- The kernel is currently taken from the host's `/boot`, which ties the build to one machine.