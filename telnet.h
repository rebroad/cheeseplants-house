#include "header.h"

extern int      bufpos[MOST];
extern char     buffer[MOST][256];
extern int      tstate[MOST];
extern int      tflags[MOST];
extern int      tsposn[MOST];
extern char     tsbuff[MOST][32];
extern int      through[MOST];
extern int      startthro[MOST];

extern int      rdfiled[8],readmask[8];
extern struct   sockaddr_in myaddr;
extern struct   sockaddr_in connectaddress;

void dosocket(void);
