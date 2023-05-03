

// Throughout the comments of this library the term 'llist' is used, which stands for Linked List


#ifndef STRLIST_H
#define STRLIST_H

// Dependencies

#include <stdio.h>          // printf
#include <stdlib.h>         // calloc, realloc, malloc, free, NULL
// string.h is used, so that this file is independent of strlib.h
#include <string.h>         // strlen
#include <stdarg.h>         // va_arg, va_start, va_list, va_end


// Datatypes

// Node Datatype (= Element of a Linked List)
typedef struct Node {
    struct Node *next;
    char *content;
} node;

// String Llist Datatype (= Linked List for Strings)
typedef struct {
    node *header;
    int length;
    int size;
} str_llist;



// Function Prototypes
// Total amount of functions in strlist.h: 11 (11 defined)

void StrListRawInit(str_llist *a);                      // can also be used to clear a llist
void StrListPush(str_llist *a, char *text);
void StrListPrint(str_llist *a);
void StrListPop(str_llist *a);
void StrListRemoveAt(str_llist *a, int idx);
void StrListInsert(str_llist *a, int idx, char *text);
char *StrListGetAt(str_llist *a, int idx);
void StrListExtend(str_llist *a, str_llist *b);
void StrListInit(str_llist *a, char *texts, ...);
char *StrListMergeContent(str_llist *a);
int StrListIndexOf(str_llist *a, char *text);

// Functions

/**
 * Initializes a Llist without any values / elements (can also clear a llist)
 * @param a ... the llist to initialize
 */
void StrListRawInit(str_llist *a){
    a -> size = 0;
    a -> length = 0;
    a -> header = NULL;
}

/**
 * Appends a string as an element of the llist
 * @param a ... llist to append to
 * @param text ... string to append
 */
void StrListPush(str_llist *a, char *text){
    node *new_node = (node *) malloc(sizeof(node));
    new_node -> next = NULL;
    new_node -> content = text;
    if (a -> header == NULL){
        a -> header = new_node;
    }
    else{
        node *ptr = a -> header;
        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = new_node;
    }
    a -> length++;
    a -> size += strlen(text);
}

/**
 * Prints out the content of the llist
 * @param a ... llist to print
 */
void StrListPrint(str_llist *a){
    node *ptr = a -> header;
    printf("[");
    while (ptr != NULL){
        if (ptr -> next == NULL){
            printf("%s", ptr -> content);
        }
        else{
            printf("%s, ", ptr -> content);
        }
        ptr = ptr -> next;
    }
    printf("]\n");
}

/**
 * Removes the last element of the given llist
 * @param a ... llist to remove from
 */
void StrListPop(str_llist *a){
    if (a -> length == 0){return;}
    node *ptr = a -> header;
    while (1){
        if (ptr -> next -> next == NULL){break;}
        ptr = ptr -> next;
    }
    a -> size -= strlen(ptr -> next -> content);
    a -> length--;
    free(ptr -> next);
    ptr -> next = NULL;
}

/**
 * Removes the element at index 'idx' from the given llist
 * @param a ... llist to remove from
 * @param idx ... index to remove at
 */
void StrListRemoveAt(str_llist *a, int idx){
    if (a -> length == 0 || idx > a -> length || idx < 0){return;}
    node *ptr = a -> header;
    int prevLen;
    if (idx > 0){
        for (int i = 0; i < idx - 1; i++){
            ptr = ptr -> next;
        }
        prevLen = strlen(ptr -> next -> content);
        node *nextNode = ptr -> next -> next;
        free(ptr -> next);
        ptr -> next = nextNode;
    }
    else{
        prevLen = strlen(a -> header -> content);
        ptr = ptr -> next;
        free(a -> header);
        a -> header = ptr;
    }
    a -> length--;
    a -> size -= prevLen;
}

/**
 * Inserts a string at index 'idx' into the llist 'a'
 * @param a ... llist to insert to
 * @param idx ... index to insert at
 * @param text ... string to insert
 */
void StrListInsert(str_llist *a, int idx, char *text){
    if (idx > a -> length || idx < 0){return;}
    node *ptr = a -> header;
    if (idx > 0){
        for (int i = 0; i < idx - 1; i++){
            ptr = ptr -> next;
        }
        node *newNode = (node *) malloc(sizeof(node));
        newNode -> content = text;
        newNode -> next = ptr -> next;
        ptr -> next = newNode;
    }
    else{
        node *newNode = (node *) malloc(sizeof(node));
        newNode -> content = text;
        newNode -> next = a -> header;
        a -> header = newNode;
    }
    a -> length++;
    a -> size += strlen(text);
}

/**
 * Gets the string at index 'idx'
 * @param a ... llist to get from
 * @param idx ... index to get from
 * @return string at index 'idx'
 */
char *StrListGetAt(str_llist *a, int idx){
    node *ptr = a -> header;
    for (int i = 0; i < idx; i++){
        ptr = ptr -> next;
    }
    return ptr -> content;
}

/**
 * extends a llist by another
 * @param a ... llist to extend
 * @param b ... llist to expand with
 */
void StrListExtend(str_llist *a, str_llist *b){
    node *ptr = a -> header;
    while (ptr -> next != NULL) {
        ptr = ptr -> next;
    }
    ptr -> next = b -> header;
    a -> length += b -> length;
    a -> size += b -> size;
}

/**
 * Initializes a llist with values (can also overwrite a existing llist's content)
 * DO NOT: pass the amount of arguments for 'texts'
 * DO    : pass NULL as the last argument
 * @param a ... llist to initialize
 * @param texts ... strings to initialize with
 */
void StrListInit(str_llist *a, char *texts, ...){
    va_list args;
    va_start(args, texts);
    node *newHeader = (node *) malloc(sizeof(node));
    newHeader -> next = NULL;
    newHeader -> content = texts;
    a -> header = newHeader;
    node *ptr = a -> header;
    ptr -> next = (node *) malloc(sizeof(node));
    ptr = ptr -> next;
    char *arg;
    a -> length = 1;
    a -> size = strlen(texts);
    while (1){
        arg = va_arg(args, char *);
        if (arg == NULL){break;}
        ptr -> content = (char *) calloc(strlen(arg)+1, 1);
        ptr -> content = arg;
        node *newNode = (node *) malloc(sizeof(node));
        newNode -> next = NULL;
        newNode -> content = 0;
        ptr -> next = newNode;
        ptr = ptr -> next;
        a -> length++;
        a -> size += strlen(arg);
    }
    a -> length++;
    ptr -> content = "voided";
    StrListRemoveAt(a, a -> length - 1);
    va_end(args);
}

/**
 * Merges the content of the given llist into one string
 * @param a ... llist to merge
 * @return merged content of 'a'
 */
char *StrListMergeContent(str_llist *a){
    node *ptr = a -> header;
    char *newStr = (char *) calloc(1,1);
    while (ptr != NULL){
        newStr = realloc(newStr, strlen(newStr) + strlen(ptr -> content) + 1);
        strncat(newStr, ptr -> content, strlen(ptr -> content));
        ptr = ptr -> next;
    }
    return newStr;
}

/**
 * Gets the index of the given string in the given llist
 * @param a ... llist to search in
 * @param text ... string to search
 * @return index of 'text' in 'a' (returns -1 if 'text' is not in 'a')
 */
int StrListIndexOf(str_llist *a, char *text){
    node *ptr = a -> header;
    int idx = -1;
    while (1){
        idx++;
        if (strcmp(text, ptr -> content) == 0){
            break;
        }
        if (ptr -> next == NULL){
            idx = -1;
            break;
        }
        ptr = ptr -> next;
    }
    return  idx;
}

#endif
