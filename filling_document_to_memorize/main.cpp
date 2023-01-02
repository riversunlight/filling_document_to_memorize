/*
* 文章暗記用プログラム
* 
* - この科目のテスト、教科書の本文の穴埋めしか出てこないなーーー
* - せや、本文めちゃめちゃ暗記したろ
* =====って時にめちゃめちゃ使える!!!!!=====
*/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

// 問題データ
typedef struct _que {
	string doc; // 本文(穴埋め形式)
	vector<string> ans; // 穴埋めの答え
}question;

vector<question> question_data; // 問題データの管理

// ファイルの情報を読み込む
// 開いてから閉じるまで、一度読み込んだら暗記終了まで読み込まない
void read_file() {
	FILE* fp;
	errno_t err;
	char file_name[500];
	char buf[2000];
	int que_num = 0;

	cout << "ファイル名を入力してください" << endl;
	cin >> file_name;

	err = fopen_s(&fp, file_name, "r");
	if (err != 0) {
	    cout << "ファイルオープンエラー" << endl;
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

// 問題を並び替える
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

int main() {
	srand((unsigned int)time(NULL));

	// ファイル読み込み
	read_file();

	// 並び替え
	shuffle_question();

	// 暗記フェーズ

	
	return 0;
}