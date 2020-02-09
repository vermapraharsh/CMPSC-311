/*
 * author: Praharsh Verma
 * email: pbv5036@psu.edu
 * parse_url.c for CMPSC 311 Fall 2019
 * last updated: 11/20/2019
 */
#include "parse_url.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

// returns 1 if the url starts with http:// (case insensitive)
// and returns 0 otherwise
// If the url is a proper http scheme url, parse out the three
// components of the url: host, port and path and copy
// the parsed strings to the supplied destinations.
// Remember to terminate your strings with 0, the null terminator.
// If the port is missing in the url, copy "80" to port.
// If the path is missing in the url, copy "/" to path.

int parse_url(const char *url, char *host, char *port, char *path) {
    //initilize varibles
    char *portNum;
    char *tempPointer1;
    char *tempPointer2;
    int *portNumTemp;
    portNumTemp = malloc(sizeof(int));

    //check if URL starts with http://
    if (strncasecmp(url, "http://", 7) != 0) {
      return 0;
    }

    //copies all url info past http:// into host
    strcpy(host, url + 7);
    *portNumTemp = 80;

    //points to the end of the host name
    tempPointer1 = strpbrk(host, " : / \r \n \0");

    //if there is nothing in the URL past the hostname, then fill in defualt
    //values for port and path
    if(tempPointer1 == NULL)
    {
      sprintf(port,"%d",*portNumTemp);
      strcpy(path, "/");
      return 1;
    }

    //sets pointer to start of the port# and passes it to port
    if (*tempPointer1 == ':') {
      portNum = tempPointer1 + 1;
      int holder = atoi(tempPointer1 + 1);
      char portStr[12];
      sprintf(portStr, "%d", holder);
      portNum = portStr;
      strcpy(port, portNum);
    }

    //in the case that there is no port, must sprintf to port to avoid
    //segmenation fault
    else
    {
      sprintf(port,"%d",*portNumTemp);
    }

    //finds start of the pathname
    tempPointer2 = strpbrk(host, "/");

    //if there is no pathname define one by default
    if (tempPointer2 == NULL) {
      strcpy(path, "/");
    }

    //else just copy the pathname to path
    else {
      strcpy(path, tempPointer2);
    }

    //adds null terminator to end of hostname
    *tempPointer1 = '\0';
    return 1;
}
