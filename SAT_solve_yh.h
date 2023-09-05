#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string.h>
#include"type.h"
using namespace std;
//B:\An\sy\S\problem11-100.cnf
//B:\An\sy\S\problem9-100.cnf
//B:\An\sy\S\tst_v25_c100.cnf
//B:\An\sy\S\problem8-50.cnf
//B:\An\sy\S\1.txt
//B:\An\sy\SATsolver\SAT-example\unsatisfied\eu-rand_net60-25-10.shuffled-3000.cnf
//B:\An\sy\SATsolver\SAT-example\based\1\unsat-5cnf-30.cnf


//B:\An\sy\SATsolver\SAT-example\satisfied\M\problem5-200.cnf
// 
//B:\An\sy\SATsolver\SAT-example\based\2\ais10.cnf
//B:\An\sy\SATsolver\SAT-example\satisfied\M\sud00861.cnf
//B:\An\sy\SATsolver\SAT-example\satisfied\M\bart17.shuffled-231.cnf
//B:\An\sy\SATsolver\SAT-example\based\1\unsat-5cnf-30.cnf
//B:\An\sy\SATsolver\SAT-example\based\2\sud00009.cnf

//B:\An\sy\SATsolver\SAT-example\satisfied\L\eh-dp04s04.shuffled-1075.cnf

class SAT_solver_yh {
public:
	long long BIDX = 0;//记录回溯层数
	int num_liter = 0, num_clause = 0;//记录文字数和子句数
	int num_clause_current = 0;

	

	

	
	liter_information liter_info[10000][2];// 1为正文字 0为－文字 文字信息表
	clause_information clause_info[15000];//  子句表
	clock_t start_time, end_time;//

	//栈定义
	//子句栈
	pair<int,int> clause_stack[1600000];
	int top_clause_stack = -1;
	//文字赋值栈
	pair<int,int> liter_change_stack[1000000];
	int top_liter_change_stack=-1;
	//文字删除栈
	pair<int,pair<int,int> > liter_delete_stack[1000000];
	int top_liter_delete_stack=-1;

	//单文字存储栈
	int unit_liter[100000];
	int top_unit_liter = -1;


    char filename[200];//文件名
	int* fzb = nullptr;   //赋值表
	int* ans = nullptr;   //答案赋值表
	pair<int, int> getlr(int i, int j)//根据坐标返回第几行第几个
	{
		if (i <= 4)return{ i + 1,j + 1 };
		else if (i > 4)
		{
			return { i + 1,j - i + 5 };
		}
		return { -1,-1 };
	}
    void createfromfile()
	{
		//打开文件
		FILE* fp;

        fp = fopen("./resource/cnfinit.cnf", "r");

		
		if (!fp)
		{
            printf("这里文件读取失败！");
			return;
		}


		//读取文件，过滤注释
		char str[100];
		fgets(str, 100, fp);
		while (str[0] == 'c')
		{
			fgets(str, 100, fp);
		}

		//读取文字个数和子句个数
		int bi = 6;
		while (str[bi] != ' ')
		{
			num_liter = num_liter * 10 + str[bi] - '0';
			bi++;
		}
		bi++;
		while (bi < strlen(str) - 1)
		{
			num_clause = num_clause * 10 + str[bi] - '0';
			bi++;
		}	
		num_clause_current = num_clause;


		//初始化liter_info数组
		for (int i = 1; i <= num_liter; i++)
		{
			for (int type = 0; type < 2; type++)
			{
				liter_info[i][type].n_number = 0;
				liter_info[i][type].is_assigned = UNASSIGNED;
				liter_info[i][type].literal_clause = (int*)malloc((num_clause+5) * sizeof(int));
				liter_info[i][type].literal_pos_in_clause = (int*)malloc((num_clause + 5) * sizeof(int));
			}
		}
		
		//初始化clause_info数组
		for (int i = 0; i < num_clause+1000; i++)
		{
			clause_info[i].length_original = 0;
			clause_info[i].length_current = 0;
			clause_info[i].is_satisfied = UNSATISFIED;
			clause_info[i].unit_clause_literal = 0;
			clause_info[i].literals = (int*)malloc((2 * num_liter + 1) * sizeof(int));
			clause_info[i].literals_is_assigned = (int*)malloc((2 * num_liter + 1) * sizeof(int));

		}


		//创建子句和文字为链表

		int curliter;         //当前指向的文字
		int curclause;

		for (curclause = 0; curclause < num_clause; curclause++)   //读子句
		{
			//每个子句中读文字
			fscanf(fp, "%d", &curliter);
			while (curliter != 0)
			{
				int type = (curliter > 0) ? 1 : 0;
				liter_information* cur_liter_info = &liter_info[abs(curliter)][type];
				clause_information* cur_clause_info = &clause_info[curclause];

				cur_clause_info->literals[cur_clause_info->length_current] = curliter;
				cur_clause_info->literals_is_assigned[cur_clause_info->length_current] = UNASSIGNED;
				
				cur_liter_info->literal_clause[cur_liter_info->n_number] = curclause;
				cur_liter_info->literal_pos_in_clause[cur_liter_info->n_number] = cur_clause_info->length_current;

				cur_clause_info->length_current++;
				cur_clause_info->length_original++;
				cur_liter_info->n_number++;


				
				fscanf(fp, "%d", &curliter);
			}

		}

		fclose(fp);
    }

    void createfromfile(char* inputfilename)
    {
        //打开文件
        FILE* fp;

        for(int i=0;i<=strlen(inputfilename);i++)filename[i]=inputfilename[i];
        fp = fopen(inputfilename, "r");


        if (!fp)
        {
            printf("文件读取失败1！");
            return;
        }


        //读取文件，过滤注释
        char str[100];
        fgets(str, 100, fp);
        while (str[0] == 'c')
        {
            fgets(str, 100, fp);
        }

        //读取文字个数和子句个数
        int bi = 6;
        while (str[bi] != ' ')
        {
            num_liter = num_liter * 10 + str[bi] - '0';
            bi++;
        }
        bi++;
        while (bi < strlen(str) - 1)
        {
            num_clause = num_clause * 10 + str[bi] - '0';
            bi++;
        }
        num_clause_current = num_clause;


        //初始化liter_info数组
        for (int i = 1; i <= num_liter; i++)
        {
            for (int type = 0; type < 2; type++)
            {
                liter_info[i][type].n_number = 0;
                liter_info[i][type].is_assigned = UNASSIGNED;
                liter_info[i][type].literal_clause = (int*)malloc((num_clause+5) * sizeof(int));
                liter_info[i][type].literal_pos_in_clause = (int*)malloc((num_clause + 5) * sizeof(int));
            }
        }

        //初始化clause_info数组
        for (int i = 0; i < num_clause+1000; i++)
        {
            clause_info[i].length_original = 0;
            clause_info[i].length_current = 0;
            clause_info[i].is_satisfied = UNSATISFIED;
            clause_info[i].unit_clause_literal = 0;
            clause_info[i].literals = (int*)malloc((2 * num_liter + 1) * sizeof(int));
            clause_info[i].literals_is_assigned = (int*)malloc((2 * num_liter + 1) * sizeof(int));

        }


        //创建子句和文字为链表

        int curliter;         //当前指向的文字
        int curclause;

        for (curclause = 0; curclause < num_clause; curclause++)   //读子句
        {
            //每个子句中读文字
            fscanf(fp, "%d", &curliter);
            while (curliter != 0)
            {
                int type = (curliter > 0) ? 1 : 0;
                liter_information* cur_liter_info = &liter_info[abs(curliter)][type];
                clause_information* cur_clause_info = &clause_info[curclause];

                cur_clause_info->literals[cur_clause_info->length_current] = curliter;
                cur_clause_info->literals_is_assigned[cur_clause_info->length_current] = UNASSIGNED;

                cur_liter_info->literal_clause[cur_liter_info->n_number] = curclause;
                cur_liter_info->literal_pos_in_clause[cur_liter_info->n_number] = cur_clause_info->length_current;

                cur_clause_info->length_current++;
                cur_clause_info->length_original++;
                cur_liter_info->n_number++;



                fscanf(fp, "%d", &curliter);
            }

        }

        fclose(fp);
    }

	void addcnf(int map[9][9])//通过地图初始条件增加cnf约束
	{
		for (int i = 0; i <= 4; i++)  //前五行
		{
			for (int j = 0; j <= 4 + i; j++)
			{
				if (map[i][j] ==0)continue;

				//添加约束
				pair<int, int> k = getlr(i, j);
				int liter=k.first * 100 + k.second * 10 + map[i][j]-110;
				clause_info[num_clause].literals[0] = liter;
				clause_info[num_clause].literals_is_assigned[0] = UNASSIGNED;
				
				liter_info[liter][1].literal_clause[liter_info[liter][1].n_number] = num_clause;
				liter_info[liter][1].literal_pos_in_clause[liter_info[liter][1].n_number] = 0;

				clause_info[num_clause].length_current++;
				clause_info[num_clause].length_original++;

				liter_info[liter][1].n_number++;

				num_clause++;
				num_clause_current++;
			}
		}

		for (int i = 5; i <= 8; i++)  //后四行
		{
			for (int j = i - 4; j <= 8; j++)
			{
				if (map[i][j] == 0)continue;
				pair<int, int> k = getlr(i, j);
				int liter = k.first * 100 + k.second * 10 + map[i][j] - 110;
				clause_info[num_clause].literals[0] = liter;
				clause_info[num_clause].literals_is_assigned[0] = UNASSIGNED;

				liter_info[liter][1].literal_clause[liter_info[liter][1].n_number] = num_clause;
				liter_info[liter][1].literal_pos_in_clause[liter_info[liter][1].n_number] = 0;

				clause_info[num_clause].length_current++;
				clause_info[num_clause].length_original++;

				liter_info[liter][1].n_number++;

				num_clause++;
				num_clause_current++;
			}
		}
		return;
	}
	

    int solve()//计算cnf问题
	{

		//初始化赋值表
		fzb = new int[num_liter + 10];
		ans = new int[num_liter + 10];
		for (int i = 0; i <= num_liter; i++)fzb[i] = 0;

		/*
		Travel(headclause);
		cout << endl;
		*/



		//文件存储操作
		char filename2[200];
		int len = strlen(filename);
		for (int i = 0; i < len - 3; i++)filename2[i] = filename[i];
		filename2[len - 3] = 'r';
		filename2[len - 2] = 'e';
		filename2[len - 1] = 's';
		filename2[len] = '\0';

		FILE* fp2 = fopen(filename2, "w");
		if (!fp2)
		{
			cout << "储存文件失败！";
            return -2;
		}


		//进行DPLL
		start_time = clock();
		int dpll = DPLL( 0, 0);
		end_time = clock();

		if (dpll == 1) {
			cout << "s 1" << endl;
			fprintf(fp2, "s 1\n");
		}
		else if (dpll == 0) {
			cout << "s 0" << endl;
			fprintf(fp2, "s 0\n");

			cout << "t " << (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000 << endl;
			fprintf(fp2, "t %d\n", (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000);

            return 0;
		}
		else if (dpll == -1)
		{
			cout << "s -1" << endl;
			fprintf(fp2, "s -1");
            return -1;
		}


		cout << "v ";
		fprintf(fp2, "v ");
		for (int i = 1; i <= num_liter; i++)
		{
			cout << ans[i] * i << " ";
			fprintf(fp2, "%d ", ans[i] * i);
		}

		cout << endl;
		fprintf(fp2, "\n");

		cout << "t " << (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000 << endl;
		fprintf(fp2, "t %d\n", (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000);

		cout << "文件已经成功存储在" << filename2 << "中";

		
		fclose(fp2);
        return 1;
	}

	void solve(int zya)
	{
		//针对于数独问题的求解
		fzb = new int[num_liter + 10];
		ans = new int[num_liter + 10];
		for (int i = 0; i <= num_liter; i++)fzb[i] = 0;

		/*
		Travel(headclause);
		cout << endl;
		*/
		int dpll = DPLL(0, 0);
		//if (dpll)cout << "答案已解出！";

		return;
	}

	//遍历打印链表
	void Travel()
	{
		for (int i = 0; i < num_clause; i++)
		{
			if (clause_info[i].is_satisfied == SATISFIED)continue;
			for (int j = 0; j < clause_info[i].length_original; j++)
			{
				if (clause_info[i].literals_is_assigned[j] == UNASSIGNED)cout << clause_info[i].literals[j] << " ";
			}
			cout << "0" << endl;
		}
		cout << endl;
		return;
	}

	void deleteSingleliter(int x, int idx) {
		//删除所有含有x的子句  以及删除所有子句中的反x 并压入栈中 打上标记curidx
		int type = 0;
		if (x > 0)type = 1;
		liter_information* x_info = &liter_info[abs(x)][type];
		//先删除含有x的所有子句
		for (int i = 0; i < x_info->n_number; i++)
		{
			clause_information* thisclause = &clause_info[x_info->literal_clause[i]];
			if (thisclause->is_satisfied == SATISFIED)continue;
			thisclause->is_satisfied = SATISFIED;
			num_clause_current--;

			//删除的子句压栈
			clause_stack[++top_clause_stack] = { idx,x_info->literal_clause[i] };
		}
		//再删除含有-x的所有文字
		liter_information* _x_info = &liter_info[abs(x)][1 - type];
		for (int i = 0; i < _x_info->n_number; i++)
		{
			clause_information* thisclause = &clause_info[_x_info->literal_clause[i]];
			if (thisclause->is_satisfied == SATISFIED)continue;
			thisclause->literals_is_assigned[_x_info->literal_pos_in_clause[i]] = ASSIGNED;
			thisclause->length_current--;

			//删除的文字压栈
			liter_delete_stack[++top_liter_delete_stack] = { idx,{_x_info->literal_clause[i],_x_info->literal_pos_in_clause[i]} };
		}


		x_info->is_assigned = ASSIGNED;
		_x_info->is_assigned = ASSIGNED;
		fzb[abs(x)] = x / abs(x);
		liter_change_stack[++top_liter_change_stack] = { idx,x };
		return;
	}

	bool emptyClauseExists() { //返回有无空子句
		for (int i = 0; i < num_clause; i++)
		{
			if (clause_info[i].length_current == 0)return true;//如果有子句当前长度为0 返回true
		}
		return false;
	}

	void recover(int idx)
	{
		//恢复改变的文字值
		while (liter_change_stack[top_liter_change_stack].first == idx)
		{
			int changed_x = liter_change_stack[top_liter_change_stack].second;
			liter_info[abs(changed_x)][0].is_assigned = UNASSIGNED;
			liter_info[abs(changed_x)][1].is_assigned = UNASSIGNED;
			fzb[abs(changed_x)] = 0;
			top_liter_change_stack--;
		}

		//恢复删除的子句
		while (clause_stack[top_clause_stack].first == idx)
		{
			int deleted_clause = clause_stack[top_clause_stack].second;
			clause_info[deleted_clause].is_satisfied = UNSATISFIED;
			num_clause_current++;
			top_clause_stack--;
		}

		//恢复删除的单字
		while (liter_delete_stack[top_liter_delete_stack].first == idx)
		{
			int idx_of_clause = liter_delete_stack[top_liter_delete_stack].second.first;
			int idx_of_liter = liter_delete_stack[top_liter_delete_stack].second.second;
			clause_info[idx_of_clause].length_current++;
			clause_info[idx_of_clause].literals_is_assigned[idx_of_liter]=UNASSIGNED;
			top_liter_delete_stack--;
		}
	}


	int DPLL(int x, int idx)
	{
		//x代表将x赋值为1进行dpll idx为当前DPLL编号

		//cout << "dpll:" << x << endl;

		//第一步 按照x赋值进行修改
		if (x!=0)
		{
			deleteSingleliter(x, idx);
			/*
			cout << "更改" << x << endl;
			Travel(chead);
			*/
		}

		//Travel();
		//for (int i = 1; i <= num_liter; i++)cout << fzb[i] << " ";
		//cout << endl;

		//判断 
		if (is_sentence_satisfied())//如果公式被满足 则结束
		{
			for (int i = 1; i <= num_liter; i++)ans[i] = fzb[i];
			return true;//如果整个公式被满足 说明一切子句被满足返回true
		}
		else if (emptyClauseExists())
		{
			//cout << "YES";
			return false;//如果公式中含有空句子 说明有句子无法被满足 返回false;
		}

		//第二步 单子句传播
		int Singleliter = SingleliterExit();
		while (Singleliter)
		{
			deleteSingleliter(Singleliter,idx);

			
			//cout << "删除单字句" << Singleliter<<endl;
			//Travel();
			//for (int i = 1; i <= num_liter; i++)cout << fzb[i] << " ";

			//判断 
			if (is_sentence_satisfied())//如果公式被满足 则结束
			{
				for (int i = 1; i <= num_liter; i++)ans[i] = fzb[i];
				return true;//如果整个公式被满足 说明一切子句被满足返回true
			}
			else if (emptyClauseExists())
			{
				//cout << "YES";
				return false;//如果公式中含有空句子 说明有句子无法被满足 返回false;
			}

			Singleliter = SingleliterExit();
		}

		//第二步 按照策略选取一个数进行赋值
		int selectedliter = GetMinQ();

		BIDX++;
		idx = BIDX;
		int dpll1 = DPLL(selectedliter,idx);
		if (dpll1 == 1)return 1;
		else if (dpll1 == -1)return -1;
		recover(idx);
		//回溯出栈
		
		BIDX--;
		/*
		cout << "恢复";
		Travel(chead);
		*/

		BIDX++;
		idx = BIDX;
		dpll1 = DPLL(-selectedliter, idx);
		if (dpll1 == 1)return 1;
		else if (dpll1 == -1)return -1;
		recover(idx);
		
		
		BIDX--;
		/*
		cout << "恢复";
		Travel(chead);
		*/

		return 0;
	}


	int get_min_length() {//找到所有未满足子句中最短子句的长度
		int min_length = 0x3f3f3f3f;
		for (int i = 0; i < num_clause; i++)
		{
			if (clause_info[i].is_satisfied == SATISFIED)continue;
			if (clause_info[i].length_current < min_length)
			{
				min_length = clause_info[i].length_current;
			}
		}
		
		return min_length;
	}
	
	void get_weight(int x, int k, int& s,int& t) {
		s = t = 0;
		for (int j = 0; j < liter_info[x][1].n_number; ++j) {
			int c = liter_info[x][1].literal_clause[j];//子句序号
			if (clause_info[c].length_current == k)
				s += 1 - clause_info[c].is_satisfied;
		}
		for (int j = 0; j < liter_info[x][0].n_number; ++j) {// 子句序号
			int c = liter_info[x][0].literal_clause[j];
			if (clause_info[c].length_current == k)
				t += 1 - clause_info[c].is_satisfied;
		}
		return;
	}

	 int GetMinQ() {
		int i, k;
		int max = 0, r, s, t;
		int u;
		for (i = 1; i <= num_liter; ++i) {
			if (fzb[i] == 0) {
				k = get_min_length();//最短子句
				get_weight(i, k, s, t);//i 变元 k  长度
				r = (s + 1) * (t + 1);
				if (r > max) {
					max = r;
					if (s >= t) u = i;
					else u = -(int)i;
				}
			}
		}
		return u;
	}

	int SingleliterExit()  //寻找单子句 如果存在 返回该单子句文字 如果不存在 返回0
	{
		for (int i = 0; i < num_clause; i++)
		{
			if (clause_info[i].is_satisfied == SATISFIED)continue;
			if (clause_info[i].length_current == 1)
			{
				for (int j = 0; j < clause_info[i].length_original; j++)
				{
					if (clause_info[i].literals_is_assigned[j] == UNASSIGNED)
					{
						return clause_info[i].literals[j];
					}
				}
			}
		}
		return 0;
	}

	bool is_sentence_satisfied()//判断是否整个公式都被满足 只要有一个句子没满足就返回UNSATISFIED；
	{
		if (num_clause_current > 0)return 0;
		return 1;
	}



	
};
