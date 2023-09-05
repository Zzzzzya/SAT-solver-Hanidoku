#pragma once
using namespace std;

#define UNASSIGNED 0
#define ASSIGNED 1
#define SATISFIED 1
#define UNSATISFIED 0
//���������㶨��
typedef struct node {
	struct node* next;
	struct node* rightliter;
	int data;
	int is_exit; //1��ʾ���� 0�����ѱ�ɾ��
	int is_satisfied;
}lit, *litnode;

//�Ӿ�ṹ�嶨��(�Ż�ǰ)
typedef struct clause {
	int length;        //ÿ���Ӿ��е�������
	litnode head;      //�Ӿ������������ͷ�ڵ�
}clause, * clausenode;

//�Ӿ������㶨�壨�Ż�ǰ��
typedef struct cnode {
	struct cnode* next;    //��һ�Ӿ�
	clause* c;              //��ǰ����Ӿ�
	int is_satisfied; //1��ʾ��ǰ�Ӿ��ѱ����� 0��ʾ��ǰ�Ӿ���δ������
	int is_exit; //1��ʾ���� 0�����Ѿ���ɾ��
}cnode, * clink;

//���ֶ��壨�Ż��󣩲�������洢�Ӿ�ͷ������
typedef struct literal_information {
	int* literal_clause; //���������Ӿ��ڹ�ʽ�еı������
	int* literal_pos_in_clause;//�����ڸ��Ӿ��е�λ��
	int n_number; //�����ָ���
	int is_assigned;//�Ƿ��Ѿ�����ֵ
}liter_information;

typedef struct clause_information {//�Ӿ�ṹ
	int* literals;//�Ӿ��е�����
	int* literals_is_assigned;//ÿһ�������Ƿ񱻸�ֵ����
	int length_current;//���ڵ��־䳤��
	int length_original;//����Ӿ䳤��
	int is_satisfied;//�Ƿ����� NO OR YES true 
	int unit_clause_literal;//�洢���Ӿ������У�δ��ֵ����
}clause_information;