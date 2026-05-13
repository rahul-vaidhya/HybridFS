/* Recovery idea:
At boot or inode load:
if(ip->hfs_pending){
   ip->addrs[0] = ip->hfs_oldblock;
   ip->hfs_pending = 0;
}

GC idea:
if(ip->hfs_dirty){
   // reclaim stale previous versions if tracked
   ip->hfs_dirty = 0;
}
*/
