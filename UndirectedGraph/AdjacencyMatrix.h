//
// Created by 梁竞 on 2017/11/21.
//

#ifndef UNDIRECTEDGRAPH_CREATEMGRAPH1_H
#define UNDIRECTEDGRAPH_CREATEMGRAPH1_H

#endif //UNDIRECTEDGRAPH_CREATEMGRAPH1_H

#include <stdio.h>

typedef char VertexType;  //顶点类型（可自定义）
typedef int EdgeType;  //边上的权值类型（可自定义）
#define INFINITY 65535; //用来表示两结点之间不存在边


//图的邻接矩阵存储结构(最大顶点数可自定义)
typedef struct {
    VertexType vexs[100]; //顶点表
    EdgeType arc[100][100]; //邻接矩阵，可看作边表
    int numNodes, numEdges; //图中当前的顶点数和边数
} MGraph;


/**
 * function:建立无向图的邻接矩阵表示
 * @param G
 */
void createMGraph(MGraph *G) {

    int i, j, k, w;
    printf("请输入最大顶点数和边数：");
    scanf("%d,%d", &G->numNodes, &G->numEdges); //输入图的顶点数和边数
    getchar();

    //添加顶点到顶点表
    for (i = 0; i < G->numNodes; i++) {
        printf("请输入顶点(字符表示)：");
        scanf("%c", &G->vexs[i]);
        getchar();
    }

    printf("显示当前顶点表：");
    //显示顶点表
    for (i = 0; i < G->numNodes; i++) {
        printf("v%d=%c ", i, G->vexs[i]);
    }
    printf("\n");

    //初始化邻接矩阵
    for (i = 0; i < G->numNodes; i++)
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = INFINITY;
        }


    //读入numEdges条边，建立邻接矩阵（INFINITY表示两顶点之间没有边，k的值表示两顶点间有边且值代表权值）
    for (k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi,vj)上的下标i，下标j和权w:");
        scanf("%d,%d,%d", &i, &j, &w); //输入边(vi,vj)上的权
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j]; //注意：无向图的邻接矩阵是对称的
    }


    printf("打印当前边表信息：\n");
    //打印边表信息
    for (i = 0; i < G->numNodes; i++)
        for (j = 0; j < G->numNodes; j++) {
            printf("(v%d,v%d)=%d ", i, j, G->arc[i][j]);
            if (j == G->numNodes - 1) {
                printf("\n");
            }
        }
}



