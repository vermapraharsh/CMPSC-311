#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csapp.h"
#include "cache.h"


/* cache_init initializes the input cache linked list. */
void cache_init(CacheList *list) {
  list->size = 0;
  list->first = NULL;
  list->last = NULL;
}

/* cache_URL adds a new cached item to the linked list. It takes the
* URL being cached, a link to the content, the size of the content, and
* the linked list being used. It creates a struct holding the metadata
* and adds it at the beginning of the linked list.
*/
void cache_URL(const char *URL, const char *headers, void *item, size_t size, CacheList *list) {
  CachedItem *temp;
  size_t test;
  CachedItem *newNode;
  if(size > MAX_OBJECT_SIZE){
    return;
  }
  else{
    newNode->url = strdup(URL);
    newNode->headers = strdup(headers);
    newNode->item_p = (void *) malloc(sizeof(item));
    newNode->size = (int *) malloc(sizeof(size));
    if(list->first == NULL)
    {
      list->first = newNode;
      list->last = newNode;
    }
    else if(list->size == list->last)
    {
      newNode->next = list->last;
      newNode->prev = NULL;
      list->last->prev = newNode;
      list->first = newNode;
      list->last->next = NULL;
    }
    else{
      if(list->size + newNode->size > MAX_CACHE_SIZE){
        while(list->size + newNode->size > MAX_CACHE_SIZE){
          test = list->last->size;
          temp = list->last;
          list->last = list->last->prev;
          list->last->next = NULL;
          temp->prev = NULL;
          list->size -= test;
        }
      }
      newNode->next = list->first;
      newNode->prev = NULL;
      list->first->prev = newNode;
      list->first = newNode;
    }
  }
  list->size += newNode->size;
}




/* find iterates through the linked list and returns a pointer to the
* struct associated with the requested URL. If the requested URL is
* not cached, it returns null.
*/
CachedItem *find(const char *URL, CacheList *list) {
  CachedItem *current;
  current = list->first;
  if(current->url == URL){
    return current->url;
  }
  else{
    while(current->next != NULL){
      current = current->next;
      if(current->url == URL){
        return current->url;
      }
    }
  }
  return NULL;
}


/* frees the memory used to store each cached object, and frees the struct
* used to store its metadata. */
void cache_destruct(CacheList *list) {
  CachedItem *current;
  CachedItem *temp;
  current = list->first;
  while(current->next != NULL)
  {
    temp = current->next;
    free(current);
    current = temp;
  }
  free(current);
}
