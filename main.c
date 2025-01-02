#include <stdio.h>
#define TREE_IMPLEMENTATION
#include "tree.h"

int main(void)
{
    Node n1, n2, n3, n4, n5, n6, n7;
    n1.data = 1;
    n2.data = 2;
    n3.data = 3;
    n4.data = 4;
    n5.data = 5;
    n6.data = 6;
    n7.data = 7;
    
//    add_node(&n1, &n2);
//    add_node(&n1, &n3);
//    add_node(&n2, &n4);
//    add_node(&n3, &n5);
//    add_node(&n3, &n6);
//    add_node(&n2, &n7);
    
    add_nodes(&n1, &n2, &n3);
    add_nodes(&n2, &n4, &n7);
    add_nodes(&n3, &n5, &n6);
    
    printf("dfs: ");
    df(&n1);
    printf("\n");

    printf("bfs: ");
    bf(&n1, 1);
    printf("\n");

    return 0;
}
