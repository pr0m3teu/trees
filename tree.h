#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct Node Node;

struct Node {
    Node** children;
    size_t num_children;
    size_t size;
    int data;
};

typedef struct node_t node_t;

struct node_t {
    node_t* left;
    node_t* right;
    int value;
};

// Normal Trees
void add_node(Node* parent, Node* child);
void add_nodes_with_null(Node* first, ...);

void df(Node *start);
void bf(Node *start, bool first);

// Binary Trees
node_t* init_node(int value);
void add_left(node_t *parent, node_t *child);
void add_right(node_t *parent, node_t *child);


#ifdef TREE_IMPLEMENTATION

#define add_nodes(first, ...) add_nodes_with_null(first, __VA_ARGS__, NULL)

static void check_ptr(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        exit(1);
    }
}

void add_node(Node* parent, Node* child)
{
    if (child == NULL)
    {
        fprintf(stderr, "ERROR: Child node is NULL\n");
        return;
    }
    
    if (parent->children == NULL)
    {
        parent->children = (Node**) malloc(sizeof(Node*));
        check_ptr(parent->children);
        parent->children[0] = child;
        parent->num_children = 1;
        parent->size = 1;
    }
    else 
    {
        if (parent->num_children == parent->size)
        {
            parent->children = realloc(parent->children, sizeof(Node*) * parent->size * 2);
            check_ptr(parent->children);
            parent->size *= 2;
        }
        parent->children[parent->num_children++] = child;
    }
}

void add_nodes_with_null(Node* first, ...)
{
    va_list args;
    va_start(args, first);
    
    Node* node = va_arg(args, Node*);
    while(node != NULL)
    {
        add_node(first, node);
        node = va_arg(args, Node*);
    }
    
}

void df(Node* start)
{
    if (start == NULL) return;
    printf("%d ", start->data);
    for (size_t i = 0; i < start->num_children; ++i)
    {
        df(start->children[i]);
    }
}

void bf(Node *start, bool first)
{
    if (start == NULL) return;
    if (first) printf("%d ", start->data);

    for (size_t i = 0; i < start->num_children; ++i)
    {
        printf("%d ", start->children[i]->data);
    }
    for (size_t i = 0; i < start->num_children; ++i) bf(start->children[i], false);
}

// Binary Trees

node_t* init_node(int value)
{
    node_t *node = malloc(sizeof(node_t));
    check_ptr(node);

    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

void add_left(node_t *parent, node_t *child)
{
    if (parent == NULL) return;
    parent->left = child;
}

void add_right(node_t *parent, node_t *child)
{
    if (parent == NULL) return;
    parent->right = child;
}

#endif // TREE_IMPLEMENTATION
#endif // TREE_H_
