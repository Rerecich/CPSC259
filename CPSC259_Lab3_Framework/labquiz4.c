#include <stdlib.h>
//#include "quiz4-v4.h"

/*
 *  RECURSIVELY swaps the positions of the first and fourth nodes, and
 *  second and third nodes in each group of four nodes in a linked list.
 *  Effectively, reverses the order of each group of four nodes.
 *  This must be achieved by reassigning/relinking the next attribute
 *  of the list nodes. You may NOT overwrite the data attribute of
 *  existing nodes and you may NOT malloc or free existing nodes.
 *
 *  You may assume that the list length is a multiple of 4.
 *
 *  THIS MUST BE ACHIEVED RECURSIVELY TO EARN FULL CREDIT.
 *  THERE WILL BE A MANUALLY-GRADED COMPONENT WORTH APPROXIMATELY
 *  50% CREDIT FOR THIS PROGRAMMING QUESTION. A RECURSIVE SOLUTION
 *  (CORRECT OR OTHERWISE) WILL AUTOMATICALLY EARN THE MANUAL COMPONENT.
 * 
 *  Example:
 *  before:  A - B - C - D - E - F - G - H - I - J - K - L
 *  after:   D - C - B - A - H - G - F - E - L - K - J - I
 *
 *  @param list - pointer to the first node in a linked list to be rearranged.
 *  @return - pointer to the front of the rearranged list.
 */

typedef struct node {
    int data;
    struct node* next;
} node;


struct node* Rearrange(struct node* list) {
  node* start = list;
  node* end = list + 3; //pointer to end of list
  
  
   //int i;
  int k;

    
  
    for (k = 4; k > 0; k--) { //will assign a to point to end, b to point to last added end, then c, etc. does not apply for last group
        (*list).next = (list + k);
        Rearrange(list);
        
        if (((list + 3).next) == NULL) {
        return list;
        }

        else {
            Rearrange(list);
        }
    }

    
    
   

   



}