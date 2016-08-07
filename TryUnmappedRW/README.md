TryUnmappedRW is simple kernel security verification tool. 


TryUnmappedRW will iterate over files provided in file, next it will try to open it in mode which you want (r|w) and it will try to perform read/write operation on that file with unmapped buffer (0x4141414141414141) as parameter. It allows to detect simpliest cases where developer implements device/proc/sysfs files and does not use secure functions as copy_from_user()/copy_to_user().



<pre>$ ./tryUnmappedRW 
Usage:
 tryUnmappedRW list /data/local/tmp/list.txt r
 tryUnmappedRW list /data/local/tmp/list.txt w
 tryUnmappedRW single /dev/hiddenFile r

 tryUnmappedRW list list.txt mode - try to open all files listed in list.txt
 tryUnmappedRW single /dev/hiddenFile mode - try to open /dev/hiddenFile
 	mode parameter can be specified 'r' for read only open or 'w' for write only open.</pre>



To gereate file paths file you can use "find" binary:
<pre>$ find /dev/ > /data/local/tmp/dev.txt</pre>
  
  
How to build?  
  
Just run:   
$ make  
If you want make cross compile then run:  
$ CC_PATH=/path/to/your/version/of/g++/arm-linux-eabi- make