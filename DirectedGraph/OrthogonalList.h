//
// Created by 梁竞 on 2017/11/23.
//

#ifndef DIRECTEDGRAPH_ORTHOGONALLIST_H
#define DIRECTEDGRAPH_ORTHOGONALLIST_H

#endif //DIRECTEDGRAPH_ORTHOGONALLIST_H

//十字链表
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int EdgeType; //权值类型(可自定义)
typedef char VexType; //顶点数据类型(可自定义)
typedef int Status;

//边表结点结构
typedef struct ArcNode {
    int tailvex;  //表示弧起点在顶点表的下标
    int headvex;  //表示弧终点在顶点表的下标
    struct ArcNode *headlink; //表示入边表指针域，指向终点相同的下一条边
    struct ArcNode *taillink; //表示出边表指针域，指向起点相同的下一条边
    EdgeType weight; //权值
} ArcNode;


//顶点表结点结构
typedef struct VexNode {
    VexType data; //数据类型
    ArcNode *firstin; //入边表头指针，指向该顶点的入边表中的第一个结点
    ArcNode *firstout; //出边表头指针，指向该顶点的出边表中的第一个结点
} VexNode;


//有向图的十字链表结构
typedef struct {
    VexNode vexList[10];
    int vexNum, arcNum;  //有向图当前的顶点数和弧数
} OLGraph;

void printVexNode(OLGraph *G);
void displayArc(OLGraph *G);
int vexDegree(OLGraph *G, int vex);

/**
 * function:有向图的十字链表结构的创建
 * @param G
 * @return
 */
Status createOLGraph(OLGraph *G) {

    int i, j, w, k;
    ArcNode *p;
    printf("请输入有向图的顶点数以及弧数：");
    scanf("%d,%d", &G->vexNum, &G->arcNum);
    getchar();

    //读入顶点信息
    for (i = 0; i < G->vexNum; i++) {

        printf("请输入顶点的值：");
        scanf("%c", &G->vexList[i].data);

        //起始时，将各个顶点的出边表头指针和入边表头指针初始化为空
        G->vexList[i].firstin = NULL;
        G->vexList[i].firstout = NULL;
        getchar();
    }

    //打印顶点表信息
    printVexNode(G);
    printf("\n");

    //读入边的信息以及权值
    for (k = 0; k < G->arcNum; k++) {

        printf("请输入边（vi,vj）的顶点序号以及权值w:");
        scanf("%d,%d,%d", &i, &j,&w);
        getchar();

        p = (ArcNode *) malloc(sizeof(ArcNode)); //分配内存空间
        p->tailvex = i;
        p->headvex = j;
        p->weight = w;
        p->headlink = G->vexList[j].firstin;
        p->taillink = G->vexList[i].firstout;
        G->vexList[j].firstin = G->vexList[i].firstout = p;  //完成入弧和出弧链头的插入(关键)
    }

    return OK;
};


/**
 * function:打印顶点表信息
 * @param G
 */
void printVexNode(OLGraph *G) {

    printf("当前的顶点表信息：\n");
    for (int j = 0; j < G->vexNum; j++) {
        printf("v%d=%c ", j, G->vexList[j].data);
    }
}


/**
 * function:打印有向图中的各条边信息
 * @param G
 */
void displayArc(OLGraph *G) {

    ArcNode *p;
    for (int i = 0; i < G->vexNum; i++) {

        //循环打印以每个顶点为起点的各条边即可显示出有向图中的所有边信息
        p = G->vexList[i].firstout;
        while (p) {
            printf("<%c,%c,权值：%d>", G->vexList[p->tailvex].data, G->vexList[p->headvex].data, p->weight);
            p = p->taillink;
        }
        printf("\n");
    }
}


/**
 * function:求某个顶点的度
 * @param G
 * @param vex
 * @return
 */
int vexDegree(OLGraph *G, int vex) {

    int id; //入度
    int od; //出度

    ArcNode *in = G->vexList[vex].firstin; //该顶点的入边表头指针
    ArcNode *out = G->vexList[vex].firstout; //该顶点的出边表头指针

    //计算入度
    while (in) {
        ++id;
        in = in->headlink;
    }

    //计算出度
    while (out) {
        ++od;
        out = out->taillink;
    }

    return id + od; //该顶点的度
}



