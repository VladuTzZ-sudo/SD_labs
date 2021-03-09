#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "../queue/queue.h"
#include "../stack/stack.h"

#define NR_NEIGHBOURS -1

#define TYPE_UNDIRECTED 0
#define TYPE_DIRECTED 1

typedef struct {
	int type;
	int nodes;
	int **adj;
} Graph;

int **createEdges(int type, int nodes, int edges, FILE *file);

void destroyEdges(int nodes, int **adj);

Graph *createGraph(int type, int nodes, int edges, FILE *file);

void destroyGraph(Graph *graph);

void bfs(Graph *graph, int n);

void dfs(Graph *graph, int n);

int degree(Graph *graph, int node);

int indegree(Graph *graph, int node);

int outdegree(Graph *graph, int node);

#endif // GRAPH_H_INCLUDED
