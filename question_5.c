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

    // Allocating memory for new node (both at struct level and object level)
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->name = (char *) malloc(strlen(newObj) + 1);

    // Assigning string to new node
    strcpy(new_node->name, newObj);

    // Assigning XOR value to new node
    new_node->xor_value = calculate_xor_value(*head, NULL);

    // If head node isn't NULL, update it's XOR value
    if (*head != NULL) {
        
        // Calculating XOR value of node next to head (e.g. 1 ^ NULL ^ NULL = 1)
        Node *next_head = calculate_xor_value((*head)->xor_value, NULL);
        // Updating head XOR value (e.g. 1 ^ 3 = 2)
        (*head)->xor_value = calculate_xor_value(next_head, new_node);

    }

    // Updating head to new node
    *head = new_node;
}

// If possible, inserts before the string "before" and returns true. Returns false if not possible (e.g., the before string is not in the list).
int insert_before(Node** head, const char* before, const char* newObj) {
    
    // String should not be added if it's more than 64 bytes (1 byte per char)
    if (strlen(newObj) + 1 > 64) {
        return 0;
    }

    // If before string is the head, then insert before head
    if (!strcmp((*head)->name, before)) {

        // Create new node for newObj
        Node *new_node = (Node *) malloc(sizeof(Node));
        new_node->name = (char *) malloc(strlen(newObj) + 1);

        // Assigning name to new node
        strcpy(new_node->name, newObj);

        // Assign XOR value by doing previous and next
        new_node->xor_value = calculate_xor_value(NULL, *head);

        Node *next_head = calculate_xor_value(NULL, (*head)->xor_value);

        // Change head XOR value by doing next (to it) and new node
        (*head)->xor_value = calculate_xor_value(new_node, next_head);

        // Assign new node as head
        *head = new_node;

        return 1;
    }

    // Go through XOR linked list
    Node *curr = *head;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {

        // Get the next node (prev ^ value = next)
        next = calculate_xor_value(prev, curr->xor_value);

        // If the string "before" is found, insert newObj before that
        if (!strcmp(next->name, before)) {

            // Create new node for newObj
            Node *new_node = (Node *) malloc(sizeof(Node));
            new_node->name = (char *) malloc(strlen(newObj) + 1);

            // Assigning name to new node
            strcpy(new_node->name, newObj);

            // Assign XOR value by doing previous and next
            new_node->xor_value = calculate_xor_value(curr, next);
            
            // Change previous XOR value by doing next (to it) and new node
            curr->xor_value = calculate_xor_value(prev, new_node);

            return 1;

        }

        // Update for next iteration
        prev = curr;
        curr = next;

    }

    return 0;
}

// If possible, inserts after the string "after" and returns true. Returns false if not possible (e.g., the after string is not in the list).
int insert_after(Node** head, const char* after, const char* newObj) {

    // String should not be added if it's more than 64 bytes (1 byte per char)
    if (strlen(newObj) + 1 > 64) {
        return 0;
    }

    // Go through XOR linked list
    Node *curr = *head;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {

        // Get the next node (prev ^ value = next)
        next = calculate_xor_value(prev, curr->xor_value);

        // If the string "after" is found, insert newObj after that
        if (!strcmp(curr->name, after)) {

            // If next is NULL, then there is nothing to its right
            if (next == NULL) {

                // The insert string function can be used
                insert_string(&curr, newObj);

                return 1;

            }

            // Create new node for newObj
            Node *new_node = (Node *) malloc(sizeof(Node));
            new_node->name = (char *) malloc(strlen(newObj) + 1);

            // Assigning name to new node
            strcpy(new_node->name, newObj);

            // Assign XOR value by doing previous and next
            new_node->xor_value = calculate_xor_value(curr, next);
            
            // Change previous XOR value by doing next (to it) and new node
            curr->xor_value = calculate_xor_value(prev, new_node);

            return 1;

        }

        // Update for next iteration
        prev = curr;
        curr = next;

    }

    return 0;
}

// If possible removes the string at the beginning of the XOR Linked list and returns its value in result. If successful return true, otherwise returns false
int remove_string(Node** head, char* result) {
    
    // String cannot be removed if head is null
    if (*head == NULL) {
        return 0;
    }

    // Store head node temporarily
    Node *temp = *head;

    *head = calculate_xor_value(NULL, temp->xor_value);
    
    // Get node next to the new head
    Node *next_head = calculate_xor_value(temp, (*head)->xor_value);

    // Change XOR value for new head
    (*head)->xor_value = calculate_xor_value(NULL, next_head);

    // Returning value of removed node to the result string
    strcpy(result, temp->name);

    free(temp->name);
    free(temp);

    return 1;
}

// If possible, removes the string after the string "after" and fills in the result buffer with its value. If successful return true, otherwise returns false
int remove_after(Node** head, const char *after, char *result) {

    // String cannot be removed if head is null
    if (*head == NULL) {
        return 0;
    }

    // Go through XOR linked list
    Node *curr = *head;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {

        // Get the next node (prev ^ value = next)
        next = calculate_xor_value(prev, curr->xor_value);

        // If the string "after" is found, delete node after that
        if (!strcmp(curr->name, after)) {

            // Check that there is a node after the string "after"
            if (next == NULL) {
                return 0;
            }

            // Store node to be removed temporarily
            Node *temp = next;
            
            // Get node next to node to be removed
            Node *next_removed = calculate_xor_value(curr, temp->xor_value);

            // Change XOR value for current node
            curr->xor_value = calculate_xor_value(prev, next_removed);

            // Returning value of removed node to the result string
            strcpy(result, temp->name);

            free(temp->name);
            free(temp);

            return 1;

        }

        // Update for next iteration
        prev = curr;
        curr = next;

    }

    return 0;
}

// If possible, removes the string before the string "before" and fills in the result buffer with its value. If successful return true, otherwise returns false.
int remove_before(Node** head, const char *before, char *result) {
        
    // String cannot be removed if head is null
    if (*head == NULL) {
        return 0;
    }

    // If the string "before" is at head, return false
    if (!strcmp((*head)->name, before)) {
        return 0;
    }

    // Go through XOR linked list
    Node *curr = *head;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {

        // Get the next node (prev ^ value = next)
        next = calculate_xor_value(prev, curr->xor_value);

        // If the string "before" is found, delete node before that
        if (!strcmp(next->name, before)) {

            // Store node to be removed temporarily
            Node *temp = curr;

            // If there is no previous node, next will be the new head
            if (prev == NULL) {
                
                // New head is the string "before"
                *head = next;

                // Get node next to the new head
                Node *next_head = calculate_xor_value(temp, (*head)->xor_value);

                (*head)->xor_value = calculate_xor_value(NULL, next_head);
                
            }
            else {

                // Get node next to prev
                Node *next_removed = calculate_xor_value(prev->xor_value, temp);

                // Change XOR value for prev
                prev->xor_value = calculate_xor_value(next_removed, next);

            }

            // Returning value of removed node to the result string
            strcpy(result, temp->name);

            free(temp->name);
            free(temp);

            return 1;

        }

        // Update for next iteration
        prev = curr;
        curr = next;

    }

    return 0;
}

// Removes all nodes and releases any memory allocated to the linked list
void free_all(Node** head) {

    Node *curr = *head;
    Node *prev = NULL;
    Node *next;

    Node *temp;

    int flag_free = 0;

    while (curr != NULL) {

        temp = prev;

        // Get next node in the XOR Linked List
        next = calculate_xor_value(prev, curr->xor_value);

        // Update node value
        prev = curr;
        curr = next;

        if (temp != NULL) {

            printf("%s\n", temp->name);

            free(temp->name);
            free(temp);
        }

        if (curr == NULL) {
            flag_free = 1;
        }

    }

    // Free last node in XOR Linked List (if you have to)
    if (flag_free) {
        temp = prev;

        printf("%s\n", temp->name);

        free(temp->name);
        free(temp);
    }

        // Temp | Curr  | Prev | Next 
        //      | Alpha | NULL | 
        // NULL | Bravo | Alpha| Bravo
        // Alpha| Charlie| Bravo| Charlie -> free Alpha 
        // Bravo| NULL | Charlie | NULL -> free Bravo
        // Curr is NULL
}

int main () {

    Node* head = NULL;
    insert_string(&head, "Alpha");
    insert_string(&head, "Bravo");
    insert_string(&head, "Charlie");

    // Going back to Alpha backwards from Charlie
    Node *next = head;
    printf("%s\n", head->name);
    head = calculate_xor_value(head->xor_value, NULL);
    printf("%s\n", head->name);
    head = calculate_xor_value(head->xor_value, next);
    printf("%s\n", head->name);

    printf("_______________\n");

    //char *result = malloc(64);

    //remove_before(&head, "Charlie", result);

    //printf("REMOVED: %s\n", result);

    //free(result);

    //free_all(&head);

    // Going back to Yessir from Alpha
    //Node *previous = head;
    //printf("%s\n", head->name);
    //head = calculate_xor_value(NULL, head->xor_value);
    //Node *previous2 = head;
    //printf("%s\n", head->name);
    //head = calculate_xor_value(previous, head->xor_value);
    //printf("%s\n", head->name);
    //head = calculate_xor_value(previous2, head->xor_value);
    //printf("%s\n", head->name);

    return 0;
}
