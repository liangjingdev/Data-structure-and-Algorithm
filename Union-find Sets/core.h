//
// Created by 梁竞 on 2017/11/21.
//

#ifndef UNION_FIND_SETS_CORE_H
#define UNION_FIND_SETS_CORE_H

#endif //UNION_FIND_SETS_CORE_H

#include <stdio.h>

void MakeSet(int x);

int Find(int x);

int father[10];  /* father[x]表示x的父节点*/
int rank[10];    /* rank[x]表示x的秩*/

/**
 * function:初始化集合以及其秩
 *          起始，每个数据元素都是一个集合。每一个元素的祖先结点也是它本身。秩为0。
 * @param x
 */
void MakeSet(int x) {

    for (int i = 0; i < x; i++) {
        father[i] = i;  //根据实际情况指定的父节点可变化
        rank[i] = 0;   //根据实际情况初始化秩也有所变化
    }
}


/**
 * function: 查找x元素所在的集合,回溯时压缩路径
 * @param x
 */
int Find(int x) {

    if (x != father[x]) {
        father[x] = Find(father[x]);
    }

    return father[x];
}


/**
 * function:按秩合并x,y所在的集合
 * @param x
 * @param y
 */
void Union(int x, int y) {

    x = Find(x); //寻找该元素结点的祖先结点
    y = Find(y);  //寻找该元素结点的祖先结点

    //判断这两个元素的祖先是否相同，也即是判断这两个元素是否在同一个集合里面。
    if (x == y)
        return;;

    //重要的是祖先的rank，所以只用修改祖先的rank就可以了，子节点的rank不用管
    //合并两棵树树时，将高度较小的树的根指向高度较大的树可以保证合并后的树的高度上界不再增加。若高度相等，则合并后的树高度加一
    if (rank[x] > rank[y]) {
        father[y] = x;
    } else {
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
        father[x] = y;
    }
}

