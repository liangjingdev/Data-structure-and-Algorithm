#include <stdio.h>
#include "AdjacencyList.h"

int main() {

    int i, j;
    GraphAdjList G;
    createALGraph(&G);

    //判断两个顶点之间是否存在边
    printf("现在需要判断连个顶点之间是否存在边，请输入两个顶点的序号i,j:");
    scanf("%d,%d", &i, &j);
    int result = judgeEdge(i, j, &G);
    printf("结果：%d",result);

    return 0;

}