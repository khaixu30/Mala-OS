# SETTING UP ENVIRONMENT

## REQUIREMENTS

Before building the project make sure to check the following packages/libraries installed on your system. Each one has command to verify and install if they are not installed.

### 1. `gcc` OR `clang`
```bash
gcc --version
```
You should get something like `gcc (GCC) xx.x.x xxxxxxxx`. If it's not installed try installing it from:
```bash
sudo pacman -S base-devel # It'll install complete environment for C/C++
```

### 2. `make`
```bash
make --version
```
It's included in the `base-devel` package by default, so you'll get something like `GNU Make x.x.x`.

### 3. `binutils` (`ld`, `objdump`, `reafelf`, `nm`, `strip`)
They also come by `base-devel`, so you don't have to worry.

### 4. `git`
```bash
git --version
```

You'll get something like `git version x.xx.x`. If it's not installed try:
```bash
sudo pacman -S git
# OR USING AUR REPOSITORIES
yay -S git-git
```

### 5. `qemu-system-x86_64`
```bash
qemu-system-x86_64 --version
```
You should get something like `QEMU emulator xx.x.x`. If not installed try:

```bash
sudo pacman -S qemu-system-x86
```

### 6. `grub-mkrescue` / `xorriso`
```bash
grub-mkrescue --version
```

You should something like `grub-mkrescue (GRUB) x:x.xx-x`. If not installed try:
```bash
sudo pacman -S grub libisoburn mtools dosfstools
```

### 7. KVM
Check kvm by
```bash
ls -l /dev/kvm
```

If your output is like `root kvm xx, xxx mmm dd xx:xx /dev/kvm`, it's installed, otherwise you'll have to enable virtualization from `BIOS`/`UEFI`. And to add user in the `kvm` group run:
```bash
sudo usermode -aG kvm $USER     # Log out and log in again for changes to take effect
```

### 8. `gdb`
Comes with `gcc` or `base-devel`, you can verify it from:
```bash
gdb --version
```

Output should be like `GNU gdb (GDB) xx.x`


### 9. A text-editor/ IDE
I've used VSCode, you can choose IDE/Text editor of your choice and preference.


[*Later Requirements will be mention here...*]