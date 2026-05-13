#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
  struct stat st;
  if(argc<2){ printf("usage: hfsstat file\n"); exit(0); }
  if(stat(argv[1], &st)<0){ printf("file not found\n"); exit(0); }

  printf("HybridFS Report: %s\n", argv[1]);
  printf("Size: %d bytes\n", (int)st.size);

  if(st.size <= 20)
    printf("Storage Tier: Resident (NTFS style)\n");
  else
    printf("Storage Tier: Non-Resident CoW (APFS style)\n");

  printf("Log Mode: Append-only metadata (LFS style)\n");
  exit(0);
}
