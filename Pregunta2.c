#include <stdio.h>
#include <stdlib.h>

typedef int vertex;
typedef struct node *link;
typedef struct node
{
    vertex w;
    link next;
} Node;
typedef struct graph
{
    int V, A;
    link *adj;
} *Graph;

static link NEWnode(vertex w, link next)
{
    link x = malloc(sizeof *x);
    x->w = w;
    x->next = next;
    return x;
}
Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = calloc(V, sizeof(link));
    return G;
}
void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
    for (link a = G->adj[v]; a; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

int GRAPHoutdeg(Graph G, vertex v)
{
    int d = 0;
    for (link a = G->adj[v]; a; a = a->next)
        d++;
    return d;
}
int GRAPHindeg(Graph G, vertex v)
{
    int d = 0;
    for (vertex u = 0; u < G->V; u++)
        for (link a = G->adj[u]; a; a = a->next)
            if (a->w == v)
                d++;
    return d;
}

int main()
{
    Graph G = GRAPHinit(6);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 5);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 5);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 5, 3);
    printf("outdeg(1)=%d\n", GRAPHoutdeg(G, 2));
    printf("indeg(1)=%d\n", GRAPHindeg(G, 3));
    return 0;
}
