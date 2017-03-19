#ifndef _PETERSON_H
#define _PETERSON_H

#ifdef _PETERSON_C 
#define EXTERN
#else
#define EXTERN extern
#endif // #ifdef _PETERSON_C

#define TRUE 1
#define FALSE 0 
#define LEVEL_ZERO 0

EXTERN int *level;
EXTERN int *last_enter;
EXTERN int init_peterson(char *);
EXTERN int close_peterson();
EXTERN void enter_region(int);
EXTERN int is_highest_level(int);
EXTERN void leave_region(int);

#endif // #ifndef _PETERSON_H
