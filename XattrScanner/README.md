XattrScanner is simply xattr audit tool.

What is Xattr?

https://en.wikipedia.org/wiki/Extended_file_attributes
man 5 attr


Why xattr can be a good target for audit?

Xattr can store capabilities for file ("security.capability" attribute). So we can compare it to setuid/setgid bit but sometimes even more powerfull (it can allow for smack/selinux bypass in case if we get CAP_MAC_ADMIN).

If you do not know what "linux capability" is then please check:
man 7 capabilities
http://www.friedhoff.org/posixfilecaps.html

Capabilities are applied as follows:
    1)  pI' = pI
    2)  pP' = (X & fP) | (pI & fI)
    3)  pE' = fE & pP'

So for example:
If we find file which have capability CAP_SYS_ADMIN as capability permitted on file and next we find vulnerability which will allow us get code execution in context of that binary then we can move CAP_SYS_ADMIN from CapPermitted to CapEffective (only if we have it in CapBnd), this allows us for multiple operations as mounting files systems without root permission (uid=0)!

More info how to exploit some capability to full root:
https://forums.grsecurity.net/viewtopic.php?f=7&t=2522


So what exactly XattrScanner will does for You?

It just traverse over file system and obtain xattr attribute for each file.
If it find some xattr attribute then it will dump its name and value in hex and it will try to dump it as string.
Also if the name of attribute will be "security.capability" then it will decode and dump capability.


Example usages:

//1
$ ./xattrScanner -p /usr/bin
Scanning: /usr/bin
[+] (1) /usr/bin/gnome-keyring-daemon
 capInheritable: 0x0000000000000000 capPermitted: 0x0000000000004000 capEfective: 0x01

[+] (1) /usr/bin/arping
 capInheritable: 0x0000000000000000 capPermitted: 0x0000000000002000 capEfective: 0x00

Done
//


//2
$ ./xattrScanner -p /
Scanning: /
[+] (2) /home/user/Downloads/ofs.c
Name: user.xdg.origin.url Value: \x68\x74\x74\x70\x3a\x2f\x2f\x73\x65\x63\x6c\x69\x73\x74\x73\x2e\x6f\x72\x67\x2f\x6f\x73\x73\x2d\x73\x65\x63\x2f\x32\x30\x31\x35\x2f\x71\x32\x2f\x61\x74\x74\x2d\x37\x31\x37\x2f\x6f\x66\x73\x5f\x63\x2e\x62\x69\x6e
Value String ( http://seclists.org/oss-sec/2015/q2/att-717/ofs_c.bin )
Name: user.xdg.referrer.url Value: \x68\x74\x74\x70\x3a\x2f\x2f\x73\x65\x63\x6c\x69\x73\x74\x73\x2e\x6f\x72\x67\x2f\x6f\x73\x73\x2d\x73\x65\x63\x2f\x32\x30\x31\x35\x2f\x71\x32\x2f\x37\x31\x37
Value String ( http://seclists.org/oss-sec/2015/q2/717 )

Done
//


We can see that /usr/bin/gnome-keyring-daemon has capability permitted: 0x0000000000004000
Now we can run:
$ capsh --decode=0x0000000000004000
0x0000000000004000=cap_ipc_lock
To see that it has capability cap_ipc_lock.


How to build?

Just run: 
$ make
If you want make cross compile then run:
$ CC_PATH=/path/to/your/version/of/g++/arm-linux-eabi- make