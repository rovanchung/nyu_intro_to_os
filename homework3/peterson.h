#ifndef _PETERSON_H
#define _PETERSON_H

#ifdef _PETERSON_C 
#define EXTERN
#else
#define EXTERN extern
#endif // #ifdef DEFINE_VARIABLES

#define TRUE 1
#define FALSE 0 
#define ZERO_STATE 0

EXTERN int *level;
EXTERN int *last_enter;
EXTERN int init_peterson(int);
EXTERN int close_peterson();
EXTERN void enter_region(int);
EXTERN int is_highest_level(int);
EXTERN void leave_region(int);

#endif // #ifndef _PETERSON_H
