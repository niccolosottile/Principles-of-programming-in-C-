#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct used to store nodex of XOR linked list
typedef struct node {
    char* name;
    struct node* xor_value;
} Node;

// Returns the XOR value given pointers to the previous and next nodes
Node* calculate_xor_value(Node* before, Node* after) {
    return (Node*)((intptr_t)before ^ (intptr_t)after);
}

// Inserts the string at the beginning of the XOR linked list.
void insert_string(Node** head, const char* newObj) {

    // String should not be added if it's more than 64 bytes (1 byte per char)
    if (strlen(newObj) + 1 > 64) {
        return;
    }

    printf("continued");

    

}

// If possible, inserts before the string "before" and returns true. Returns false if not possible (e.g., the before string is not in the list).
int insert_before(Node** head, const char* before, const char* newObj) {
    return -1;
}

// If possible, inserts after the string "after" and returns true. Returns false if not possible (e.g., the after string is not in the list).
int insert_after(Node** head, const char* after, const char* newObj) {
    return -1;
}

// If possible removes the string at the beginning of the XOR Linked list and returns its value in result. If successful return true, otherwise returns false
int remove_string(Node** head, char* result) {
    return -1;
}

// If possible, removes the string after the string "after" and fills in the result buffer with its value. If successful return true, otherwise returns false
int remove_after(Node** head, const char *after, char *result) {
    return -1;
}

// If possible, removes the string before the string "before" and fills in the result buffer with its value. If successful return true, otherwise returns false.
int remove_before(Node** head, const char *before, char *result) {
    return -1;
}

// Removes all nodes and releases any memory allocated to the linked list
void free_all(Node** head) {
    
}

int main () {

    Node* head = NULL;
    insert_string(&head, "Alpha");
    //insert_string(&head, "Bravo");
    //insert_string(&head, "Charlie");

    return 0;
}
