#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;
string str[50];
int n;
set<char> s[200];
set<char> follow[200];
map<char, string> mp_fei;
map<string, set<char> > select;
string analy[200][200];
int flagflag = 0;
void judge() {
	for (int i = 0; i < n; i++) {//1���������ս����ʾ״̬��Ϊ"δ֪"
		mp_fei[str[i][0]] = "weizhi";
	}
	int flag = 1; int p = 0;
	//2����˳��ɨ�������ʽ�Ҳ�����Ϊ���漸�������
	while (1) { //   e��������a,b,c,d���������˷��ս��״̬�ĸı䣬������(2)������ѭ������������ѭ�����жϽ�����
		if (flag == 0) break;
		p++;
		flag = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 3; j <= str[i].size(); j++) {
				if (str[i][j] == '@') {//a������������"��"������󲿷��ս��״̬��������"��"��������Ϊ"��"������ɨ����һ����ʽ��
					if (mp_fei[str[i][0]] != "null") {
						mp_fei[str[i][0]] = "null";
						flag = 1;
					}
					break;

				}//b���������ս��������󲿷��ս��״̬����Ϊ"δ֪"��������Ϊ"�ǿ�"������ɨ����һ����ʽ��
				else if (str[i][j] == '\0') {//d
					if (mp_fei[str[i][0]] != "null") {
						mp_fei[str[i][0]] = "null";
						flag = 1;
						break;
					}
				}
				else if ((str[i][j] < 'A' || str[i][j]>'Z')) {
					if (mp_fei[str[i][0]] == "weizhi") {
						mp_fei[str[i][0]] = "notnull";
						flag = 1;
					}
					break;
				}//	c�����������ս�������÷��ս��״̬����Ϊ"δ֪"����������ǰ����ʽ��ɨ����һ����ʽ��
				//��Ϊ"�ǿ�"������󲿷��ս��״̬����Ϊ"δ֪"��������Ϊ"�ǿ�"������ɨ����һ����ʽ��
				//��Ϊ"��"������ɨ�豾����ʽ����һ���ţ�
				else if (str[i][j] >= 'A' && str[i][j] <= 'Z') {//c
					if (mp_fei[str[i][j]] == "weizhi") break;
					else if (mp_fei[str[i][j]] == "notnull") {
						if (mp_fei[str[i][0]] == "weizhi") {
							mp_fei[str[i][0]] = "notnull";
							flag = 1;
						}
						break;
					}
					else if (mp_fei[str[i][0]] == "null")	continue;
				}//d��������"\0"������󲿷��ս��״̬��������"��"��������Ϊ"��"������ɨ����һ����ʽ��
			}
		}
	}

}
void first() {
	for (int z = 0; z < n; z++) {
		for (int i = 0; i < n; i++) {
			for (int j = 3; j <= str[i].size(); j++) {
				//A���������ս���������ս�������󲿷��ս����first��������ɨ����һ����ʽ��
				//B������������"��"����"��"�����󲿷��ս����first��������ɨ����һ����ʽ��
				if ((str[i][j] < 'A' || str[i][j]>'Z') && str[i][j] != '\0') {
					//	printf(" i==%d j==%d  \n",i,j);
					s[str[i][0]].insert(str[i][j]);
					break;
				}
				//C�����������ս�������÷��ս����  first��- {��} �����󲿷��ս����first����
				else if (str[i][j] >= 'A' && str[i][j] <= 'Z') {
					//	printf("feifeifei i==%d j==%d  \n",i,j);
					set<char> ::iterator it;
					for (it = s[str[i][j]].begin(); it != s[str[i][j]].end(); it++) {
						if (*it != '@') {
							s[str[i][0]].insert(*it);
						}

					}
					//Ȼ����÷��ս���Ƿ�����Ƴ��գ�������Ϊ�գ���ɨ�豾����ʽ����һ���ţ�����Ϊ�գ������ɨ����һ����ʽ��
					if (mp_fei[str[i][j]] == "null")  continue;
					else break;
				}
				//D��������"\0"����"��"�����󲿷��ս����first��������ɨ����һ����ʽ��
				else if (str[i][j] == '\0') {
					s[str[i][0]].insert('@');
					break;
				}
			}
		}
	}
}

void follow_follow() {
	for (int z = 0; z < n; z++) {
		for (int i = 0; i < n; i++) {
			//��1���ڲ���ʽ�Ҳ��ҵ��÷��ս����ɨ��������ķ��ţ���Ϊ���漸�������
			//��2���ڲ���ʽ���Ҳ��������Ҹ÷��ս�������ҵ���ת��1������
			for (int e = 3; e < str[i].size(); e++) {
				if (str[i][e] >= 'A' && str[i][e] <= 'Z') {
					for (int j = e + 1; j <= str[i].size(); j++) {
						//�����ս�����򽫸��ս������÷��ս����follow����
						if ((str[i][j] < 'A' || str[i][j]>'Z') && str[i][j] != '\0') {
							follow[str[i][e]].insert(str[i][j]);
							break;
						}//���Ƿ��ս�������÷��ս����  first��- {��} ����÷��ս����folow����
						//Ȼ����÷��ս���Ƿ�����Ƴ��գ�������Ϊ�գ���ɨ�豾����ʽ����һ���ţ�
						else if (str[i][j] >= 'A' && str[i][j] <= 'Z') {
							set<char> ::iterator it;
							for (it = s[str[i][j]].begin(); it != s[str[i][j]].end(); it++) {
								if (*it != '@')
									follow[str[i][e]].insert(*it);
							}
							if (mp_fei[str[i][j]] != "null") break;
						}//����"\0"���򽫸ò���ʽ���󲿷��ս����follow����������follow����
						else if (str[i][j] == '\0') {
							set<char> ::iterator it;
							for (it = follow[str[i][0]].begin(); it != follow[str[i][0]].end(); it++) {
								if (*it != '@')
									follow[str[i][e]].insert(*it);
								//	printf("*it===%c\n",*it);
							}
						}
					}
				}
			}
		}
	}

}
void select_select() {
	for (int i = 0; i < n; i++) {
		//ɨ�����ʽ���Ҳ�����Ϊ���漸�������
		for (int j = 3; j <= str[i].size(); j++) {
			//			(1)	�����ս�����򽫸��ս������ò���ʽ��select����

			if ((str[i][j] < 'A' || str[i][j]>'Z') && str[i][j] != '\0' && str[i][j] != '@') {
				select[str[i]].insert(str[i][j]);
				break;
			}//(2)	����"��"�����󲿷��ս����follow������ò���ʽ��select����
			//(4)	����"\0"���򽫸ò���ʽ���󲿷��ս����follow������ò���ʽ��select����
			else if (str[i][j] == '@' || str[i][j] == '\0') {
				set<char> ::iterator it;
				for (it = follow[str[i][0]].begin(); it != follow[str[i][0]].end(); it++) {
					select[str[i]].insert(*it);
				}
			}//(3)	���Ƿ��ս�������÷��ս����  first��- {��} ����ò���ʽ��select����
			//Ȼ����÷��ս���Ƿ�����Ƴ��գ�������Ϊ�գ���ɨ�豾����ʽ����һ���ţ�
			else if (str[i][j] >= 'A' && str[i][j] <= 'Z') {
				set<char> ::iterator it;
				for (it = s[str[i][j]].begin(); it != s[str[i][j]].end(); it++) {
					if (*it != '@')
						select[str[i]].insert(*it);
				}
				if (mp_fei[str[i][j]] != "null") break;
			}
		}
	}
}
void menu() {
	printf("\n\n\n                LL(1)�﷨������ʾ����\n");
	printf("             1.����LL(1)�ķ�\n");
	printf("             2.��ʾ�����LL(1)�ķ�\n");
	printf("             3.�ж��ս���Ƿ�Ϊ��\n");
	printf("             4.������ս����FIRST��\n");
	printf("             5.������ս����FOLLOW��\n");
	printf("             6.������ս����SELECT��\n");
	printf("             7.����������ʾ\n");
	printf("         ����������Ҫ�Ĳ�����");
}
void inputt() {
	system("cls");
	printf("�����ķ�����ʽ�ĸ�����<=50����");
	scanf_s("%d", &n);
	for (int i = 0; i < 50; i++) {
		str[i].clear();
	}
	for (int i = 0; i < n; i++) {
		printf("(%d):", i);
		cin >> str[i];
	}
	select.clear();
	mp_fei.clear();
	for (int i = 0; i < 200; i++) {
		s[i].clear();
		follow[i].clear();
	}
	flagflag = 0;
	judge();
	first();
	follow_follow();
	select_select();
	system("pause");
}
void outputt() {
	system("cls");
	printf("\n\n\n");
	for (int i = 0; i < n; i++)
		cout << "       " << str[i] << endl;
	system("pause");
}
void judge_1() {
	system("cls");
	map<char, string> ::iterator it;
	for (it = mp_fei.begin(); it != mp_fei.end(); it++) {
		cout << it->first << "---------";
		if (it->second == "null") printf("1\n\n");
		else printf("0\n\n");
		//		cout<<it->second<<endl;
		//		it->second<<endl;
	}
	system("pause");

}
void first_1() {
	system("cls");
	set<char> ::iterator it;
	for (int i = 'A'; i <= 'Z'; i++) {
		//		printf("s[i].size=====%d",s[i].size());
		if (!s[i].empty()) {
			printf("     First��%c���� {", i);
			for (it = s[i].begin(); it != s[i].end(); it++) {
				printf(" %c ", *it);
			}
			printf("}\n\n");
		}
	}
	system("pause");
}

void follow_follow_1() {
	system("cls");
	set<char> ::iterator it;
	for (int i = 'A'; i <= 'Z'; i++) {
		int f = 0;
		//		printf("s[i].size=====%d",s[i].size());
		for (int j = 0; j < n; j++) {
			if (i == str[j][0]) f = 1;
		}
		if (!follow[i].empty() || f == 1) {
			follow[i].insert('#');
			printf("     Follow��%c���� {", i);
			for (it = follow[i].begin(); it != follow[i].end(); it++) {
				printf(" %c ", *it);
			}
			printf(" }\n\n");
		}
	}

	system("pause");
}
void select_select_1() {
	system("cls");
	map<string, set<char> > ::iterator it;
	for (it = select.begin(); it != select.end(); it++) {
		cout << "       SELECT(" << it->first << ")= {";
		set<char> ::iterator it1;
		for (it1 = it->second.begin(); it1 != it->second.end(); it1++) {
			printf(" %c ", *it1);
		}
		printf(" }\n\n");
	}
	int flag = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (str[i][0] == str[j][0]) {
				vector<int> ANS;
				set_intersection(select[str[i]].begin(), select[str[i]].end(), select[str[j]].begin(), select[str[j]].end(), inserter(ANS, ANS.begin()));
				if (!ANS.empty()) {
					flag = 1;
				}
			}
		}
	}
	if (flag == 0) printf("��LL(1)�ķ���\n");
	else {
		printf("����LL(1)�ķ���\n");
		flagflag = 1;
	}
	system("pause");
}
void analyse() {
	/*
			����    ����ջ  ʣ�മ  ����ʽ��ƥ��
			1       #E      i+i*i#  E->TR
			2       #RT     i+i*i#  T->FQ
			3       #RQF    i+i*i#  F->i
			4       #RQi    i+i*i#  ƥ��
			5       #RQ     +i*i#   Q->@
			6       #R      +i*i#   R->+TR
			7       #RT+    +i*i#   ƥ��
			8       #RT     i*i#    T->FQ
			9       #RQF    i*i#    F->i
			10      #RQi    i*i#    ƥ��
			11      #RQ     *i#     Q->*FQ
			12      #RQF*   *i#     ƥ��
			13      #RQF    i#      F->i
			14      #RQi    i#      ƥ��
			15      #RQ     #       Q->@
			16      #R      #       R->@
			17      #       #       ����
	*/
	system("cls");
	if (flagflag == 1) {
		printf("\n\n		���ķ�����LL(1)�ķ�!!���ܽ���LL(1)����������");
		system("pause");
		return;
	}
	printf("������Ҫ�����ķ��Ŵ�(��#����):");
	string chuan;
	cin >> chuan;
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			analy[i][j] = "null";
		}
	}
	map<string, set<char> > ::iterator it;
	for (it = select.begin(); it != select.end(); it++) {
		set<char> ::iterator it1;
		string ss = it->first.substr(3, it->first.size());
		for (it1 = it->second.begin(); it1 != it->second.end(); it1++) {
			analy[it->first[0]][*it1] = ss;
			//			cout<<"sit->first[0]==="<<it->first[0]<<"    *it1==="<<*it1<<"      analy==="<<analy[it->first[0]][*it1]<<endl;
		}
	}
	for (it = select.begin(); it != select.end(); it++) {
		if (it->first[3] == '@') {
			analy[it->first[0]]['#'] = "@";
		}
	}
	printf("        ����    ����ջ  ʣ�മ   ����ʽ��ƥ��\n");
	string st = "";
	st = st + "#" + str[0][0];
	int k1 = 1;
	int k2 = 0;
	int k3 = 0;
	string zuizou = "";
	string tuidao[20];
	for (int i = 0; i < 20; i++) {
		tuidao[i] = "";
	}
	int flag_jieshou = 0;
	while (1) {
		k3++;
		tuidao[k3] += zuizou;
		for (int i = st.size() - 1; i > 0; i--) {
			tuidao[k3] += st[i];
		}
		printf("        %-4d    ", k3);
		cout << std::left << setw(8) << st;
		cout << std::left << setw(8) << chuan;
		char c = st[st.size() - 1];
		st = st.substr(0, st.size() - 1);
		if (chuan[k2] == '#' && c == '#') {
			cout << std::left << setw(12) << "����" << endl;
			flag_jieshou = 1;
			break;
		}
		if (c == chuan[0]) {
			cout << std::left << setw(12) << "ƥ��" << endl;
			zuizou += chuan[0];
			chuan = chuan.substr(1, chuan.size());
			continue;
		}
		string ss = analy[c][chuan[0]];
		if (ss == "null") {
			cout << std::left << setw(12) << "��������" << endl;
			system("pause");
			return;
		}

		string s1 = "";
		s1 = s1 + c + "->" + ss;
		cout << std::left << setw(12) << s1 << endl;
		for (int i = ss.size() - 1; i >= 0; i--) {
			st = st + ss[i];
		}

		if (ss == "@") {
			st = st.substr(0, st.size() - 1);
		}
	}
	int zzz = 0;
	if (flag_jieshou) {
		printf("\n�����Ƶ�:\n");
		for (int i = 1; i <= k3; i++) {
			if (tuidao[i] == "" || tuidao[i] == tuidao[i - 1]) continue;
			if (zzz) {
				printf("=>");
			}
			cout << tuidao[i];
			zzz = 1;
		}
		printf("\n\n");
	}
	system("pause");
}

int main() {
	while (1) {
		system("cls");
		menu();
		int x; cin >> x;
		switch (x) {
		case 1:
			inputt();
			break;
		case 2:
			outputt();
			break;
		case 3:
			judge_1();
			break;
		case 4:
			first_1();
			break;
		case 5:
			follow_follow_1();
			break;
		case 6:
			select_select_1();
			break;
		case 7:
			analyse();
			break;
		}
	}

}
/*��������
8
E->TR
R->+TR
R->@
T->FQ
Q->*FQ
Q->@
F->i
F->(E)
i+i*i#
10
S->AB
S->bC
A->@
A->b
B->@
B->aD
C->AD
C->b
D->aS
D->c
*/