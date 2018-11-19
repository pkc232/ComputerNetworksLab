#include <fcntl.h>
#include <bits/stdc++.h>
#include <stdio.h>

#include <sys/poll.h>

#include <sys/time.h>

#include <unistd.h>
using namespace std;

/* For simplicity, all error checking has been left out */


int main(int argc, char ** argv) {

   int fd1,fd2;

   char buf[1024];

   int i;

   struct pollfd pfds[2];

   fd1 = open("file1.txt", O_RDONLY);
   fd2 = open("file2.txt",O_RDONLY);


   while (1) {

       pfds[0].fd = fd1;

       pfds[0].events = POLLIN;


       pfds[1].fd = fd2;

       pfds[1].events = POLLIN;


       poll(pfds, 2, 1000);

       if (pfds[0].revents & POLLIN) {

          i = read(fd1, buf, 1024);

          if (!i) {

              printf("stdin closed \n ");

              return 0;

          }