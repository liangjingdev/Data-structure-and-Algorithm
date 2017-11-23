//
// Created by 梁竞 on 2017/11/23.
//

#include <stdio.h>
#include "OrthogonalList.h"

//有向图的十字链表结构测试
int main() {

    int i;
    OLGraph G;
    createOLGraph(&G);

    //打印该有向图当中的各条边信息
    printf("该有向图中的各条边信息：\n");
    displayArc(&G);

    //求某个顶点的度
    printf("现在求某个顶点的度，请输入该顶点的序号值:");
    scanf("%d", &i);
    int k = vexDegree(&G, i);
    printf("顶点%c的度为%d",G.vexList[i].data,k);
}
