#include <iostream>
#include <typeinfo>

typedef struct Node {
    int     data;
    struct Node *next;    
}Node_t;

Node_t *findLast(Node_t *LinkedList) {
    if (LinkedList == nullptr) {    
        return LinkedList;
    }
    Node_t *current = LinkedList;
     while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

void add(Node_t *LinkedList, int value) {
    // 1) find the last item
    // 2)create a new node
    // 3) assign & link
    if (LinkedList == nullptr) {
        std::cout << "add: LinkedList == nullptr" << std::endl; 
        LinkedList = new Node_t;
        LinkedList->data  = value;
        LinkedList->next = nullptr;        
    } else {
        Node_t  *newNode = new Node_t,
                *lastNode = findLast(LinkedList);
        newNode->next = nullptr;
        newNode->data = value;
        lastNode->next = newNode;    
    }
}

Node_t *remove(Node_t *LinkedList) {
    if (LinkedList == nullptr) {
        return LinkedList;
    }
    // 1) find the head of next and set is as new head
    // 2) delete head
    Node_t *next = LinkedList->next;
    std::cout << "Popping node with data value " << LinkedList->data << std::endl; 
    delete LinkedList;
    return next;
}

void print(Node_t *LinkedList) {
    // 1)loop over the list
    // 2) print things
    if (LinkedList == nullptr) {
        std::cout << "print: LinkedList == nullptr" << std::endl; 
        return;    
    }
    std::cout << "Printing data of linked list:" << std::endl; 
    while(LinkedList != nullptr) {
        std::cout << LinkedList->data << std::endl; 
        LinkedList = LinkedList->next;       
    }
}

int main (int argc, char ** argv) {    
    Node_t *MY_LINKED_LIST = new Node_t; 
    MY_LINKED_LIST->data = 10;
    MY_LINKED_LIST->next = nullptr;
    add (MY_LINKED_LIST, 12);
    add (MY_LINKED_LIST, 152);
    add (MY_LINKED_LIST, 1232);
    print(MY_LINKED_LIST);
    MY_LINKED_LIST = remove(MY_LINKED_LIST);
    print(MY_LINKED_LIST);
    return 0;}

// #include <iostream>

// typedef struct Node {
//     int data;
//     struct Node *next;
// }Node_t;

// void add(Node_t *LinkedList, int value) {
//     // find the last item
//     // create new node
//     // add value and link
//     Node_t *newNode,*current = LinkedList;
//     while (current->next != nullptr) {
//         current = current->next;
//     }
//     newNode = new Node_t;
//     newNode->next = nullptr;
//     newNode->data = value;
//     current->next = newNode;
// }
// void remove(Node_t *LinkedList) {

// }
// void print() {

// }

// int main() {
//     Node_t *myList;
//     add(myList, 1);
//     std::cout << myList->data << std::endl;
// }