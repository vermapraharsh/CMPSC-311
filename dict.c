/*
 * author: Praharsh Verma
 * email: pbv5036@psu.edu
 * dict.c for CMPSC 311 Fall 2019
 * last updated: 10/15/2019
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

// count number of keys in a dict.
int countKeys(const dictNode *dict)
{

  int keyCount = 0;                                      //starts node count at 0
  const dictNode *node = dict;                        //defines node as type dictNode  
  
  for(node = dict; node != NULL; node = node->next)   //loops through all the nodes of dictNode, and adds 1 for every entry
  
  {

   keyCount = keyCount + 1;
  
  }
  
  return keyCount;

}

// given a key, look up its corresponding value in the
// dictionary, returns -1 if the value is not in the dictionary.
// your search for key should end when the key in the next node
// is bigger than the lookup key or you reached the end of the
// list.
int lookupKey(const dictNode *dict, const char *key)
{
  
  if(dict == NULL) //checks to see if dict is empty so we don't run into a segmentation error
  {

    return -1; //if empty, we immediatly return -1
  }

  const dictNode *node = dict; //we create an object of the dict class

  if(strcmp(node->key, key) == 0) //comparing the current node key with the inputted key, if they are the same strcmp returns 0

  {

    return node->value; //if they are the same, we have found the key, and we can return its value

  }

  else if(strcmp(node->key, key) > 0) //if strcmp returns a positive integer, that means the current node key is larger than the
                                      //inputted key, and we must end our search  

  {

    return -1; //therefore we return -1

  }

  else //strcmp returns a negative integer meaning that our current node key is less than the inputted key, and we can continute
       //the search

  {

    while(node->next != NULL) //we must ensure that we do not use a pointer pointing to a null value to avoid segmentation error 

    {
      node = node->next; //now we iterate through the dictionary nodes

      if(strcmp(node->key, key) == 0) //if strcmp returns 0, we have found our key

      {

        return node->value; //therefore we can return the value at this node

      }

      if(strcmp(node->key, key) > 0) //if strcmp returns a positive integer, the key at the current node is larger than the key
                                     //we inputted, we must end the search

      {

        return -1; //we return -1 to show the specified key was not in the dictionary

      }

    }

  }

  return -1; //if all searches fail, we must return -1 to show the key was not present in the dictionary

}
// delete the node in a dict with given key, return the value of
// the deleted node if it was found, return -1 if it wasn't found.
int deleteKey(dictNode **dict, const char *key)
{

  dictNode *currentNode = *dict; //create object of dict
  dictNode *previousNode = NULL; //previousNode is initilized as NULL
 
  while(currentNode != NULL) //statement to ensure we are not making a call to a NULL pointer causing a segmentation error
 
  {
      
    if(strcmp(currentNode->key,key) != 0) //if the strcmp function returns any other value than 0, the strings are not equal
   
    {
      if(strcmp(currentNode->key,key) > 0) //if the strcmp function returns a positive integer, it is because the key in the 
                                           //current node is greater than entered key value
      {
       
        return -1; //therefore we return -1

      }

    }

    else

    {

      break; //if strcmp returns 0, the strings are equal, and we should exit the loop

    }


    previousNode = currentNode; //move the previous node in the dictionary to the next value
    currentNode = currentNode->next; //moves current node to next
  
  }

  if(currentNode == NULL) //if the currentNode is NULL, we have reached the end of the dictionary
 
  {
 
    return -1; //therefore we return -1 as the key was not in the dictionary
 
  }
 
  else
  
  {
  
    int val = currentNode->value; //stores the current nodes value in int val for use later
   
    if(currentNode == *dict)
   
    {
   
      *dict = (*dict)->next;
   
    }
   
    else
   
    {
   
      previousNode->next = currentNode->next;
   
    }
 
    return val;

  }

}
// given a key/value pair, first lookup the key in the dictionary,
// if it is already there, update the dictionary with the new
// value; if it is not in the dictionary, insert a new node into
// the dictionary, still make sure that the key is in alphabetical
// order.
// IMPORTANT: When creating a new node, make sure you dynamically
// allocate memory to store a copy of the key in the memory. You
// may use strdup function. DO NOT STORE the input key from the 
// argument directly into the node. There is no guarantee that key
// pointer's value will stay the same. 
// YOU MUST KEEP THE ALPHABETICAL ORDER OF THE KEY in the dictionary.
void addKey(dictNode **dict, const char *key, int value)
{
  
  dictNode *topNode = *dict; //initializes the top node as object dict
  dictNode *previousNode = NULL; //initializes previous node to NULL
  dictNode *currentNode = topNode; //initializes current node to the top of the structure, the top node
 
  dictNode *sampleDict = (dictNode *) malloc(sizeof(dictNode)); //creates a memory allocated object sampleDict in which to perfo
                                                                //rm the calculations
  sampleDict->key = strdup(key); //duplicates the inputted key value into the sampleDict object 
  sampleDict->value = value; //sets the value of sampleDict with the inputted value 
  sampleDict->next = NULL; //since we are starting at the top of the dictionary, the next node must be NULL
 
  if(topNode == NULL) //we must check if the topNode is NULL to avoid causing a segmentation error
  
  {
    *dict = sampleDict; //the pointer is set to the sampleDict object
    return; //we exit the function because the topNode was empty
  
  }
  
  while(currentNode != NULL) //we must now iterate through the dictionary
  
  { 
  
    if(strcmp(key, currentNode->key) > 0) //if strcmp returns a positive integer, the inputted key value is larger than th
                                          //e key at the current node 
    {
    
      previousNode = currentNode; //if that is the case, then we can continue out travesral of the dictionary 
      currentNode = currentNode->next;//we move the current and previous nodes up one position
    
    }
    
    else if(strcmp(key, currentNode->key) == 0) //if strcmp value is 0, then the key and currentnode key are the same
    
    {

      currentNode->value = value; //this means we can set the currentnode value to the value the user inputted for that key
      return;
    
    }

    else
    
    {         //we break the loop here since this else statement is only reached if strcmp returns a negative integer value, which
              //means that the value of key is smaller than the value of the currentnode's key, and we must exit our search
      break;
                                                                                                                                      }
  }

  if(currentNode == topNode) //in the condition that the currentNode and topNode are equal, this means we have traversed to the e       //nd of the dictionary
   {
    
    sampleDict->next = topNode; //we set the next value of the sampleDict object to topNode
    topNode = sampleDict; //topNode then becomes sampleDict

   }

   else //in the case they are not equal, we must set the previousNode window up, and sampleDict window up as well

   {

    previousNode->next = sampleDict;
    sampleDict->next = currentNode;
   
   }
   
   *dict = topNode; //finally we establish that the dict pointer is pointing to the memory address of the topNode
   
}
