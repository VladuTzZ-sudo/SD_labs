#include <stdio.h>
#include <stdlib.h>

#include "graph/graph.h"

int main()
{
	int type = TYPE_DIRECTED;
	int nodes;
	int edges;
	fscanf(stdin, "%d%d", &nodes, &edges);
	Graph *g = createGraph(type, nodes, edges, stdin);
	for (int i = 0; i < nodes; i++) {
		printf("%d [%d]: ", i, g->adj[i][NR_NEIGHBOURS]);
		for (int j = 0; j < g->adj[i][NR_NEIGHBOURS]; j++) {
			printf("%d ", g->adj[i][j]);
		}
		printf("\n");
	}
	int start;
	scanf("%d", &start);
	bfs(g, start);
	dfs(g, start);
    destroyGraph(g);
    return 0;
}
