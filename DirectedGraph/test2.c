//
// Created by 梁竞 on 2017/11/23.
//

#include <stdio.h>
#include "AdjacencyList.h"

//有向图的邻接表结构测试
int main() {

    int i, j;
    GraphAdjList G;
    createALGraph(&G);

    //判断两个顶点之间是否存在边
    printf("现在需要判断两个顶点之间是否存在边，请输入两个顶点的序号i,j:");
    scanf("%d,%d", &i, &j);
    int result = judgeEdge(i, j, &G);
    printf("结果：%d\n", result);

    printf("测试有向图的邻接表结构的深度优先遍历算法：");
    DFSTraverse(G);
    printf("\n");

    printf("测试有向图的邻接表结构的广度优先遍历算法：");
    BFSTraverse(G);
    printf("\n");

    return 0;

}