#include <stdio.h>
#include "csapp.h"
#include <string.h>
#include "cache.h"

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

//The struct rangeRequest is used to handle HTTP Range Requests, which specifies a specific range of bytes to fetch
//Request Type: Request Action
//0 : not a valid range request
//1 : request bytes from r1 to r2
//2 : request bytes from r1 to the end
//3 : request the last r1 bytes
typedef struct rangeRequest {
  int requestType;
  int r1;
  int r2;
} rangeRequest;

void clientHandler(int fd);
int readReqHeaders(rio_t *rp);
int parse_url(char *url, char *host, char *port, char *path);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
int rangeProcess(char *buf, rangeRequest *rangePtr);

//Main function, derived from tiny.c int main(int argc, char **argv)
int main(int argc, char **argv)
{
  //Define variables
  int listenfd;
  int connfd;
  char host[MAXLINE];
  char port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  //Checks arguments passed from the command line
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]);
  while (1)
  {
    clientlen = sizeof(clientaddr);
    if ((connfd = accept(listenfd, (SA *)&clientaddr, &clientlen)) > -1) //line:netp:tiny:accept
    {
      if (getnameinfo((SA *) &clientaddr, clientlen, host, MAXLINE, port, MAXLINE, 0) < 0)
      {
        printf("Error with getnameinfo of %d\n", listenfd);
      }

      printf("Accepted connection from (%s, %s)\n", host, port);
      clientHandler(connfd);
      if (close(connfd) < 0)
      {
        printf("Error closing file %d\n", listenfd);
      }

    }
    else
    {
      printf("Error accepting fd %d\n", listenfd);
    }

  }
}

//clientHandler handles the client requests
//Derived from tiny.c function void doit(int fd)
void clientHandler(int fd)
{
  int serverfd;
  int length;
  char buf[MAXLINE];
  char method[MAXLINE];
  char url[MAXLINE];
  char version[MAXLINE];
  char data[MAXLINE];
  char path[MAXLINE];
  char host[MAXLINE];
  char request[MAXLINE];
  char port[MAXLINE];
  rio_t rio;
  rangeRequest range = {0, 0, 0};
  rangeRequest *rangePtr = &range;

  //reads request line and headers
  rio_readinitb(&rio, fd);
  if (!rio_readlineb(&rio, buf, MAXLINE)) //line:netp:doit:readrequest
  {
    clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
    return;
  }
  printf("%s", buf);
  sscanf(buf, "%s %s %s", method, url, version); //line:netp:doit:parserequest
  if (strcasecmp(method, "GET")) //line:netp:doit:beginrequesterr
  {
    clienterror(fd, method, "501", "Not Implemented", "Proxy does not implement this method");
    return;
  }

  // reads request header
  if (readReqHeaders(&rio) < 0)
  {
    clienterror(fd, method, "404", "Not found", "Proxy could not find the requested file");
  }

  //if the version is HTTP/1.1, change it to HTTP/1.0
  if(!strcasecmp(version, "HTTP/1.1"))
  {
    strcpy(version, "HTTP/1.0");
  }

  //parse the URL and return error mesage if parse fails
  if (parse_url(url, host, port, path) == -1)
  {
    clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
    return;
  }

  //process the HTTP range request
  if (rangeProcess(buf, rangePtr) < 0)
  {
    clienterror(fd, method, "416", "Requested Range Not Satisfiable", "Requested range could not be understood by the server");
    return;
  }

  //creates a request string
  sprintf(request, "GET %s %s\r\nHost: %s\r\n%sConnection: close\r\nProxy-Connection: close\r\n\r\n", path, version, host, user_agent_hdr);

  //establishes TCP connection with server
  if ((serverfd = open_clientfd(host, port)) < 0)
  {
    clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
    return;
  }

  //copies the request to serverfd
  rio_writen(serverfd, request, strlen(request));

  //asscoiates serverfd with buffer at address rio
  rio_readinitb(&rio, serverfd);

  //if the Range Request is of type 0 (defined above)
  if (rangePtr->requestType == 0)
  {
    //reads data by the max text buffer length until EOF, then rio_readnb returns 0
    while((length = rio_readnb(&rio, data, MAXLINE)))
    {
      if (length < 0)
      {
        clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
        return;
      }
      //writes data from data into fd
      if (rio_writen(fd, data, length) < 0)
      {
        clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
        return;
      }
    }
  }

  //if the Range Request is of type 1 (defined above)
  if (rangePtr->requestType == 1)
  {
    while((length = rio_readnb(&rio, data, MAXLINE)))
    {
      if (length < 0)
      {
        clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
        return;
      }
      rio_writen(fd, data, length);
    }
  }

  //if the Range Request is of type 2 (defined above)
  if (rangePtr->requestType == 2)
  {
    while((length = rio_readnb(&rio, data, MAXLINE)))
    {
      if (length < 0)
      {
        clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
        return;
      }
      rio_writen(fd, data, length);
    }
  }

  //if the Range Request is of type 3 (defined above)
  if (rangePtr->requestType == 3)
  {
    while((length = rio_readnb(&rio, data, MAXLINE)))
    {
      if (length < 0)
      {
        clienterror(fd, method, "400", "Bad Request", "Request could not be understood by the server");
        return;
      }
      rio_writen(fd, data, length);
    }
  }
  ///closes TCP connection with server
  close(serverfd);
}

/*
* readReqHeaders - read HTTP request headers
* from tiny.c
*/
//readReqHeaders reads the HTTP request header
//Derived from tiny.c void read_requesthdrs(rio_t *rp)
int readReqHeaders(rio_t *rp)
{
  char buf[MAXLINE];
  if (!rio_readlineb(rp, buf, MAXLINE))
  {
    return -1;
  }
  printf("%s", buf);
  while(strcmp(buf, "\r\n")) //line:netp:readhdrs:checkterm
  {
    rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);
  }
  return 0;
}

//parse_url parses URL info into url, host, port, and path
int parse_url(char *url, char *host, char *port, char *path)
{
  int *port_int;
  port_int = malloc(sizeof(int));
  char *pointer_1;
  char *pointer_2;

  //if URL does not begin with "http://", return -1
  if (strncasecmp(url, "http://", 7) != 0)
  {
    return -1;
  }

  //copy the URL exlcuding the "http://" into host
  strcpy(host, url + 7);

  //set a pointer to the first occurance of ":", "/", \r, \n, or \0 to find end of host
  pointer_1 = strpbrk(host, " : / \r \n \0");

  //set the default port to 80, as this is the typical port for designed for HTTP connections, and exclusivly uses TCP
  *port_int = 80;

  //if there is a ":" following the host, that is the port number, so we reassign the port # to this value
  if (*pointer_1 == ':')
  {
    *port_int = atoi(pointer_1 + 1);
  }

  //find the first occurance of "/" after the "http://" to locate the start of the path
  pointer_2 = strpbrk(host, "/");

  //if there is no path, then concatenate a null terminator t0 make it blank
  if (pointer_2 == NULL)
  {
    path[0] = '\0';
  }

  //if there is a path name, copy it to path
  else
  {
    strcpy(path, pointer_2);
  }

  //add a null terminator at the end of the host
  *pointer_1 = '\0';
  sprintf(port,"%d",*port_int);
  return 0;
}

//clienterror returns error messages to the client
//Derived from tiny.c void clienterror(int fd, char *cause, char *errnum), char *shortmsg, char *longmsg)
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
  char buf[MAXLINE];
  char body[MAXBUF];
  //Builds HTTP response body
  sprintf(body, "<html><title>Proxy Error</title>");
  sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
  sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
  sprintf(body, "%s<hr><em>Proxy </em>\r\n", body);
  //Builds HTTP response
  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  sprintf(buf, "%sContent-type: text/html\r\n", buf);
  sprintf(buf, "%sContent-length: %d\r\n\r\n", buf, (int)strlen(body));
  rio_writen(fd, buf, strlen(buf));
  rio_writen(fd, body, strlen(body));
}

//processes HTTP range
int rangeProcess(char *buf, rangeRequest *rangePtr)
{
  char *strtPtr; //points to the first occurance of "bytes="
  int r1;
  int r2;
  if ((strtPtr = strstr(buf, "bytes=")) != NULL)
  {
    strtPtr = strtPtr + 6; //relocates pointer to after "="
    if (sscanf(strtPtr, "-%u", &r1) == 1)
    {
      rangePtr->requestType = 3;
      rangePtr->r1 = r1;
      return 3;
    }
    else if (sscanf(strtPtr, "%u-%u",&r1, &r2) == 2)
    {
      rangePtr->requestType = 1;
      rangePtr->r1 = r1;
      rangePtr->r2 = r2;
      return 1;
    }
    else if (sscanf(strtPtr, "%u-",&r1) == 1)
    {
      rangePtr->requestType = 2;
      rangePtr->r1 = r1;
      return 2;
    }
    else
    {
      rangePtr->requestType = 0;
      return -1;
    }
  }
  return 0;
}
