# OS-demo-programs
A collection of short demonstration programs from a decade+ of OS class.

I have taught the junior/senior level operating systems class at Saint
Louis University since 2001, usually every other year. The class is more
of a systems programming class, in that we don't actually write or alter
the OS itself.

Along the way, I created a number of short C/C++ programs to demonstrate operating
system behavior. The use of these programs may not be obvious, or well commented. I will
try to improve that over time.

They are organized into eight directories based on topic:
* basic : command line arguments, `stdin/out/err`, `errno` and `perror`
* fork : process management with `fork`, `exec`
* ipc : interprocess communication with pipes and signals
* threads : `pthread` threads and synchronization
* security : security issues
* memory : memory management, pointers, TLB and stacks
* file : disk and file issues
* network : networking with sockets
