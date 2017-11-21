#include <stdio.h>
#include "core.h"


int main() {

    int max = 10;  //元素个数
    MakeSet(max);  //初始化集合

    printf("打印各集合中的元素（起始时，每个元素为一个集合，father[x]=x（即祖先结点就是自己）):\n");
    //打印各集合中的元素（起始时，每个元素为一个集合，father[x]=x（即祖先结点就是自己））
    for (int i = 0; i < max; i++) {
        printf("%d ", father[i]);
    }
    printf("\n");

    //将只含有元素3的集合和只含有元素4的集合进行合并.合并后3和4为一个集合
    Union(3, 4);

    printf("将只含有元素3的集合和只含有元素4的集合进行合并,合并后的结果:\n");
    for (int i = 0; i < max; i++) {
        printf("%d ", father[i]);
    }
    printf("\n");

    Union(7, 8);
    printf("将只含有元素7的集合和只含有元素8的集合进行合并,合并后的结果:\n");
    for (int i = 0; i < max; i++) {
        printf("%d ", father[i]);
    }
    printf("\n");

    //此时一个集合中含有3和4两个元素，并且4为祖先结点。另外一个集合中含有7和8两个元素且8为祖先结点。现在将元素3和元素8进行合并。
    Union(3, 8);
    printf("此时一个集合中含有3和4两个元素且4为祖先结点。另外一个集合中含有7和8两个元素且8为祖先结点。现在将元素3和元素8进行合并。结果：\n");
    for (int i = 0; i < max; i++) {
        printf("%d ", father[i]);
    }
    printf("\n");

    printf("打印两个秩相同的集合合并后新的集合的秩：%d\n", rank[8]);

    //查找元素3的祖先结点，查找时会进行路径压缩，之后father[3]会直接指向8，即8为元素3的直接父节点且为祖先结点。
    printf("查找元素3的祖先结点，查找时会进行路径压缩，之后father[3]会直接指向8，即8为元素3的直接父节点且为祖先结点。\n");
    int fth = Find(3);
    printf("查找后元素3的父结点为：%d、\n", fth);

    printf("最后打印结果为：\n");
    for (int i = 0; i < max; i++) {
        printf("%d ", father[i]);
    }

    return 0;
}