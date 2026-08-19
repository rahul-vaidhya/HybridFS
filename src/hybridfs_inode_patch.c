/* Add these fields near end of struct inode in kernel/file.h */

int hfs_resident;
char hfs_data[128];
uint hfs_size;

uint hfs_oldblock;
uint hfs_curblock;

int hfs_pending;
int hfs_dirty;
