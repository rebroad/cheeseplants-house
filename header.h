#ifndef HEADER_H
#define HEADER_H

#define _XOPEN_SOURCE 1

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <sys/file.h>
#include <errno.h>
#ifdef __CYGWIN__
#include <sys/ioctl.h>
#else
#include <asm/ioctls.h>
#endif
#include <unistd.h>

#define Portnumber   3672
#define MOST         256
#define MAXDAYLASS   6
#define MAXNIGHTLASS 64
#define DAYTIME      8
#define NIGHTTIME    17
#define MAXUSERS     1500
#define LOGLENGTH    20
#define INVLENGTH    64
#define MAXROOMS     64
#define MAXEXITS     100
#define MAXDELAY     600
#define MAXEDITS     10
#define SHOUTTIME    300
#define SHOUTADD     180
#define SHOUTMAX     5
#define NORMALWIDTH  80
#define NORMALHEIGHT 18
#define DLASSWAIT    21
#define NLASSWAIT    1
#define LETTERS      20
#define MAXNOTICES   100
#define TICKLENGTH   300
#define LASSIDLE     900
#define INETIDLE     3600
#define MAXHOSTS     200
#define OBJECTNUM    5

#define   DATAFILE     "Data/DBData"
#define   DCATFILE     "Data/DBCat"
#define   ROOMFILE     "Data/Rooms"
#define   EXITFILE     "Data/Exits"
#define   BANSFILE     "Data/Banished"
#define   LOGSFILE     "Data/Log"
#define   NOTCFILE     "Data/Board"
#define   HOSTFILE     "Data/Hosts"

char *crypt();
long ulimit();
int  errno;
time_t time();

struct eddata {
    int  user;
    char *editing;
    char *editname;
    char buffer[1024];
    char name[64];
};

struct  user {
    int     number;

    char    *name;
    char    title[80];
    char    ltitle[80];
    char    desc[256];
    int     flags;
    int     tempflags;
    int     age;
    int     lastlogin;
    int     lastlogout;

    char    prompt[64];
    char    cprompt[64];
    char    tprompt[64];
    char    myprompt[256];

    char    passwd[14];
    char    npasswd[14];
    int     oldpasswd;

    char    email[80];
    char    comment[80];
    char    ignoremsg[80];
    
    char    scapename[64];
    char    scapedesc[1024];
    int     scapeuser;
    int     invitenum[INVLENGTH];
    int     inviteflags[INVLENGTH];

    int     room;
    int     idletime;
    int     agetime;
    int     logintype;
    int     leaving;

    char    host[32];
    int     doing;
    int     olddoing;
    
    int     nextuser;
    int     lastuser;
    int     nextroom;
    int     lastroom;

    char    thischar;
    char    lastchar;
    int     charcount;
    int     localecho;
    int     ina[5];
    
    int     ednum;
    char    tty[32];
    int     cposn;
    int     plevel;
    int     ttyheight;
    int     ttywidth;

    char    objection[80];
    int     objecting;
    int     objected[OBJECTNUM];
};

#endif // HEADER_H
