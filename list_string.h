// String Linked list interface ... 

#include <stdbool.h>

typedef struct Node *List;

List insertLL(List, char*);
List deleteLL(List, char*);
bool inLL(List, char*);
void freeLL(List);
void showLL(List);
