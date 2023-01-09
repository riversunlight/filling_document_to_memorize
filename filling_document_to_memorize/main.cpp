/*
* ���͈ËL�p�v���O����
* 
* - ���̉Ȗڂ̃e�X�g�A���ȏ��̖{���̌����߂����o�Ă��Ȃ��ȁ[�[�[
* - ����A�{���߂���߂���ËL������
* =====���Ď��ɂ߂���߂���g����!!!!!=====
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <windows.h>
using namespace std;

// ���f�[�^
typedef struct _que {
	string doc; // �{��(�����ߌ`��)
	vector<string> ans; // �����߂̓���
	vector<bool> ac; // �����ς݂��ǂ���
}question;

vector<question> question_data; // ���f�[�^�̊Ǘ�

// �t�@�C���̏���ǂݍ���
// �J���Ă������܂ŁA��x�ǂݍ��񂾂�ËL�I���܂œǂݍ��܂Ȃ�
void read_file() {
	FILE* fp;
	errno_t err;
	char file_name[500];
	char buf[2000];
	int que_num = 0;
	int fil_cnt = 0;

	cout << "�t�@�C��������͂��Ă�������" << endl;
	cin >> file_name;

	err = fopen_s(&fp, file_name, "r");
	if (err != 0) {
	    cout << "�t�@�C���I�[�v���G���[" << endl;
		return;
	}

	while (fgets(buf, 2000, fp) != NULL) {
		string s;
		s = buf;
		if (s == "#E\n") {
			que_num++;
			continue;
		}
		if (s[0] == '#') {
			fil_cnt++;
			s.erase(0, (int)log10(fil_cnt) + 2);
			s.pop_back();
			question_data[que_num].ans.push_back(s);
			question_data[que_num].ac.push_back(false);
		}
		else {
			question que;
			que.doc = s;
			question_data.push_back(que);
			fil_cnt = 0;
		}
	}
	fclose(fp);
	system("cls");
}

// ������ёւ���
void shuffle_question() {
	vector<int> remain;
	vector<question> temp;
	temp = question_data;
	for (int i = 0; i < (int)question_data.size(); i++) {
		remain.emplace_back(i);
	}

	for (int i = 0; i < (int)question_data.size(); i++) {
		int r = rand() % (int)remain.size();

	    question_data[i] = temp[remain[r]];
		remain.erase(remain.begin() + r);

	}
}

// �������������߂�([����])����[����]�֏���������
void fill_ac(question &que) {
	int ps = -1; // �������̎n�܂�̈ʒu
	int hoal_number = 0;
	for (int i = 0; i < (int)que.doc.size(); i++) {
		if (que.doc[i] == '(') {
			ps = i;
		}
		else if (ps != -1) {
			if (que.doc[i] - '0' >= 0 && que.doc[i] - '0' <= 9) {
				hoal_number *= 10;
				hoal_number += que.doc[i] - '0';
			}
			else {
				if (que.doc[i] == ')' && que.ac[hoal_number - 1]) {
					int digits_num = (int)log10(hoal_number) + 1;
					que.doc.erase(ps, digits_num + 2);
					que.doc.insert(ps, que.ans[hoal_number - 1]);
				}
				ps = -1;
				hoal_number = 0;
			}
		}
		
	}
}

// �S�␳��������
bool all_clear(vector<bool> ac) {
	bool res = true;
	for (int i = 0; i < (int)ac.size(); i++)
		if (!ac[i]) res = false;
	return res;
}

// �ËL�̂��߂̏o��
void memorize_doc() {
	for (int i = 0; i < (int)question_data.size(); ) {
		vector<string> user_ans((int)question_data[i].ans.size());
		fill_ac(question_data[i]); // �����ς̌����߂𖄂߂�
		cout << question_data[i].doc << endl;
		for (int j = 0; j < (int)question_data[i].ans.size(); j++) {
			if (question_data[i].ac[j]) continue;
			cout << "#" << j + 1 << ">";
			cin >> user_ans[j];
		}

		cout << endl;

		for (int j = 0; j < (int)question_data[i].ans.size(); j++) {
			if (question_data[i].ac[j]) continue;
			cout << "#" << j + 1;
			if (user_ans[j] == question_data[i].ans[j]) {
				cout << " ����!!" << endl;
				question_data[i].ac[j] = true;
			}
			else {
				cout << "�s����" << " " << question_data[i].ans[j] << endl;
			}
		}

		// �S�␳������������
		if (all_clear(question_data[i].ac)) question_data.erase(question_data.begin() + i);
		else i++;

		system("pause");
		system("cls");
	}
}

int main() {
	srand((unsigned int)time(NULL));

	// �����ɈËL���J��Ԃ�����(�I���������Ƃ��̓R���\�[����ʂ́u�~�v����)
	while (1) {
		// �t�@�C���ǂݍ���
		read_file();

		// �S���͈ËL����܂ŏI����10
		do {
			// ���ёւ�
			shuffle_question();

			// �ËL�t�F�[�Y
			memorize_doc();

			// 1���I���̍��}
			cout << "===1���I��===" << endl;
			system("pause");
			system("cls");
			
		} while ((int)question_data.size() != 0);

		// �S��I����
		cout << "*****�S��C��*******" << endl;
		cout << "���̖��t�@�C����GO!!!" << endl;
		system("pause");
		system("cls");
	}

	return 0;
}