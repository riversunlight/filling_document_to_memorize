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
#include <windows.h>
using namespace std;

// 問題データ
typedef struct _que {
	string doc; // 本文(穴埋め形式)
	vector<string> ans; // 穴埋めの答え
	vector<bool> ac; // 正解済みかどうか
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
	int fil_cnt = 0;

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

// 正解した穴埋めは([数字])から[正答]へ書き換える
void fill_ac(question &que) {
	int ps = -1; // かっこの始まりの位置
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

// 全問正解したか
bool all_clear(vector<bool> ac) {
	bool res = true;
	for (int i = 0; i < (int)ac.size(); i++)
		if (!ac[i]) res = false;
	return res;
}

// 暗記のための出題
void memorize_doc() {
	for (int i = 0; i < (int)question_data.size(); ) {
		vector<string> user_ans((int)question_data[i].ans.size());
		fill_ac(question_data[i]); // 正答済の穴埋めを埋める
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
				cout << " 正解!!" << endl;
				question_data[i].ac[j] = true;
			}
			else {
				cout << "不正解" << " " << question_data[i].ans[j] << endl;
			}
		}

		// 全問正解したか判定
		if (all_clear(question_data[i].ac)) question_data.erase(question_data.begin() + i);
		else i++;

		system("pause");
		system("cls");
	}
}

int main() {
	srand((unsigned int)time(NULL));

	// 無限に暗記を繰り返させる(終了したいときはコンソール画面の「×」から)
	while (1) {
		// ファイル読み込み
		read_file();

		// 全文章暗記するまで終われま10
		do {
			// 並び替え
			shuffle_question();

			// 暗記フェーズ
			memorize_doc();

			// 1周終了の合図
			cout << "===1周終了===" << endl;
			system("pause");
			system("cls");
			
		} while ((int)question_data.size() != 0);

		// 全問終了後
		cout << "*****全問修了*******" << endl;
		cout << "次の問題ファイルへGO!!!" << endl;
		system("pause");
		system("cls");
	}

	return 0;
}