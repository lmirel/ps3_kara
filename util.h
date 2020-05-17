
#ifndef __UTIL_H__
#define __UTIL_H__

struct Subs {
    struct Subs *prev, *next;   //chaining refs
    int idx;            //sub index
    long smsts;         //millis timestamp start
    long emsts;         //millis timestamp end
    char *text;     
};

struct Subs *subs_load (char *path);
struct Subs * subs_clear (struct Subs *subs);
struct Subs *subs_get (struct Subs *head, long cts);

#endif
