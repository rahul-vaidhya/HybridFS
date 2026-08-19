int
writei(struct inode *ip, int user_src, uint64 src, uint off, uint n)
{
  uint tot, m;
  struct buf *bp;

  if(off > ip->size || off + n < off)
    return -1;
  if(off + n > MAXFILE * BSIZE)
    return -1;

  if(off == 0 && n <= 128){
    if(either_copyin(ip->hfs_data, user_src, src, n) == -1)
      return -1;
    ip->hfs_resident = 1;
    ip->hfs_size = n;
    ip->size = n;
    printf("HybridFS: resident inline storage inode %d\n", ip->inum);
    iupdate(ip);
    return n;
  }

  if(off == 0 && ip->size > 0){
    ip->hfs_pending = 1;
    ip->hfs_oldblock = ip->addrs[0];
    printf("HybridFS: CoW overwrite inode %d\n", ip->inum);
  }

  ip->hfs_resident = 0;

  for(tot=0; tot<n; tot+=m, off+=m, src+=m){
    uint addr = bmap(ip, off / BSIZE);
    if(addr == 0)
      break;
    ip->hfs_curblock = addr;
    bp = bread(ip->dev, addr);
    m = min(n - tot, BSIZE - off % BSIZE);
    if(either_copyin(bp->data + (off % BSIZE), user_src, src, m) == -1){
      brelse(bp);
      break;
    }
    log_write(bp);
    brelse(bp);
  }

  if(off > ip->size)
    ip->size = off;

  ip->hfs_pending = 0;
  ip->hfs_dirty = 1;
  iupdate(ip);
  return tot;
}
