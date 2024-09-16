#ifndef GLOBAL_H
#define GLOBAL_H

#include "header.h"

extern int     Portnum;
extern int     Lasthour;
extern int     Ipmonitor;
extern int     Lassusers;
extern int     Maxlassusers;
extern time_t  ti;
extern struct  tm *whattime;
extern int     housestatus;
extern int     lasstime;
extern int     lasstries;
extern int     lasschecktime;
extern int     lasswait;
extern int     houseflags;
extern int     lasttick;

extern char    capstr[64];
extern char    stringo[2048];
extern char    stringp[2048];
extern char    stringq[2048];
extern char    stringr[2048];
extern char    stringt[2048];
extern char    stringu[2048];

extern char    *argles;

extern int     parc;
extern char    parr[4][256];
extern char    parv[4][256];

extern char    unames[MAXUSERS][16];
extern char    cnames[MAXUSERS][16];
extern int     nnext[MAXUSERS],nlast[MAXUSERS];
extern int     nhash[256];
extern int     lastshout[MAXUSERS]; /* Sadly necessary 8-( */
extern int     shouts[MAXUSERS];

extern int     Firstuser;
extern int     Roomuser[MAXROOMS];
extern char    Roomname[MAXROOMS][64];
extern char    Roomexit[MAXROOMS][16];
extern char    Roomdesc[MAXROOMS][1024];

extern int     Exitfrom[MAXEXITS];
extern int     Exitto[MAXEXITS];

extern int     Exitflags[MAXEXITS];

extern struct  user users[MOST];
 
extern int   togand;
extern int   togeor;

extern struct eddata edits[MAXEDITS];

extern char  noticemsg[MAXNOTICES][64];
extern int   noticenum[MAXNOTICES];

extern struct in_addr hostlist[MAXHOSTS];
extern int    hoststatus[MAXHOSTS];
extern char   hostlabel[MAXHOSTS][20];

#endif // GLOBALS_H
