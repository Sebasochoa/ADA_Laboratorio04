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

void GRAPHshow(Graph G)
{
    if (!G)
    {
        printf("Grafo no existe.\n");
        return;
    }
    for (vertex v = 0; v < G->V; v++)
    {
        printf("%d:", v);
        for (link a = G->adj[v]; a; a = a->next)
            printf(" %d", a->w);
        printf("\n");
    }
}

void GRAPHdestroy(Graph *GP)
{
    if (!GP || !*GP)
        return;
    Graph G = *GP;
    for (vertex v = 0; v < G->V; v++)
    {
        link a = G->adj[v];
        while (a)
        {
            link nx = a->next;
            free(a);
            a = nx;
        }
    }
    free(G->adj);
    free(G);
    *GP = NULL;
}

int main()
{
    Graph G = GRAPHinit(4);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 3, 1);
    GRAPHshow(G);
    GRAPHdestroy(&G);
    GRAPHshow(G);
    return 0;
}
