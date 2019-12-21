# malloc
This repository contains an implementation of the malloc and free functions in C. This was a university assignment using the guide referenced at the end.

- The policy adopted for the malloc function is a first fit type policy.
- The block data structure is a double-link list type.

# Implementation

## pointers with sizeof 8 bytes
To align the size of the data block the following function was used:
```
#define align8(x) (((x) + 7) & (-8))
```
This allows us to obtain the closest highest multiple of 8. The idea is based off the fact that the last 3 bits of information for a multiple of 8 should be 0. Given that x=x&(-8) gives the lowest closest multiple of 8, by adding 7 we will get the closest high multiple of 8.

## pointers with sizeof 4 bytes

Implementation is analogous to the tutorial linked in the reference.

# Compilation
If you are on a 64bit machine you can directly compile it using Makefile and it will align using the formula above.

If you desire to run the 32bit implementation on a 64bit machine (which uses pointers of 4 bytes) you will need to install the gcc-multilib package and run the Makefile with CFLAGS = -m32

# Reference

A Malloc Tutorial - Marwan Burelle - Laboratoire Système et Sécurité de l’EPITA (LSE) 

https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf


