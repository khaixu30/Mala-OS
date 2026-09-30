
# Create Directories
mkdir build/rootfs
mkdir build/rootfs/{bin, sbin, etc, dev, proc, sys, tmp, var, root, home}

# Stickey Bit, Anyone can write, but owner can delete
chmod 1777 build/rootfs/tmp

# Making Device nodes
sudo mknod build/rootfs/dev/console c 5 1
sudo mknod build/rootfs/dev/null c 1 3
sudo mknod build/rootfs/dev/tty c 5 0
sudo mknod build/rootfs/dev/zero c 1 5

# Setting up, /etc folder for minimal setup
cat > build/rootfs/etc/passwd << 'EOF'
root:x:0:0:root:/root:/bin/sh
EOF

cat > build/rootfs/etc/hostname << 'EOF'
projectos
EOF

# Populate /sbin with your own init
cp build/initramfs_init/init build/rootfs/sbin/init

# Verifying tree
find build/rootfs -mindepth 1 | sort
ls -la build/rootfs/dev



