#include <stdio.h>
#include <stdlib.h>

#include "graph/graph.h"

/* INPUT
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
0
*/

/* OUTPUT UNDIRECTED
0 [2]: (1, 4) (7, 8)
1 [3]: (0, 4) (2, 8) (7, 11)
2 [4]: (1, 8) (3, 7) (8, 2) (5, 4)
3 [3]: (2, 7) (4, 9) (5, 14)
4 [2]: (3, 9) (5, 10)
5 [4]: (2, 4) (3, 14) (4, 10) (6, 2)
6 [3]: (5, 2) (7, 1) (8, 6)
7 [4]: (0, 8) (1, 11) (6, 1) (8, 7)
8 [3]: (2, 2) (6, 6) (7, 7)
0 1 7 2 6 8 3 5 4
0 7 8 2 5 4 3 6 1
0 7 8 6 5 4 3 2 1
outdegree(0) = 2
outdegree(1) = 3
outdegree(2) = 4
outdegree(3) = 3
outdegree(4) = 2
outdegree(5) = 4
outdegree(6) = 3
outdegree(7) = 4
outdegree(8) = 3
0 (0): 0
1 (4): 0 1
2 (12): 0 1 2
3 (19): 0 1 2 3
4 (21): 0 7 6 5 4
5 (11): 0 7 6 5
6 (9): 0 7 6
7 (8): 0 7
8 (14): 0 1 2 8
*/

/* OUTPUT DIRECTED
0 [2]: (1, 4) (7, 8)
1 [2]: (2, 8) (7, 11)
2 [3]: (3, 7) (8, 2) (5, 4)
3 [2]: (4, 9) (5, 14)
4 [1]: (5, 10)
5 [1]: (6, 2)
6 [2]: (7, 1) (8, 6)
7 [1]: (8, 7)
8 [0]:
0
0 1 7 2 8 3 5 4 6
0 7 8 1 2 5 6 3 4
0 7 8 1 2 5 6 3 4
outdegree(0) = 2
outdegree(1) = 2
outdegree(2) = 3
outdegree(3) = 2
outdegree(4) = 1
outdegree(5) = 1
outdegree(6) = 2
outdegree(7) = 1
outdegree(8) = 0
0 (0): 0
1 (4): 0 1
2 (12): 0 1 2
3 (19): 0 1 2 3
4 (28): 0 1 2 3 4
5 (16): 0 1 2 5
6 (18): 0 1 2 5 6
7 (8): 0 7
8 (14): 0 1 2 8
*/

int main()
{
	int type = TYPE_DIRECTED;
	int nodes;
	int edges;
	fscanf(stdin, "%d%d", &nodes, &edges);
	Graph *g = createGraph(type, nodes, edges, stdin);
	for (int i = 0; i < nodes; i++) {
		printf("%d [%d]: ", i, g->adj[i][NR_NEIGHBOURS]);
		for (int j = 0; j < g->adj[i][NR_NEIGHBOURS].n; j++) {
			printf("(%d, %d) ", g->adj[i][j].n, g->adj[i][j].w);
		}
		printf("\n");
	}
	int start;
	topological(g);
	scanf("%d", &start);
	bfs(g, start);
	dfs(g, start);
	dfs_rec(g, start);
	for (int i = 0; i < g->nodes; i++) {
		printf("outdegree(%d) = %d\n", i, outdegree(g, i));
	}
	dijkstra(g, start);
	prim(g);
	kruskal(g);
    destroyGraph(g);
    return 0;
}
