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
using namespace std;

// ���f�[�^
typedef struct _que {
	string doc; // �{��(�����ߌ`��)
	vector<string> ans; // �����߂̓���
}question;

vector<question> question_data; // ���f�[�^�̊Ǘ�

// �t�@�C���̏���ǂݍ���
// �J���Ă������܂ŁA��x�ǂݍ��񂾂�ËL�I���܂œǂݍ��܂Ȃ�
void read_file() {
	FILE* fp;
	errno_t err;
	char file_name[500];
	char buf[1000];
	int que_num = 0;

	cout << "�t�@�C��������͂��Ă�������" << endl;
	cin >> file_name;

	err = fopen_s(&fp, file_name, "r");
	if (err != 0) {
	    cout << "�t�@�C���I�[�v���G���[" << endl;
		return;
	}

	while (fgets(buf, 1000, fp) != NULL) {
		string s;
		s = buf;
		if (s == "#E") {
			que_num++;
			continue;
		}
		if (s[0] == '#') {
			s.erase(0, 2);
			question_data[que_num].ans.push_back(s);
		}
		else {
			question que;
			que.doc = s;
			question_data.push_back(que);
		}
	}
	fclose(fp);
}

int main() {
	// �t�@�C���ǂݍ���
	read_file();

	// ���ёւ�

	// �ËL�t�F�[�Y

	
	return 0;
}