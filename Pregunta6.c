#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

bool GRAPHremoveArc(Graph G, vertex v, vertex w)
{
    link *pp = &G->adj[v];
    while (*pp)
    {
        if ((*pp)->w == w)
        {
            link del = *pp;
            *pp = del->next;
            free(del);
            G->A--;
            return true;
        }
        pp = &(*pp)->next;
    }
    return false;
}

void GRAPHshow(Graph G)
{
    for (vertex v = 0; v < G->V; v++)
    {
        printf("%d:", v);
        for (link a = G->adj[v]; a; a = a->next)
            printf(" %d", a->w);
        printf("\n");
    }
}

int main()
{
    Graph G = GRAPHinit(5);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 0, 3);
    GRAPHinsertArc(G, 2, 4);
    printf("Grafo original:\n");
    GRAPHshow(G);
    printf("Grafo modificado:\n");
    GRAPHremoveArc(G, 0, 3);
    GRAPHshow(G);
    return 0;
}
