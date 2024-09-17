/**
 * @file main.c
 * @brief Main entry point and initialization for the chat system.
 *
 * This file contains the main() function which initializes the chat system,
 * sets up signal handling, and starts the main server loop. It also includes
 * utility functions for logging and debug output.
 */

#include "header.h"
#include "globals.h"
#include "telnet.h"
#include "functions.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

/****************************************************************************
  FUNCTION - exit_nicely()
  Calls closeup then exit()s. This function is purely here for use with
  signal trapping.
 ****************************************************************************/

void exit_nicely()
{
    closeup();
    exit(0);
}

void debug_log(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    time_t now = time(NULL);
    char timestamp[26];
    ctime_r(&now, timestamp);
    timestamp[24] = '\0';  // Remove newline
    
    FILE *log_file = fopen("house_debug.log", "a");
    if (log_file) {
        fprintf(log_file, "[%s] ", timestamp);
        vfprintf(log_file, format, args);
        fprintf(log_file, "\n");
        fclose(log_file);
    }
    
    va_end(args);
}

void signal_handler(int signum) {
    fprintf(stderr, "Received signal %d\n", signum);
    exit(1);
}

/****************************************************************************
  FUNCTION - main(argc,argv)
  Starts up the house in one of the following ways....
  No arguments - Runs on port Portnumber.
  R            - Remakes the database then dies.
  port         - Runs on requested port.
  port D       - Runs on requested port but doesnt detatch.
  Logs its startup if the actual socket code gets going......
 ****************************************************************************/

int main(int argc, char *argv[]) {
    signal(SIGHUP, signal_handler);
    int i;
    int debug_mode = 0;
    int dts;
    Firstuser=-1;
/*    if (strlen(argv[0])<79) {
	int siz,i;
	char *args;
	char **argps;
	siz=argc*4+84;
	for (i=1;i<argc;i++)
	    siz+=(strlen(argv[i])+1);
	argps=(char**)malloc((unsigned)siz);
	args=(char*) (argps+(argc*4)+4);
	siz=80;
	for (i=0;i<79;i++) args[i]='*';
	args[79]=0;
	argps[0]=args;
	argps[argc]=(char*)0;
	for (i=1;i<argc;i++) {
	    strcpy(&args[siz],argv[i]);
	    argps[i]=&args[siz];
	    siz+=(strlen(argv[i])+1);
	}
	execvp(argv[0],argps);
    } - TODO - What the heck is this above?!
    */ 

    debug_log("Program started with %d arguments", argc);

    for (i = 0; i < MAXROOMS; i++)
	Roomuser[i] = -1;

    Portnum = Portnumber;
    if (argc > 1) {
        i = atoi(argv[1]);
        if (i > 0)
            Portnum = i;
    }

    if (argc>1)
	if (strcmp(argv[1], "help") == 0) {
            printf("Usage: %s [port] [D]\n", argv[0]);
            printf("  port: Optional port number (default: %d)\n", Portnumber);
            printf("  D: Run in debug mode (don't detach)\n");
            exit(0);
        }
    if (argc > 2 && argv[2][0] == 'D')
        debug_mode = 1;

    debug_log("Port number set to %d", Portnum);
    debug_log("Debug mode: %s", debug_mode ? "ON" : "OFF");

    printf("Cheeseplant`s house version 3.0\n");
    printf("Starting code up on port %d\n",Portnum);
    printf("Maximum login channels set to %d\n",MOST);
    Lasthour=-1;
    Ipmonitor=-1;
    Lassusers=0;
    housestatus=0;
    houseflags=0;
    Maxlassusers=MAXDAYLASS;
    printf("Maximum LASS logins during day set to   %d\n",MAXDAYLASS);
    printf("Maximum LASS logins during night set to %d\n",MAXNIGHTLASS);
    printf("Daytime starts at   %-.2d00 Hrs\n",DAYTIME);
    printf("Nighttime starts at %d00 Hrs\n",NIGHTTIME);
    printf("Maximum users allowed in resident list is %d\n",MAXUSERS);
    printf("Trapping signals.....\n");
    if ((signal(SIGINT,exit_nicely))==SIG_ERR) {
        (void) printf("Error: Signals handling failure!\n");
        exit(1);
    }
    if ((signal(SIGPIPE,SIG_IGN))==SIG_ERR) {
        (void) printf("Error: Signals handling failure!\n");
        exit(1);
    }
#ifndef __CYGWIN__
    (void) ulimit(4,256L);
#endif
    (void) printf("File descriptor table size %d\n",dts=getdtablesize());
    if (dts<256) exit(0);
    if (argc>1) {
	if (argv[1][0]=='R') {
	    (void) printf("Remaking database for you......\n");
	    initfiles();
	    (void) time((time_t*)&ti);
	    fileremake();
	    (void) printf("Done...\n");
	    exit(0);
        }
    }

    debug_log("About to fork");

    if (!debug_mode) {
	pid_t pid = fork();
        if (pid < 0) {
            debug_log("Fork failed");
            exit(1);
        } else if (pid > 0) {
	    printf("Startup code forked and exiting.....\n");
            debug_log("Parent process exiting");
	    exit(0);
	}
        // Child continues
        debug_log("Child process continuing");
        setsid();
	fflush(stdout); fflush(stdin);
	for (i = getdtablesize() - 1; i >= 0; i--)
	    close(i);
#ifndef __CYGWIN__
	if ((i = open("/dev/tty",O_RDWR)) >=0) {
	    ioctl(i,TIOCNOTTY,(char *)0);
	    close(i);
        }
#else
	setpgrp();
#endif
    } else {
        printf("Running in debug mode, not forking\n");
        debug_log("Running in debug mode, not forking");
    }
    argles=argv[0];
    printf("Before first pstatus\n");
    debug_log("Cheeseplants House Startup: Initialising");
    printf("After first pstatus\n");
    for (i=0;i<MAXEDITS;i++) edits[i].user=-1;
    for (i=0;i<MAXUSERS;i++) 
	cnames[i][0]=0,unames[i][0]=0,nnext[i]=-1,nlast[i]=-1;
    for (i=0;i<MAXNOTICES;i++) noticenum[i]=-1,noticemsg[i][0]=0;
    for (i=0;i<256;i++) nhash[i]=-1;
    debug_log("Cheeseplants House Startup: Socket");
    setupsocket();
    debug_log("Cheeseplants House Startup: Mail");
    mailinit();
    debug_log("Cheeseplants House Startup: Files");
    initfiles();
    debug_log("Cheeseplants House Startup: Rooms");
    loadrooms();
    debug_log("Cheeseplants House Startup: Exits");
    loadexits();
    debug_log("Cheeseplants House Startup: Hosts");
    undumphostlist();
    debug_log("Cheeseplants House Startup: Notices");
    undumpnotices();
    time((time_t*)&ti);
    timestr(ti,stringp);
    snprintf(stringo, sizeof(stringo), "%s: *\n", stringp);
    Logfile(stringo);
    debug_log("Cheeseplants House Startup: Begin");
    printf("Before dosocket()\n");
    dosocket();
    printf("After dosocket()\n");
    return 0;
}

