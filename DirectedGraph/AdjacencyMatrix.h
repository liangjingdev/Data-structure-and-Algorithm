//
// Created by 梁竞 on 2017/11/23.
//

#ifndef DIRECTEDGRAPH_ADJACENCYMATRIX_H
#define DIRECTEDGRAPH_ADJACENCYMATRIX_H

#endif //DIRECTEDGRAPH_ADJACENCYMATRIX_H

#include <stdio.h>

typedef char VertexType;  //顶点类型（可自定义）
typedef int EdgeType;  //边上的权值类型（可自定义）
typedef int Boolean;
typedef int Status;
#define INFINITY 65535 //用来表示两结点之间不存在边
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROE 0
#define MAXSIZE 10 //存储空间初始分配量


//有向图的邻接矩阵存储结构(最大顶点数可自定义)
typedef struct {
    VertexType vexs[10]; //顶点表
    EdgeType arc[10][10]; //邻接矩阵，可看作边表
    int numNodes, numEdges; //图中当前的顶点数和边数
} DGraph;


//邻接矩阵的广度优先遍历算法需要利用到的队列结构(循环队列的顺序存储结构)
typedef struct {
    int data[10];
    int front;  //头指针
    int rear;   //尾指针，若队列不为空，指向队尾元素的下一个位置
} Queue;

void createDGraph(DGraph *G);
void DFS(DGraph G, int i);
void DFSTraverse(DGraph G);
void BFSTraverse(DGraph G);
Status initQueue(Queue *Q);
Status QueueEmpty(Queue Q);
Status EnQueue(Queue *Q, int e);
Status DeQueue(Queue *Q, int *e);


/**
 * function:建立有向图的邻接矩阵表示
 * @param G
 */
void createDGraph(DGraph *G) {

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


//访问标志的数组
Boolean visited[10];

/**
 * function:有向图的邻接矩阵结构的深度优先遍历递归算法
 * @param G
 * @param i
 */
void DFS(DGraph G, int i) {

    int j;
    visited[i] = TRUE;
    printf("%c", G.vexs[i]); //打印顶点
    for (j = 0; j < G.numNodes; j++) {
        if (G.arc[i][j] != INFINITY && !visited[j])
            DFS(G, j); //对未访问的邻接顶点进行递归调用
    }

}

/**
 * function:有向图的邻接矩阵结构的深度优先遍历操作
 * @param G
 */
void DFSTraverse(DGraph G) {

    int i;

    //初始所有顶点都是未访问状态
    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    for (i = 0; i < G.numNodes; i++) {
        if (!visited[i])
            DFS(G, i); //对未访问的顶点进行调用DFS访问，若该图是连通图，则只会调用一次
    }
}


/**
 * function:有向图的邻接矩阵结构的广度优先遍历算法
 * @param G
 */
void BFSTraverse(DGraph G) {

    int i, j;
    Queue Q;

    //初始化一个辅助用的队列
    initQueue(&Q);

    for (i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }

    //对每个顶点做循环
    for (i = 0; i < G.numNodes; i++) {

        //若是没有访问过的就处理
        if (!visited[i]) {

            //设置当前顶点访问过
            visited[i] = TRUE;
            printf("%c ", G.vexs[i]); //打印顶点
            EnQueue(&Q, i); //将该顶点入队列

            //若该队列不为空
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i);
                for (j = 0; j < G.numNodes; j++) {
                    if (G.arc[i][j] != INFINITY && !visited[j]) {
                        visited[j] = TRUE;
                        printf("%c ", G.vexs[j]);
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }
}

/**
 * function:初始化一个空队列
 * @param Q
 * @return
 */
Status initQueue(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
    return OK;
}


/**
 * function:若队列Q为空队列，则返回TRUE，否则返回FALSE
 * @param Q
 * @return
 */
Status QueueEmpty(Queue Q) {

    //队列为空的标志
    if (Q.front == Q.rear) {
        return TRUE;
    } else {
        return FALSE;
    }

}


/**
 * function:若队列未满，则插入元素e为Q新的队尾元素
 * @param Q
 * @param e
 * @return
 */
Status EnQueue(Queue *Q, int e) {

    //队列满的判断(保留一个元素空间，也就是说，当队列满时，数组中还有一个空闲单元。此时就认为队列已经满了)
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROE;

    Q->data[Q->rear] = e; //将元素e赋值给队尾
    Q->rear = (Q->rear + 1) % MAXSIZE; //rear指针向后移一位置.若到最后则转到数组头部o
    return OK;
}


/**
 * function:若队列不为空，则删除Q中队头元素，用e返回其值
 * @param Q
 * @param e
 * @return
 */
Status DeQueue(Queue *Q, int *e) {

    //队列空的判断
    if (Q->front == Q->rear)
        return ERROE;
    *e = Q->data[Q->front];  //将队头元素赋值给e
    Q->front = (Q->front + 1) % MAXSIZE; //front指针向后移一位。若到最后则会转到数组头部
    return OK;
}



