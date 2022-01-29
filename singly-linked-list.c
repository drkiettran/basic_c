#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Example of a singly linked-list management.
 * Singly linked-list is a uni-directional list. In other words,
 * you can can traverse only in one direction. You cannot go back
 * without performing some sort of tracking yourself.
 * 
 * All nodes are connected with a next_ptr value.
 * 
 * @author Kiet T. Tran, Ph.D.
 * 
 */

/**
 * @brief Data structures for the node and its contents ...
 * 
 */
typedef struct my_content{
    char* text;
} my_content;


typedef struct my_sll {
    struct my_sll *next_ptr;
    my_content *content;
} my_sll;


/**
 * @brief creating a singly linked-list with a given content.
 * 
 * @cond content cannot be NULL!
 * 
 * @param content 
 * @return my_sll* 
 */
my_sll* sll_make(my_content* content) {
    if (content == NULL) {
        printf("content is NULL!\n");
        return NULL;
    }
    my_sll *head = malloc(sizeof(my_sll));
    head->content = content;
    head->next_ptr = NULL;
    return head;
}

/**
 * @brief count the number of nodes in the list.
 * 
 * @param head 
 * @return int 
 */
int sll_count(my_sll *head) {

    if (head == NULL) {
        printf("head is NULL!\n");
        return 0;
    }

    int count = 1;
    my_sll *cur = head;
    while (cur->next_ptr != NULL) {
        count++;
        cur = cur->next_ptr;
    }
    return count;
}

/**
 * @brief append a node to the end of the list
 * 
 * @cond if the head is NULL, append fails and returns NULL
 * 
 * @param head 
 * @param content 
 * @return my_sll* 
 */
my_sll* sll_append(my_sll* head, my_content* content) {
    if (head == NULL || content == NULL) {
        printf("head or content is NULL!\n");
        return NULL;
    }

    my_sll* cur = head;

    // go to the last node.
    while (cur->next_ptr != NULL) {
        cur = cur->next_ptr;
    }

    // make a new node & append to the end.
    my_sll* new_sll = malloc(sizeof(my_sll));
    new_sll-> next_ptr = NULL;
    new_sll-> content = content;
    cur->next_ptr = new_sll;
    return head;
}

/**
 * @brief print all nodes and their contents.
 * 
 * @param head 
 */
void sll_print(my_sll *head) {
    if (head == NULL) {
        printf("head is NULL!\n");
    }
    
    my_sll* cur = head;
    int count = 1;
    printf("*** list:\n");
    do {
        printf("%d. %s\n", count, cur->content->text);
        cur = cur->next_ptr;
        count++;
    } while (cur != NULL);
    printf("*** size=%d\n", count-1);
}

/**
 * @brief search for a node with given content.
 * 
 * @cond neither head nor content should be NULL.
 * 
 * @param head 
 * @param content 
 * @return my_sll* 
 */
my_sll* sll_search(my_sll* head, my_content* content) {
    if (head == NULL || content == NULL) {
        printf("head or content is NULL!\n");
        return NULL;
    }

    printf("** searching for %s\n", content->text);
    my_sll* cur = head;
    do {
        if (strcmp(cur->content->text, content->text) == 0) {            
            return cur;
        }
        cur = cur->next_ptr;
    } while (cur != NULL);
    return NULL;
}

/**
 * @brief inserting a node infront of a node pointed by `at`.
 * 
 * @cond head, at, and content cannot be NULL.
 * 
 * @param head 
 * @param at 
 * @param content 
 * @return my_sll* 
 */
my_sll* sll_insert(my_sll* head, my_sll* at, my_content* content) {

    if (head == NULL || at == NULL || content == NULL) {
        printf("head or at or content is NULL!\n");
        return head;
    }
    
    printf("inserting node ... %s at %s\n", content->text, at->content->text);
    my_sll* cur = head;

    printf("inserting at the head?\n");
    // Insert at the head
    if (at == head) {
        printf("inserting @ head ...\n");
        head = malloc(sizeof(my_sll));
        head->content = content;
        head->next_ptr = cur;
        return head;
    }

    // Insert in the middle
    printf("looking for the 'before' node\n");
    do {
        if (cur->next_ptr == at) {
            printf("found node before '%s'\n", cur->content->text);
            break;
        }
        cur = cur->next_ptr;
    } while (cur != NULL);

    printf("found it?\n");
    // cannot locate the node before at
    if (cur == NULL) {
        return head;
    }

    printf("inserting and return ...\n");
    // located the node before at. now insert the node in front of at.
    // cur ---> at
    // cur ---> new ---> at;
    my_sll *new = malloc(sizeof(my_sll));
    new->content = content;
    new->next_ptr = at;
    cur->next_ptr = new;

    // printf("cur %s\n", cur->content->text);
    // printf("new %s\n", new->content->text);
    // printf("at %s\n", at->content->text);
    return head;
}

/**
 * @brief making the content with a given text.
 * 
 * @cond text cannot be NULL
 * 
 * @param text 
 * @return my_content* 
 */
my_content* content_make(char* text) {
    if (text == NULL) {
        printf("text is NULL!\n");
        return NULL;
    }

    my_content* content = malloc(sizeof(my_content));
    content->text = malloc(strlen(text)+1);
    strcpy(content->text, text);
    return content;
}

my_content* content_free(my_content* content) {
    if (content == NULL) {
        printf("content is NULL!\n");
        return content;
    }

    printf("freeing content node ...\n");
    if (content->text != NULL) {
        free(content->text);
    }
    free(content);
    return NULL;
}

void sll_free_node(my_sll* node) {
    if (node == NULL) {
        printf("node is NULL!\n");
        return;
    }

    printf("freeing sll node ...\n");
    content_free(node->content);
    free(node);
}

/**
 * @brief remove a node from a list. it is not freeing the node.
 * 
 * @cond head or at cannot be NULL
 * 
 * @param head 
 * @param at 
 * @return my_sll* 
 */
my_sll* sll_remove_node(my_sll* head, my_sll* at) {
    if (head == NULL || at == NULL) {
        return head;
    }

    // remove the head
    if (head == at) {        
        head = head->next_ptr;
        return head;
    }

    my_sll* cur = head;

    // remove in the middle
    printf("looking for the 'before' node\n");
    do {
        if (cur->next_ptr == at) {
            printf("found node before '%s'\n", cur->content->text);
            break;
        }
        cur = cur->next_ptr;
    } while (cur != NULL);

    printf("found it?\n");
    if (cur != NULL) {
        cur->next_ptr = at->next_ptr;
    }

    return head;
}

/**
 * @brief remove all nodes and free node along with the content.
 * 
 * @cond head cannot be NULL!
 * 
 * @param head 
 */
void sll_remove_all(my_sll* head) {
    if (head == NULL) {
        printf ("head is NULL!\n");
        return;
    }
    printf ("removing all nodes ...\n");
    my_sll* cur = head;
    do {
        my_sll* free_sll = cur;
        cur = cur->next_ptr;
        free(free_sll);
    } while(cur != NULL);
}

/**
 * @brief Testing code starts here ...
 * 
 */

my_sll* test_make_sll(my_content* content) {
    // creat a list with 1 node
    printf(">>> 1. making list <<<\n\n");
    my_sll *head = sll_make(content);
    printf("text= %s\n", head->content->text);
    printf("size= %d\n", sll_count(head));
    return head;
}

/**
 * @brief main program does these:
 * 1. make a singly linked-list
 * 2. append nodes
 * 3. search nodes
 * 4. insert nodes
 * 5. remove nodes
 * 6. free singly linked-list.
 * 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) {

    // creat a list with 1 node
    printf(">>> 1. making list <<<\n\n");
    my_sll *head = sll_make(content_make("*** 1.0 ***"));
    printf("text= %s\n", head->content->text);
    printf("size= %d\n", sll_count(head));

    // adding the contents ...
    printf(">>> 2. appending nodes <<<\n\n");
    sll_append(head, content_make("*** 2.0 ***"));
    sll_append(head, content_make("*** 3.0 ***"));

    printf("\n\n");
    sll_print(head);
    printf("size= %d\n", sll_count(head));

    // searching for 2
    printf(">>> 3. searching for nodes <<<\n\n");
    my_content* search_content = content_make("*** 2.0 ***");
    my_sll* found_sll = sll_search(head, search_content);
    if (found_sll != NULL) {
        printf ("search=%s; found= %s\n", search_content->text, found_sll->content->text);
    }

    // searching for 3
    printf("\n\n");
    search_content = content_free(search_content);
    search_content = content_make("*** 3.0 ***");
    found_sll = sll_search(head, search_content);
    if (found_sll != NULL) {
        printf ("search=%s; found= %s\n", search_content->text, found_sll->content->text);
    }

    printf(">>> 4. inserting nodes <<<\n\n");
    printf("before insert at 2.0...\n");
    sll_print(head);

    // search for content 2, then insert at that node.  
    printf("\n\n");  
    search_content = content_free(search_content);
    search_content = content_make("*** 2.0 ***");
    my_sll* at = sll_search(head, search_content);

    head = sll_insert(head, at, content_make("*** 1.5 ***"));

    printf("\n\n");
    printf("after insert at 2.0...\n");
    sll_print(head);

    // search for content 3, then insert at that node.    
    printf("\n\n");
    search_content = content_free(search_content);
    search_content = content_make("*** 3.0 ***");
    at = sll_search(head, search_content);

    head = sll_insert(head, at, content_make("*** 2.5 ***"));

    printf("\n\n");
    printf("after insert at 3.0...\n");
    sll_print(head);

    // insert at head.
    printf("\n\n");
    head = sll_insert(head, head, content_make("*** 0.5 ***"));
    printf("\n\n");
    printf("after insert at head...\n");
    sll_print(head);

    printf(">>> 5. removing nodes <<<\n\n");
    search_content = content_free(search_content);
    search_content = content_make("*** 0.5 ***");
    at = sll_search(head, search_content);
    head = sll_remove_node(head, at);
    sll_print(head);

    search_content = content_free(search_content);
    search_content = content_make("*** 2.5 ***");
    at = sll_search(head, search_content);
    head = sll_remove_node(head, at);
    sll_print(head);

    search_content = content_free(search_content);
    search_content = content_make("*** 1.5 ***");
    at = sll_search(head, search_content);
    head = sll_remove_node(head, at);
    sll_print(head);

    printf(">>> 6. freeing list <<<\n\n");
    search_content = content_free(search_content);
    sll_remove_all(head);
}