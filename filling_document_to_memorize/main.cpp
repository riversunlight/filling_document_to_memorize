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

// �t�@�C���̏���ǂݍ���
// �J���Ă������܂ŁA��x�ǂݍ��񂾂�ËL�I���܂œǂݍ��܂Ȃ�
void read_file() {
	FILE* fp;
	errno_t err;
	char file_name[500];

	cout << "�t�@�C��������͂��Ă�������" << endl;
	cin >> file_name;

	err = fopen_s(&fp, file_name, "r");
	if (err == EOF) {
	    cout << "�t�@�C���I�[�v���G���[" << endl;
		return;
	}


}

int main() {
	// �t�@�C���ǂݍ���
	read_file();

	// ���ёւ�

	// �ËL�t�F�[�Y

	
	return 0;
}