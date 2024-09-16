#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <time.h>
#include <unistd.h>
#include <sys/types.h> // needed?

void timestr(time_t t, char *s);
void ltimestr(time_t t, char *s);
void pstatus(const char *msg);
void setupsocket(void);
int mailinit(void);
void initfiles(void);
void loadrooms(void);
void loadexits(void);
void undumphostlist(void);
void undumpnotices(void);
void Logfile(const char *msg);
void closeup(void);
void fileremake(void);

#endif // FUNCTIONS_H
