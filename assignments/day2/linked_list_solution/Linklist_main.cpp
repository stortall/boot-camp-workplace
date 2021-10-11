
/*Implement a single (forward) linked list for integers, your application should be able to:
• Add items to the end of the list
• Remove items from the front the list
https://en.wikipedia.org/wiki/Linked_list
• Print the list in the correct order*/

#include "Linklist.h"


int main () {   
    element *head = genLL(3);

    add2list(head,5);

    printMeList(head);

    head = removeFromHead(head);

    std::cout << "----------------- " << std::endl;

    printMeList(head);

    deleteLL(head);


    return 0;
} 