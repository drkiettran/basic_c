#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ansi_color_codes.h"

/**
 * @brief Example of a doubly linked-list management.
 * doubly linked-list is a binary-directional list. In other words,
 * you can can traverse forward and backward from any node.
 * 
 * All nodes are connected with a prev_ptr and a next_ptr value.
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


typedef struct my_dll {
    struct my_dll* prev_ptr;
    struct my_dll* next_ptr;
    my_content *content;
} my_dll;

typedef enum {false, true} bool;

/**
 * @brief making the content with a given text.
 * 
 * @cond text cannot be NULL
 * 
 * @param text 
 * @return my_content* 
 */
my_content* content_make(const char* text) {
    if (text == NULL) {
        printf("text is NULL!\n");
        return NULL;
    }

    my_content* content = malloc(sizeof(my_content));
    content->text = malloc(strlen(text)+1);
    strcpy(content->text, text);
    return content;
}

/**
 * @brief Free the content
 * 
 * @param content 
 * @return my_content* 
 */
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

/**
 * @brief Compare if two contents are the same.
 * 
 * @param c1 
 * @param c2 
 * @return true 
 * @return false 
 */
bool content_equals(my_content* c1, my_content* c2) {
    if (c1 == NULL || c2 == NULL) {
        return false;
    }

    return !strcmp((*c1).text, c2->text); // 1 way to dereference a ptr.
}

/**
 * @brief Making a node with a given content.
 * 
 * @param content 
 * @return my_dll* 
 */
my_dll* dll_make_node(my_content* content) {
    if (content == NULL) {
        printf("content is NULL!\n");
        return NULL;
    }

    my_dll* node = malloc(sizeof(my_dll));
    node->prev_ptr = NULL;
    node->next_ptr = NULL;
    node->content = content;
    return node;
}

/**
 * @brief Making the list
 * 
 * @param content 
 * @return my_dll* 
 */
my_dll* dll_make_list(my_content* content) {
    if (content == NULL) {
        printf("content is NULL!\n");
        return NULL;
    }

    return dll_make_node(content);
}

/**
 * @brief Freeing a node including its content.
 * 
 * @param node 
 * @return my_dll* 
 */
my_dll* dll_free_node(my_dll* node) {
    if (node == NULL) {
        printf("node is NULL!\n");
        return node;
    }

    printf("freeing sll node ...\n");
    content_free(node->content);
    free(node);
    return NULL;
}

/**
 * @brief Adding a given node at the end of the list. It becomes
 *        the last node in the list.
 * 
 * @param head 
 * @param node 
 * @return my_dll* 
 */
my_dll* dll_append_node(my_dll* head, my_dll* node) {
    if (node == NULL) {
        printf("node is NULL!\n");
        return head;
    }

    my_dll* last_node = head;
    while (last_node-> next_ptr != NULL) {
        last_node = last_node->next_ptr;
    }
    last_node->next_ptr = node;
    node->prev_ptr = last_node;
    return head;
}

/**
 * @brief Inserting a node in a list.
 * 
 * @param head 
 * @param at 
 * @param new_node 
 * @return my_dll* 
 */
my_dll* dll_insert_node(my_dll* head, my_dll* at, my_dll* new_node) {
    if (head == NULL || at == NULL || new_node == NULL) {
        printf("list is empty or at is NULL or new_node is NULL!\n");
        return head;
    }

    // inserting at head
    if (at == head) {
        new_node->next_ptr = head;
        head->prev_ptr = new_node;
        new_node->prev_ptr = NULL;
        return new_node;
    }

    // insert in the middle
    new_node->next_ptr = at;
    new_node->prev_ptr = at->prev_ptr;
    at->prev_ptr->next_ptr = new_node;
    at->prev_ptr = new_node;
    return head;
}

/**
 * @brief Removing a node from the list (DONOT FREE THE NODE)
 * 
 * @param head 
 * @param at 
 * @return my_dll* 
 */

my_dll* dll_remove_node(my_dll* head, my_dll* at) {
    if (head == NULL || at == NULL) {
        printf("head and/or at is NULL!\n");
        return head;
    }

    if (at == head) {
        head = head->next_ptr;
        if (head != NULL) {
            head->prev_ptr = NULL;
        }
    } else {
        at->prev_ptr->next_ptr = at->next_ptr;
        if (at->next_ptr != NULL) {
            at->next_ptr->prev_ptr = at->prev_ptr;
        }
    }
    return head;
}

/**
 * @brief getting the size of the list.
 * 
 * @param head 
 * @return int 
 */
int dll_size(my_dll* head) {
    my_dll* cur = head;
    int count = 0;
    while (cur != NULL) {
        count++;
        cur = cur->next_ptr;
    }
    return count;
}

/**
 * @brief Returns the last node of the list
 * 
 * @param head 
 * @return my_dll* 
 */
my_dll* dll_get_last_node(my_dll* head) {
    if (head == NULL) {
        printf("head is NULL!\n");
        return NULL;
    }

    my_dll* last = head;
    while (last->next_ptr != NULL) {
        last = last->next_ptr;
    }
    return last;
}

/**
 * @brief printing the contents of the list
 * 
 * @param head 
 */
void dll_print_list(my_dll* head) {
    if (head == NULL) {
        printf(">>> list is empty!\n");
        return;
    }

    my_dll* cur = head;
    int node_no = 1;
    while (cur != NULL) {
        printf("%d. %s\n", node_no, cur->content->text);
        cur = cur->next_ptr;
        node_no++;
    }
    printf(">>> list size: %d\n", node_no-1);
    return;
}

/**
 * @brief print the contents of the list in a reverse order.
 * 
 * @param head 
 */
void dll_print_list_reverse(my_dll* head) {
    if (head == NULL) {
        printf("list is empty!\n");
        return;
    }

    printf("%sprinting list in reverse order...%s\n", YEL, reset);
    my_dll* last = head;
    int count = 1;
    while (last->next_ptr != NULL) {
        last = last->next_ptr;
        count++;
    }

    int size = count;
    my_dll* cur = last;
    while (cur != NULL) {
        printf("%d. %s\n", count--, cur->content->text);
        cur = cur->prev_ptr;
    }
    printf(">>> list size: %d\n", size);
    return;
}
/**
 * @brief Removing all the node in the list, including the head node.
 *        return NULL when complete.
 * 
 * @param head 
 * @return my_dll* 
 */
my_dll* dll_remove_list(my_dll* head) {

    while (head != NULL) {
        my_dll* cur = head;
        head = head-> next_ptr;
        dll_free_node(cur);
    }

    return NULL;
}

// ****** TEST CODE ****** //

const char* test_str_node_0_5 = "*** Node 0.5 ***";
const char* test_str_node_1_0 = "*** Node 1.0 ***";
const char* test_str_node_1_5 = "*** Node 1.5 ***";
const char* test_str_node_2_0 = "*** Node 2.0 ***";
const char* test_str_node_2_5 = "*** Node 2.5 ***";
const char* test_str_node_3_0 = "*** Node 3.0 ***";

void test_making_dll() {
    printf("%s\ntest_making_dll%s\n", GRN, reset);
    printf("*** making doubly-linked-list correctly\n");
    my_dll* head = dll_make_list(content_make(test_str_node_1_0));
    printf("content = %s\n", head->content->text);
    assert(head != NULL);
    dll_print_list(head);

    printf("*** verify correct content\n");
    my_content* test_content = content_make(test_str_node_1_0);
    assert(content_equals(head->content, test_content));
    dll_print_list(head);

    printf("*** freeing doubly-linked-list correctly\n");
    head = dll_free_node(head);
    assert(head == NULL);
    dll_print_list(head);

    printf("*** making doubly-linked-list incorrectly\n");
    head = dll_make_list(NULL);
    assert(head == NULL);
    dll_print_list(head);

    printf("*** freeing doubly-linked-list incorrectly\n");
    free(head);
    assert(head == NULL);
    dll_print_list(head);
    return;
}

void test_appending_nodes() {    
    printf("%s\ntest_appending_nodes%s\n", GRN, reset);
    printf("*** making dll list\n");
    my_dll* head = dll_make_list(content_make(test_str_node_1_0));
    assert(dll_size(head) == 1);
    dll_print_list(head);

    printf("*** appending node correctly!\n");
    dll_append_node(head, dll_make_node(content_make(test_str_node_2_0)));
    assert(dll_size(head) == 2);
    dll_print_list(head);

    printf("*** verifying appended content\n");
    my_content* test_content = content_make(test_str_node_2_0);
    assert(content_equals(dll_get_last_node(head)->content, test_content));
    content_free(test_content);

    printf("*** removing the list\n");
    head = dll_remove_list(head);
    assert(head == NULL);
    dll_print_list(head);

    head = dll_make_list(content_make("*** Node 1 ***"));
    assert(dll_size(head) == 1);
    dll_print_list(head);

    printf("*** appending node incorrectly!\n");
    dll_append_node(head, dll_make_node(NULL));
    assert(dll_size(head) == 1);
    dll_print_list(head);

    printf("*** removing the list\n");
    head = dll_remove_list(head);
    assert(head == NULL);
    dll_print_list(head);

}

my_dll* dll_search_node(my_dll* head, my_content* content) {
    if (head == NULL) {
        printf("list is empty!\n");
        return NULL;
    }

    my_dll* search_node = head;
    while(search_node != NULL && !content_equals(search_node->content, content)) {
        search_node = search_node->next_ptr;
    }
    return search_node;
}

void test_searching_nodes() {
    printf("%s\ntest_searching_nodes%s\n", GRN, reset);
    printf("*** making dll list of 3\n");
    my_dll* head = dll_make_list(content_make(test_str_node_1_0));
    dll_append_node(head, dll_make_node(content_make(test_str_node_2_0)));
    dll_append_node(head, dll_make_node(content_make(test_str_node_3_0)));
    assert(dll_size(head) == 3);
    dll_print_list(head);
    dll_print_list_reverse(head);

    printf("searching %s\n", test_str_node_1_0);
    my_content* search_content = content_make(test_str_node_1_0);
    my_dll* searching_node = dll_search_node(head, search_content);
    assert(searching_node != NULL);
    assert(content_equals(searching_node->content, search_content));

    printf("searching %s\n", test_str_node_2_0);
    content_free(search_content);
    search_content = content_make(test_str_node_2_0);
    searching_node = dll_search_node(head, search_content);
    assert(searching_node != NULL);
    assert(content_equals(searching_node->content, search_content));

    printf("searching %s\n", test_str_node_3_0);
    content_free(search_content);
    search_content = content_make(test_str_node_3_0);
    searching_node = dll_search_node(head, search_content);
    assert(searching_node != NULL);
    assert(content_equals(searching_node->content, search_content));

    printf("*** removing the list\n");
    head = dll_remove_list(head);
    assert(head == NULL);
    dll_print_list(head);
}

void test_inserting_nodes() {
    printf("%s\ntest_inserting_nodes%s\n", GRN, reset);
    printf("*** making dll list of 3\n");
    my_dll* head = dll_make_list(content_make(test_str_node_1_0));
    dll_append_node(head, dll_make_node(content_make(test_str_node_2_0)));
    dll_append_node(head, dll_make_node(content_make(test_str_node_3_0)));
    assert(dll_size(head) == 3);
    dll_print_list(head);

    printf("inserting a new node 1.5\n");
    my_dll* new_node = dll_make_node(content_make(test_str_node_1_5));
    my_content* search_content = content_make(test_str_node_2_0);
    my_dll* at = dll_search_node(head, search_content);
    head = dll_insert_node(head, at, new_node);
    content_free(search_content);    
    assert(dll_size(head) == 4);
    dll_print_list(head);

    my_content* next_content = content_make(test_str_node_2_0);
    my_content* prev_content = content_make(test_str_node_1_0);
    
    assert(content_equals(new_node->prev_ptr->content, prev_content));
    assert(content_equals(new_node->next_ptr->content, next_content));
    content_free(next_content);
    content_free(prev_content);

    printf("inserting a new node 2.5\n");
    new_node = dll_make_node(content_make(test_str_node_2_5));
    search_content = content_make(test_str_node_3_0);
    at = dll_search_node(head, search_content);
    head = dll_insert_node(head, at, new_node);
    content_free(search_content);    
    assert(dll_size(head) == 5);
    dll_print_list(head);

    next_content = content_make(test_str_node_3_0);
    prev_content = content_make(test_str_node_2_0);
    
    assert(content_equals(new_node->prev_ptr->content, prev_content));
    assert(content_equals(new_node->next_ptr->content, next_content));
    content_free(next_content);
    content_free(prev_content);

    printf("inserting a 0.5 @ head\n");
    new_node = dll_make_node(content_make(test_str_node_0_5));    
    head = dll_insert_node(head, head, new_node);    
    assert(dll_size(head) == 6);
    dll_print_list(head);

    next_content = content_make(test_str_node_1_0);
    
    assert(new_node->prev_ptr == NULL);
    assert(content_equals(new_node->next_ptr->content, next_content));
    content_free(next_content);
    dll_print_list_reverse(head);

    printf("*** removing the list\n");
    head = dll_remove_list(head);
    assert(head == NULL);
    dll_print_list(head);
}

void test_removing_nodes() {
     printf("%s\ntest_removing_nodes%s\n", GRN, reset);
    printf("*** making dll list of 3\n");
    my_dll* head = dll_make_list(content_make(test_str_node_1_0));
    dll_append_node(head, dll_make_node(content_make(test_str_node_2_0)));
    dll_append_node(head, dll_make_node(content_make(test_str_node_3_0)));

    printf("inserting a new node 1.5\n");
    my_dll* new_node = dll_make_node(content_make(test_str_node_1_5));
    my_content* search_content = content_make(test_str_node_2_0);
    my_dll* at = dll_search_node(head, search_content);
    head = dll_insert_node(head, at, new_node);
    content_free(search_content);    

    printf("inserting a new node 2.5\n");
    new_node = dll_make_node(content_make(test_str_node_2_5));
    search_content = content_make(test_str_node_3_0);
    at = dll_search_node(head, search_content);
    head = dll_insert_node(head, at, new_node);
    content_free(search_content);    

    printf("inserting a 0.5 @ head\n");
    new_node = dll_make_node(content_make(test_str_node_0_5));    
    head = dll_insert_node(head, head, new_node);    

    dll_print_list(head);
    dll_print_list_reverse(head);

    printf("removing 0.5\n");
    search_content = content_make(test_str_node_0_5);
    my_content* cur_content = content_make(test_str_node_1_0);
    at = dll_search_node(head, search_content);
    head = dll_remove_node(head, at);
    assert(dll_size(head) == 5);
    assert(content_equals(head->content, cur_content));
    content_free(cur_content);
    content_free(search_content);
    dll_free_node(at);
    dll_print_list(head);
    dll_print_list_reverse(head);

    printf("removing 2.5\n");
    search_content = content_make(test_str_node_2_5);
    at = dll_search_node(head, search_content);
    head = dll_remove_node(head, at);
    assert(dll_size(head) == 4);
    dll_free_node(at);
    content_free(search_content);
    dll_print_list(head);
    dll_print_list_reverse(head);

    printf("removing 1.5\n");
    search_content = content_make(test_str_node_1_5);
    at = dll_search_node(head, search_content);
    head = dll_remove_node(head, at);
    assert(dll_size(head) == 3);
    dll_free_node(at);
    content_free(search_content);
    dll_print_list(head);
    dll_print_list_reverse(head);

    printf("*** removing the list\n");
    head = dll_remove_list(head);
    assert(head == NULL);
    dll_print_list(head);
}
/**
 * @brief running test code for using functions above.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) {   
    printf("%s---> STARTS!%s\n", RED, reset);
    test_making_dll();
    test_appending_nodes();
    test_searching_nodes();
    test_inserting_nodes();
    test_removing_nodes();
    printf("%s",RED);
    printf("%s\n---> ENDS!%s\n", RED, reset);

    return 0;
}