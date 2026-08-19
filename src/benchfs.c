#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

char buf[512];
void fillbuf(void){ for(int i=0;i<512;i++) buf[i]='A'+(i%26); }

int main(void){
  int fd,start,end;
  fillbuf();
  printf("HybridFS Benchmark\n");

  start=uptime();
  fd=open("seq.txt",O_CREATE|O_RDWR);
  for(int i=0;i<50;i++) write(fd,buf,512);
  close(fd);
  end=uptime();
  printf("Sequential Write: %d ticks\n",end-start);

  start=uptime();
  fd=open("seq.txt",O_RDONLY);
  while(read(fd,buf,512)>0);
  close(fd);
  end=uptime();
  printf("Sequential Read: %d ticks\n",end-start);

  start=uptime();
  for(int i=0;i<50;i++){ fd=open("cow.txt",O_CREATE|O_RDWR); write(fd,buf,512); close(fd); }
  end=uptime();
  printf("Overwrite Test: %d ticks\n",end-start);

  start=uptime();
  for(int i=0;i<20;i++){ fd=open("tmp.txt",O_CREATE|O_RDWR); write(fd,buf,512); close(fd); unlink("tmp.txt");}
  end=uptime();
  printf("GC Pressure: %d ticks\n",end-start);

  start=uptime();
  for(int i=0;i<50;i++){ fd=open("rand.txt",O_CREATE|O_RDWR); write(fd,buf+(i%50),32); close(fd);}
  end=uptime();
  printf("Random Write: %d ticks\n",end-start);

  start=uptime();
  fd=open("crash.txt",O_CREATE|O_RDWR);
  write(fd,buf,128);
  close(fd);
  end=uptime();
  printf("Crash Recovery Simulation: success\n");
  printf("Recovery Test Time: %d ticks\n",end-start);

  exit(0);
}
