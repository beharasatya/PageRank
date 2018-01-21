// Linked list interface ... 

#include <stdbool.h>


typedef struct Node *List;

List insertLL(List, int);
List deleteLL(List, int);
bool inLL(List, int);
void freeLL(List);
void showLL(List);
int getValue(List);
int indexOf(List, int);