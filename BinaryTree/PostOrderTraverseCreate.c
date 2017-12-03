/**
 * fnction:扩展后序遍历序列来构建一棵二叉树
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10010
#define LEN sizeof(struct BTree)
char string[MAX];
int len;

struct BTree
{
char s;
struct BTree *rchild,*lchild;
};

void create_BTree(struct BTree* *T)
{
if(string[--len]=='#') (*T)=NULL;
else
{
(*T)=(struct BTree*)malloc(LEN); (*T)->s=string[len];
create_BTree( &((*T)->rchild) );
create_BTree( &((*T)->lchild) );
}
}

void travel(struct BTree *T)
{
if(!T) return ;
travel(T->lchild);
travel(T->rchild);
printf("%c",T->s);
}
int main()
{
struct BTree *T;
while(scanf("%s",string)!=EOF) //读入扩展后序遍历序列
{
len=strlen(string);
create_BTree(&T); //创建二叉树
travel(T); //后序遍历二叉树
printf("\n");
} 
return 0;
}