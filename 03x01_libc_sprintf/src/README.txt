=====================
Why do we need sbrk.c
=====================
* SHORT: 
  sbrk.c offers an implementation for syscall function _sbrk()

* DETAILS:
  sprintf() is a libc function, 
  our version of libc is newlib.
  Newlib implements sprintf() using a set of syscalls (more info in slides)
  One of the used syscalls is _sbrk()   (to increase program data space)

  1) When building for a non-hosted environment (-ffreestanding),
  we need to provide these syscalls ourselves.
  Some of these syscalls have stubs that can be added by the linker via -lnosys
  Some of these syscalls, we need to implement ourselves (or add via libraries)
     SO NEED FOR _sbrk() implementation


  2) When building for a hosted environment (without -ffreestanding)
  the linker will assume it can use the syscalls provided by the running environment.
  The binary will contain no implementation for these syscalls (verify with arm-non-eabi-readelf)
     SO NO NEED FOR _sbrk()    
  
