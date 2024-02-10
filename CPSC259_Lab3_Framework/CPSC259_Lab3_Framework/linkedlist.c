/*
 File:         linkedlist.c
 Purpose:      Implements the linked list functions whose prototypes
               are declared in the linked_list.h header file
 Author:       Sarah Rerecich
 Student #s:   65693236
 CWLs:         sarahr25
 Date:         Nov. 2023
 */

#define _CRT_SECURE_NO_WARNINGS

 /* Preprocessor directives */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/******************************************************************
 PLEASE EDIT THIS FILE

 Comments that start with // should be replaced with code
 Comments that are surrounded by * are hints
 ******************************************************************/

 /*
  Returns a pointer to a new, empty linked list of struct node.
  PRE:       NULL (no pre-conditions)
  POST:      NULL (no side-effects)
  RETURN:    A pointer to a new, empty linked list of struct node (NULL)
  */
node* create_linked_list()
{
    return NULL;

}

/*
 Returns a dynamically allocated struct node that contains the specified
 struct airplane. Note that the string attributes of the newly created
 node's struct airplane must be specially copied (refer to lab 2).
 The node's next pointer doesn't point to anything
 PARAM:     plane, a struct airplane
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    A pointer to a dynamically allocated struct node a) that contains
            the specified struct airplane, and b) whose next pointer points to NULL
 */
node* create_node(airplane plane)
{
    node* new_node = (node*)malloc(sizeof(node)); 
   // new_node = NULL;
    
    new_node->plane.flight_number = plane.flight_number;
    
    new_node->plane.city_origin = _strdup(plane.city_origin);
    new_node->plane.city_destination = _strdup(plane.city_destination);
    
    new_node->plane.priority = plane.priority;
    new_node->plane.maximum_speed_kph = plane.maximum_speed_kph;
    new_node->plane.cruising_altitude = plane.cruising_altitude;
    new_node->plane.capacity = plane.capacity;

    new_node->next = NULL;

    return new_node;
}

/*
 Prepends a struct node passed as a parameter to the list passed as a
 parameter, and returns a pointer to the result.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     new_node is a pointer to a struct node
 PRE:       new_node is not null
 POST:      The specified struct node is added to the beginning of the list
            and its next pointer points to the node that used to be first
 RETURN:    A pointer to a linked list which contains all of the nodes
            of the list passed as a parameter, plus a prepended node
 */
node* prepend_node(node* list, node* new_node)
{
    new_node->next = list;
    
    return new_node;
}

/*
 Deletes the first struct node in the specified list, and returns a pointer to
 the shortened list. Be aware of nested allocations!
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL
 POST:      The list passed as a parameter has one fewer node, and the dynamically
            allocated memory which contained that removed node has been freed
 RETURN:    IF the list is empty
            THEN NULL
            ELSE a pointer to the shortened list
 */
node* delete_node(node* list)
{
    struct node* temp = (node*)malloc(sizeof(node));
    temp = NULL;

    if (list == NULL) {
        free(temp);
        return NULL;
    }
    
    temp = list;
    list = list->next;
    free(temp);

    return list;
    
}

/*
 Returns the number of nodes in the specified linked list of struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      NULL (no side-effects)
 RETURN:    The length of the specified list, an int
 */
int get_length(node* list)
{
    int length = 0;
    
    if (list == NULL) {
        return length;
    }

    while (list) {
        length++;

        if (list->next == NULL) {
            return length;
        }

        else {
            list = list->next;
        }
    }

    return length;
}

/*
 Deletes an entire list.  This function iterates along a list and deallocates the
 memory containing each struct node.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The memory containing all of the nodes in the list has been freed
 RETURN:    an empty list (NULL)
 */
node* delete_list(node* list)
{
    struct node* temp = (node*)malloc(sizeof(node));
    temp = list;

        while (list) {
            temp = list->next;
            free(list);
            list = temp;
        }

    free(temp);

  return list;
}

/*
 Prints the data stored in a node.  For the struct airplane in the node,
 prints the fields on separate lines.  For each field, prints the field name
 and the field value.  For the pointer, prints "Link = NULL\n" if the pointer points
 to null, else prints "Link points to address xxx\n", where xxx is the pointer address
 in hexademical.
 If node_to_print is NULL, prints "The node is empty\n".
 PARAM:     node_to_print is a pointer to a (possibly null) struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about node_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_node(node* node_to_print)
{
    
    
}

/*
 Prints the data stored in all nodes in the specified list to print.
 For each node, prints the data inside the node the same way that it
 is printed by print_node.  If the list is empty, a suitable message
 is printed to standard output.
 PARAM:     node_to_print is a pointer to a (possibly empty) linked list of
            struct node
 PRE:       NULL (no pre-conditions)
 POST:      Information about list_to_print has been printed to standard output
 RETURN:    NULL
 */
void print_list(node* list_to_print)
{
  // Insert your code here

}

/*
 Reverses a list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PRE:       NULL (no pre-conditions)
 POST:      The order of the nodes in the list passed as a parameter has been
            reversed
 RETURN:    a list of struct node that is the reverse of the list passed as a
            parameter
 */
node* reverse(node* list)
{
    node* prev = NULL;;
    node* curr = list;
    node* next = NULL;

    int i = 0;
    int length = get_length(list);

    if (length <= 1) {
        return list;
    }
   

   
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;

    }

    list = prev;
    //free(curr);
    //free(prev);
    //free(next);
    return list;

}

/*
 Removes every node from the list which contains an airplane destined for
 the city name passed in the second parameter.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     destination_city is a pointer to a null-terminated array of char
 PRE:       NULL (no pre-conditions)
 POST:      Any struct node in the list which contains an airplane struct
            destined for the destination_city is removed from the list, and
            the memory deallocated
 RETURN:    a list of struct node that does not contain any struct node that
            has an airplane destined for the destination_city
 */
node* remove_from_list(node* list, char* destination_city)
{
    //struct node* temp = (node*)malloc(sizeof(node));
    //temp = NULL;
    //
    //if (list == NULL) {
    //    //free(temp);
    //    return NULL;
    //}
    //
    ////whether or not th
    //
    ////if the city does match, the current node is freed 
    // if (list->plane.city_destination == destination_city) {
    //        temp = list->next;
    //        free(list);
    //        return temp;
    // }
    //
    // list->next = remove_from_list(list->next, destination_city);
    // return list;
    /////////////////////////////////////////////////
  // struct node* temp = (node*)malloc(sizeof(node));
  // temp = NULL;
  //
  // if (list == NULL) {
  //     free(temp);
  //     return NULL;
  // }
  //
  // temp = list;
  // list = list->next;
  // free(temp);
  //
  // return list;


    struct node* current = list;
    struct node* prev = NULL;
   // struct node* head = list;

    //pointer traversal
    while (current != NULL && strcmp(current->plane.city_destination, destination_city) != 0) {
        prev = current;
        current = current->next;
    }

    //unchanged
    if (current == NULL) {
        //free(curr);
        return list;
    }

    //first node
    if (prev == NULL) {
        list = current->next;
    }

    else {
        prev->next = current->next;
        //free(prev);
    }

    //current = NULL;
    free(current);
    current = NULL;
    //free(prev);

    //list = head;
    return list;
}

/*
 Returns a reference to the nth node (but does not remove it ) in the
 specified list.  If the list is too short, returns NULL.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list
            THEN a pointer to the nth node
            ELSE NULL
 */
node* retrieve_nth(node* list, int ordinality)
{
    int i = 0;
    struct node* temp;

    temp = list;


    while (temp) {
        if ((i+1) == ordinality) {
            return temp;
        }
        else {
            i++;
            temp = temp->next;
        }
    }

    free(temp);
    return NULL;
}

/*
 Inserts the specified node into the specified list of nodes at the specified
 ordinality.  For example, if ordinality = 1, this is a simple prepend_node
 operation.  If ordinality = 3, then when this function is finished, the third
 node in the list will be the node_to_insert.  If the ordinality = the length
 of the list + 1, then the node_to_insert is appended to the end of the list.
 If the ordinality > 1 + length of the list, the function returns a pointer
 to the unchanged list.
 PARAM:     list is a pointer to a (possibly empty) linked list of struct node
 PARAM:     ordinality is an integer
 PRE:       ordinality > 0
 PRE:       node_to_insert is NEVER a null (it is always a correct node pointer)
 POST:      NULL (no side-effects)
 RETURN:    IF ordinality <= length of list + 1
            THEN a pointer to the list which contains the node_to_insert in the
      correct location
            ELSE a pointer to the unchanged list
 */
node* insert_nth(node* list, node* node_to_insert, int ordinality)
{
    int i = 0;
    
    struct node* head;

    head = list;

    if (ordinality == 1) {
        node_to_insert->next = list;
        return node_to_insert;
    }

    else {
        while (list) {
            if ((i+2) == ordinality) {
                node_to_insert->next = list->next;
                list->next = node_to_insert;
                return head;
            }
            else {
                i++;
            }

            list = list->next;
        }
    }

    return head;
}