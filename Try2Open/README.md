Try2Open is simple file permissions audit tool. 

In multiple systems there are introduced MAC systems as selinux or smack what makes exploitation harder. Without MAC we could just check file permissions to check which files we can modify, in case of MAC we have to verify MAC policies and DAC to be sure if we can modify it. 


Try2Open will iterate over files provided in file and will try to open it in mode which you want (r|w).



<pre>$ ./try2open 
Usage:
 try2open list /data/local/tmp/list.txt r
 try2open list /data/local/tmp/list.txt w
 try2open single /dev/hiddenFile r

 try2open list list.txt mode - try to open all files listed in list.txt
 try2open single /dev/hiddenFile mode - try to open /dev/hiddenFile
 	mode parameter can be specified 'r' for read only open or 'w' for write only open.</pre>


To gereate file paths file you can use "find" binary:
<pre>$ find /dev/ > /data/local/tmp/dev.txt</pre>
  
  
How to build?  
  
Just run:   
$ make  
If you want make cross compile then run:  
$ CC_PATH=/path/to/your/version/of/g++/arm-linux-eabi- make