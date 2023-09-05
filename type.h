#pragma once
using namespace std;

#define UNASSIGNED 0
#define ASSIGNED 1
#define SATISFIED 1
#define UNSATISFIED 0
//文字链表结点定义
typedef struct node {
	struct node* next;
	struct node* rightliter;
	int data;
	int is_exit; //1表示还在 0代表已被删除
	int is_satisfied;
}lit, *litnode;

//子句结构体定义(优化前)
typedef struct clause {
	int length;        //每个子句中的文字数
	litnode head;      //子句中文字链表的头节点
}clause, * clausenode;

//子句链表结点定义（优化前）
typedef struct cnode {
	struct cnode* next;    //下一子句
	clause* c;              //当前结点子句
	int is_satisfied; //1表示当前子句已被满足 0表示当前子句仍未被满足
	int is_exit; //1表示还在 0代表已经被删除
}cnode, * clink;

//文字定义（优化后）采用数组存储子句头和文字
typedef struct literal_information {
	int* literal_clause; //文字所在子句在公式中的编号数列
	int* literal_pos_in_clause;//文字在该子句中的位置
	int n_number; //该文字个数
	int is_assigned;//是否已经被赋值
}liter_information;

typedef struct clause_information {//子句结构
	int* literals;//子句中的文字
	int* literals_is_assigned;//每一个文字是否被赋值过了
	int length_current;//现在的字句长度
	int length_original;//最初子句长度
	int is_satisfied;//是否满足 NO OR YES true 
	int unit_clause_literal;//存储单子句文字中，未赋值文字
}clause_information;