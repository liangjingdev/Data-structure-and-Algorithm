#include <stdio.h>
#include "AdjacencyMatrix.h"


//有向图的邻接矩阵结构测试
int main() {

    DGraph G;
    createDGraph(&G);
    printf("\n");

    printf("有向图的邻接矩阵结构的深度优先遍历算法：");
    DFSTraverse(G);
    printf("\n");

    printf("有向图的邻接矩阵的广度优先遍历算法：");
    BFSTraverse(G);
    printf("\n");
    return 0;
}