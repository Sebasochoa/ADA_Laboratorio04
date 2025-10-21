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

static bool hasArc(Graph G, vertex v, vertex w)
{
    for (link a = G->adj[v]; a; a = a->next)
        if (a->w == w)
            return true;
    return false;
}

bool UGRAPHinsertEdge(Graph G, vertex v, vertex w)
{
    bool e1 = hasArc(G, v, w), e2 = hasArc(G, w, v);
    if (e1 && e2)
        return false;
    if (!e1)
        GRAPHinsertArc(G, v, w);
    if (!e2)
        GRAPHinsertArc(G, w, v);
    return true;
}

bool UGRAPHremoveEdge(Graph G, vertex v, vertex w)
{
    bool r1 = GRAPHremoveArc(G, v, w);
    bool r2 = GRAPHremoveArc(G, w, v);
    return r1 || r2;
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

int main()
{
    Graph G = GRAPHinit(6);
    UGRAPHinsertEdge(G, 0, 1);
    UGRAPHinsertEdge(G, 0, 2);
    UGRAPHinsertEdge(G, 2, 3);
    UGRAPHinsertEdge(G, 3, 4);
    UGRAPHinsertEdge(G, 4, 5);
    printf("Grafo inicial: A=%d\n", G->A);
    GRAPHshow(G);
    printf("Eliminar {0,1}: %s\n", UGRAPHremoveEdge(G, 0, 1) ? "eliminada" : "no existia");
    printf("Estado tras eliminar {0,1}: A=%d\n", G->A);
    GRAPHshow(G);
    printf("Eliminar {0,1} de nuevo: %s\n", UGRAPHremoveEdge(G, 0, 1) ? "eliminada" : "no existia");
    printf("Eliminar {2,5}: %s\n", UGRAPHremoveEdge(G, 2, 5) ? "eliminada" : "no existia");
    printf("Eliminar {3,4}: %s\n", UGRAPHremoveEdge(G, 3, 4) ? "eliminada" : "no existia");
    printf("Estado final: A=%d\n", G->A);
    GRAPHshow(G);
    return 0;
}
