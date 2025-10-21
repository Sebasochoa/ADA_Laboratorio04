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

int UGRAPHdegrees(Graph G)
{
    int maxd = 0;
    for (vertex v = 0; v < G->V; v++)
    {
        int d = 0;
        for (link a = G->adj[v]; a; a = a->next)
            d++;
        if (d > maxd)
            maxd = d;
    }
    return maxd;
}

bool hasArc(Graph G, vertex v, vertex w)
{
    for (link a = G->adj[v]; a; a = a->next)
        if (a->w == w)
            return true;
    return false;
}

void UGRAPHinsertEdge(Graph G, vertex v, vertex w)
{
    if (!hasArc(G, v, w))
        GRAPHinsertArc(G, v, w);
    if (!hasArc(G, w, v))
        GRAPHinsertArc(G, w, v);
}

int main()
{
    Graph G = GRAPHinit(6);
    UGRAPHinsertEdge(G, 0, 1);
    UGRAPHinsertEdge(G, 0, 2);
    UGRAPHinsertEdge(G, 1, 3);
    UGRAPHinsertEdge(G, 1, 4);
    UGRAPHinsertEdge(G, 2, 5);
    UGRAPHinsertEdge(G, 4, 5);
    printf("Listas de adyacencia iniciales:\n");
    GRAPHshow(G);
    int maxd = UGRAPHdegrees(G);
    printf("El grado maximo inicial es: %d\n", maxd);
    printf("Agregando nuevas aristas (1,5) y (0,4)...\n");
    UGRAPHinsertEdge(G, 1, 5);
    UGRAPHinsertEdge(G, 0, 4);
    printf("Nuevas listas de adyacencia:\n");
    GRAPHshow(G);
    printf("El nuevo grado maximo es: %d\n", UGRAPHdegrees(G));

    return 0;
}
