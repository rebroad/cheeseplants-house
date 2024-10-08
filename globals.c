#include "globals.h"
#include <time.h>

struct tm *whattime;
int nnext[MAXUSERS], nlast[MAXUSERS];
int nhash[256];
char unames[MAXUSERS][16];
char cnames[MAXUSERS][16];
int housestatus;
int hoststatus[MAXHOSTS];
struct in_addr hostlist[MAXHOSTS];
int lastshout[MAXUSERS];
int shouts[MAXUSERS];
char parv[4][256];
char parr[4][256];
time_t ti;
int Roomuser[MAXROOMS];
struct eddata edits[MAXEDITS];
char noticemsg[MAXNOTICES][64];
int noticenum[MAXNOTICES];
char *argles;
int Maxlassusers;
int houseflags;
int Lassusers;
int Ipmonitor;
int Lasthour;
char hostlabel[MAXHOSTS][20];
int lasswait;
int lasstries;
int lasschecktime;
char Roomdesc[MAXROOMS][1024];
char Roomname[MAXROOMS][64];
char capstr[64];
char Roomexit[MAXROOMS][16];
int parc;
int lasttick;
int lasstime;
int togeor;
int togand;
int Firstuser;
struct user users[MOST];
int Portnum;
char stringo[MAX_STRING_LENGTH];
char stringp[MAX_STRING_LENGTH];
char stringq[MAX_STRING_LENGTH];
char stringr[MAX_STRING_LENGTH];
int Exitflags[MAXEXITS];
int Exitto[MAXEXITS];
int Exitfrom[MAXEXITS];
