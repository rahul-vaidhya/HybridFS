HybridFS Submission Package

Files:
1. hybridfs_writei_patch.c  - Replace writei() in kernel/fs.c
2. hybridfs_inode_patch.c   - Add fields to struct inode in kernel/file.h
3. hybridfs_notes.c         - Notes for recovery and GC logic
4. benchfs.c               - Benchmark suite for xv6 user/
5. hfsstat.c              - Tier stats utility for xv6 user/

Build:
- Copy patches into xv6-riscv source
- Add benchfs.c and hfsstat.c to user/
- Add $U/_benchfs\ and $U/_hfsstat\ to Makefile UPROGS
- Run: make clean && make qemu
