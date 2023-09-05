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
	long long BIDX = 0;//��¼���ݲ���
	int num_liter = 0, num_clause = 0;//��¼���������Ӿ���
	int num_clause_current = 0;

	

	

	
	liter_information liter_info[10000][2];// 1Ϊ������ 0Ϊ������ ������Ϣ��
	clause_information clause_info[15000];//  �Ӿ��
	clock_t start_time, end_time;//

	//ջ����
	//�Ӿ�ջ
	pair<int,int> clause_stack[1600000];
	int top_clause_stack = -1;
	//���ָ�ֵջ
	pair<int,int> liter_change_stack[1000000];
	int top_liter_change_stack=-1;
	//����ɾ��ջ
	pair<int,pair<int,int> > liter_delete_stack[1000000];
	int top_liter_delete_stack=-1;

	//�����ִ洢ջ
	int unit_liter[100000];
	int top_unit_liter = -1;


    char filename[200];//�ļ���
	int* fzb = nullptr;   //��ֵ��
	int* ans = nullptr;   //�𰸸�ֵ��
	pair<int, int> getlr(int i, int j)//�������귵�صڼ��еڼ���
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
		//���ļ�
		FILE* fp;

        fp = fopen("./resource/cnfinit.cnf", "r");

		
		if (!fp)
		{
            printf("�����ļ���ȡʧ�ܣ�");
			return;
		}


		//��ȡ�ļ�������ע��
		char str[100];
		fgets(str, 100, fp);
		while (str[0] == 'c')
		{
			fgets(str, 100, fp);
		}

		//��ȡ���ָ������Ӿ����
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


		//��ʼ��liter_info����
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
		
		//��ʼ��clause_info����
		for (int i = 0; i < num_clause+1000; i++)
		{
			clause_info[i].length_original = 0;
			clause_info[i].length_current = 0;
			clause_info[i].is_satisfied = UNSATISFIED;
			clause_info[i].unit_clause_literal = 0;
			clause_info[i].literals = (int*)malloc((2 * num_liter + 1) * sizeof(int));
			clause_info[i].literals_is_assigned = (int*)malloc((2 * num_liter + 1) * sizeof(int));

		}


		//�����Ӿ������Ϊ����

		int curliter;         //��ǰָ�������
		int curclause;

		for (curclause = 0; curclause < num_clause; curclause++)   //���Ӿ�
		{
			//ÿ���Ӿ��ж�����
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
        //���ļ�
        FILE* fp;

        for(int i=0;i<=strlen(inputfilename);i++)filename[i]=inputfilename[i];
        fp = fopen(inputfilename, "r");


        if (!fp)
        {
            printf("�ļ���ȡʧ��1��");
            return;
        }


        //��ȡ�ļ�������ע��
        char str[100];
        fgets(str, 100, fp);
        while (str[0] == 'c')
        {
            fgets(str, 100, fp);
        }

        //��ȡ���ָ������Ӿ����
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


        //��ʼ��liter_info����
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

        //��ʼ��clause_info����
        for (int i = 0; i < num_clause+1000; i++)
        {
            clause_info[i].length_original = 0;
            clause_info[i].length_current = 0;
            clause_info[i].is_satisfied = UNSATISFIED;
            clause_info[i].unit_clause_literal = 0;
            clause_info[i].literals = (int*)malloc((2 * num_liter + 1) * sizeof(int));
            clause_info[i].literals_is_assigned = (int*)malloc((2 * num_liter + 1) * sizeof(int));

        }


        //�����Ӿ������Ϊ����

        int curliter;         //��ǰָ�������
        int curclause;

        for (curclause = 0; curclause < num_clause; curclause++)   //���Ӿ�
        {
            //ÿ���Ӿ��ж�����
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

	void addcnf(int map[9][9])//ͨ����ͼ��ʼ��������cnfԼ��
	{
		for (int i = 0; i <= 4; i++)  //ǰ����
		{
			for (int j = 0; j <= 4 + i; j++)
			{
				if (map[i][j] ==0)continue;

				//���Լ��
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

		for (int i = 5; i <= 8; i++)  //������
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
	

    int solve()//����cnf����
	{

		//��ʼ����ֵ��
		fzb = new int[num_liter + 10];
		ans = new int[num_liter + 10];
		for (int i = 0; i <= num_liter; i++)fzb[i] = 0;

		/*
		Travel(headclause);
		cout << endl;
		*/



		//�ļ��洢����
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
			cout << "�����ļ�ʧ�ܣ�";
            return -2;
		}


		//����DPLL
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

		cout << "�ļ��Ѿ��ɹ��洢��" << filename2 << "��";

		
		fclose(fp2);
        return 1;
	}

	void solve(int zya)
	{
		//�����������������
		fzb = new int[num_liter + 10];
		ans = new int[num_liter + 10];
		for (int i = 0; i <= num_liter; i++)fzb[i] = 0;

		/*
		Travel(headclause);
		cout << endl;
		*/
		int dpll = DPLL(0, 0);
		//if (dpll)cout << "���ѽ����";

		return;
	}

	//������ӡ����
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
		//ɾ�����к���x���Ӿ�  �Լ�ɾ�������Ӿ��еķ�x ��ѹ��ջ�� ���ϱ��curidx
		int type = 0;
		if (x > 0)type = 1;
		liter_information* x_info = &liter_info[abs(x)][type];
		//��ɾ������x�������Ӿ�
		for (int i = 0; i < x_info->n_number; i++)
		{
			clause_information* thisclause = &clause_info[x_info->literal_clause[i]];
			if (thisclause->is_satisfied == SATISFIED)continue;
			thisclause->is_satisfied = SATISFIED;
			num_clause_current--;

			//ɾ�����Ӿ�ѹջ
			clause_stack[++top_clause_stack] = { idx,x_info->literal_clause[i] };
		}
		//��ɾ������-x����������
		liter_information* _x_info = &liter_info[abs(x)][1 - type];
		for (int i = 0; i < _x_info->n_number; i++)
		{
			clause_information* thisclause = &clause_info[_x_info->literal_clause[i]];
			if (thisclause->is_satisfied == SATISFIED)continue;
			thisclause->literals_is_assigned[_x_info->literal_pos_in_clause[i]] = ASSIGNED;
			thisclause->length_current--;

			//ɾ��������ѹջ
			liter_delete_stack[++top_liter_delete_stack] = { idx,{_x_info->literal_clause[i],_x_info->literal_pos_in_clause[i]} };
		}


		x_info->is_assigned = ASSIGNED;
		_x_info->is_assigned = ASSIGNED;
		fzb[abs(x)] = x / abs(x);
		liter_change_stack[++top_liter_change_stack] = { idx,x };
		return;
	}

	bool emptyClauseExists() { //�������޿��Ӿ�
		for (int i = 0; i < num_clause; i++)
		{
			if (clause_info[i].length_current == 0)return true;//������Ӿ䵱ǰ����Ϊ0 ����true
		}
		return false;
	}

	void recover(int idx)
	{
		//�ָ��ı������ֵ
		while (liter_change_stack[top_liter_change_stack].first == idx)
		{
			int changed_x = liter_change_stack[top_liter_change_stack].second;
			liter_info[abs(changed_x)][0].is_assigned = UNASSIGNED;
			liter_info[abs(changed_x)][1].is_assigned = UNASSIGNED;
			fzb[abs(changed_x)] = 0;
			top_liter_change_stack--;
		}

		//�ָ�ɾ�����Ӿ�
		while (clause_stack[top_clause_stack].first == idx)
		{
			int deleted_clause = clause_stack[top_clause_stack].second;
			clause_info[deleted_clause].is_satisfied = UNSATISFIED;
			num_clause_current++;
			top_clause_stack--;
		}

		//�ָ�ɾ���ĵ���
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
		//x����x��ֵΪ1����dpll idxΪ��ǰDPLL���

		//cout << "dpll:" << x << endl;

		//��һ�� ����x��ֵ�����޸�
		if (x!=0)
		{
			deleteSingleliter(x, idx);
			/*
			cout << "����" << x << endl;
			Travel(chead);
			*/
		}

		//Travel();
		//for (int i = 1; i <= num_liter; i++)cout << fzb[i] << " ";
		//cout << endl;

		//�ж� 
		if (is_sentence_satisfied())//�����ʽ������ �����
		{
			for (int i = 1; i <= num_liter; i++)ans[i] = fzb[i];
			return true;//���������ʽ������ ˵��һ���Ӿ䱻���㷵��true
		}
		else if (emptyClauseExists())
		{
			//cout << "YES";
			return false;//�����ʽ�к��пվ��� ˵���о����޷������� ����false;
		}

		//�ڶ��� ���Ӿ䴫��
		int Singleliter = SingleliterExit();
		while (Singleliter)
		{
			deleteSingleliter(Singleliter,idx);

			
			//cout << "ɾ�����־�" << Singleliter<<endl;
			//Travel();
			//for (int i = 1; i <= num_liter; i++)cout << fzb[i] << " ";

			//�ж� 
			if (is_sentence_satisfied())//�����ʽ������ �����
			{
				for (int i = 1; i <= num_liter; i++)ans[i] = fzb[i];
				return true;//���������ʽ������ ˵��һ���Ӿ䱻���㷵��true
			}
			else if (emptyClauseExists())
			{
				//cout << "YES";
				return false;//�����ʽ�к��пվ��� ˵���о����޷������� ����false;
			}

			Singleliter = SingleliterExit();
		}

		//�ڶ��� ���ղ���ѡȡһ�������и�ֵ
		int selectedliter = GetMinQ();

		BIDX++;
		idx = BIDX;
		int dpll1 = DPLL(selectedliter,idx);
		if (dpll1 == 1)return 1;
		else if (dpll1 == -1)return -1;
		recover(idx);
		//���ݳ�ջ
		
		BIDX--;
		/*
		cout << "�ָ�";
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
		cout << "�ָ�";
		Travel(chead);
		*/

		return 0;
	}


	int get_min_length() {//�ҵ�����δ�����Ӿ�������Ӿ�ĳ���
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
			int c = liter_info[x][1].literal_clause[j];//�Ӿ����
			if (clause_info[c].length_current == k)
				s += 1 - clause_info[c].is_satisfied;
		}
		for (int j = 0; j < liter_info[x][0].n_number; ++j) {// �Ӿ����
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
				k = get_min_length();//����Ӿ�
				get_weight(i, k, s, t);//i ��Ԫ k  ����
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

	int SingleliterExit()  //Ѱ�ҵ��Ӿ� ������� ���ظõ��Ӿ����� ��������� ����0
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

	bool is_sentence_satisfied()//�ж��Ƿ�������ʽ�������� ֻҪ��һ������û����ͷ���UNSATISFIED��
	{
		if (num_clause_current > 0)return 0;
		return 1;
	}



	
};
