#include <stdio.h>
#include "AdjacencyMatrix.h"


//图的邻接矩阵结构测试
int main() {

    MGraph G;
    createMGraph(&G);
    printf("\n");

    printf("图的邻接矩阵结构的深度优先遍历算法：");
    DFSTraverse(G);
    printf("\n");

    printf("图的邻接矩阵的广度优先遍历算法：");
    BFSTraverse(G);
    printf("\n");

}