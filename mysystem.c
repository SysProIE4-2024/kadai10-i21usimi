/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  int pid = 0;
  if(command == NULL){
    return 1;
  }
  if((pid = fork()) < 0){
    return -1;
  }
  if(pid != 0){
    while(wait(&status) != pid);
  }else{
    execl("/bin/sh", "sh", "-c", command, NULL);
    perror("/bin/sh");
    exit(127);
  }
  return status;
}

/* 実行例
%make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
%./mysysmain
使い方 : ./mysysmain コマンド文字列
%./mysysmain xxx
mysystem:
sh: xxx: command not found
retval = 00007f00
system:
sh: xxx: command not found
retval = 00007f00
%./mysysmain ls
mysystem:
Makefile        README.md       README.pdf      mysysmain       mysysmain.c     mysystem.c      mysystem.h
retval = 00000000
system:
Makefile        README.md       README.pdf      mysysmain       mysysmain.c     mysystem.c      mysystem.h
retval = 00000000
%./mysysmain ls -l
使い方 : ./mysysmain コマンド文字列
%./mysysmain "ls -l"
mysystem:
total 584
-rw-r--r--  1 motoharu  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 motoharu  staff    2795  7  4 09:46 README.md
-rw-r--r--@ 1 motoharu  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 motoharu  staff   33816  7  9 17:22 mysysmain
-rw-r--r--  1 motoharu  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 motoharu  staff    1096  7  9 17:26 mysystem.c
-rw-r--r--  1 motoharu  staff      90  7  4 09:46 mysystem.h
retval = 00000000
system:
total 584
-rw-r--r--  1 motoharu  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 motoharu  staff    2795  7  4 09:46 README.md
-rw-r--r--@ 1 motoharu  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 motoharu  staff   33816  7  9 17:22 mysysmain
-rw-r--r--  1 motoharu  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 motoharu  staff    1096  7  9 17:26 mysystem.c
-rw-r--r--  1 motoharu  staff      90  7  4 09:46 mysystem.h
retval = 00000000
%./mysysmain "cat aaa"
mysystem:
cat: aaa: No such file or directory
retval = 00000100
system:
cat: aaa: No such file or directory
retval = 00000100
%./mysysmain "echo aaa > a.txt"
mysystem:
retval = 00000000
system:
retval = 00000000
%./mysysmain "cat a.txt"
mysystem:
aaa
retval = 00000000
system:
aaa
retval = 00000000
*/
