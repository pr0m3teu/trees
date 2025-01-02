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

void add_node(Node* parent, Node* child);
void add_nodes_with_null(Node* first, ...);

void df(Node *start);
Node* dfs(Node *start, int data);

void bf(Node *start, bool first);


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

Node* dfs(Node *start, int data)
{
    if (start->data == data) return start;
    for (size_t i = 0; i < start->num_children; i++)
    {
        return dfs(start->children[i], data);
    }
    return NULL;
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

#endif // TREE_IMPLEMENTATION
#endif // TREE_H_
