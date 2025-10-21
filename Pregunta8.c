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
    printf("Insertar {0,1}: %s\n", UGRAPHinsertEdge(G, 0, 1) ? "insertado" : "ya existia");
    printf("Insertar {0,2}: %s\n", UGRAPHinsertEdge(G, 0, 2) ? "insertado" : "ya existia");
    printf("Insertar {2,3}: %s\n", UGRAPHinsertEdge(G, 2, 3) ? "insertado" : "ya existia");
    printf("Insertar {4,5}: %s\n", UGRAPHinsertEdge(G, 4, 5) ? "insertado" : "ya existia");
    printf("Estado del grafo: A=%d\n", G->A);
    GRAPHshow(G);
    printf("Intentar duplicado {0,1}: %s\n", UGRAPHinsertEdge(G, 0, 1) ? "insertado" : "ya existia");
    printf("Intentar duplicado {2,3}: %s\n", UGRAPHinsertEdge(G, 2, 3) ? "insertado" : "ya existia");
    printf("Estado final: A=%d\n", G->A);
    GRAPHshow(G);
    return 0;
}
