## lock-obj-pub.hppa-unknown-linux-gnu.h
## File created by gen-posix-lock-obj - DO NOT EDIT
## To be included by mkheader into gpg-error.h

typedef struct
{
  long _vers;
  union {
    volatile char _priv[48];
    int _x16_align __attribute__ ((aligned (16)));
    long _x_align;
    long *_xp_align;
  } u;
} gpgrt_lock_gnu_t;

#define GPGRT_LOCK_INITIALIZER {1,{{0,0,0,0,0,0,0,0, \
                                    0,0,0,0,0,0,0,0, \
                                    0,0,0,0,0,0,0,0, \
                                    0,0,0,0,0,0,0,0, \
                                    0,0,0,0,0,0,0,0, \
                                    0,0,0,0,0,0,0,0}}}
##
## Local Variables:
## mode: c
## buffer-read-only: t
## End:
##
