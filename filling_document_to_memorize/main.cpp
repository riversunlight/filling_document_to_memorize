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
using namespace std;

// 問題データ
typedef struct _que {
	string doc; // 本文(穴埋め形式)
	vector<string> ans; // 穴埋めの答え
}question;

// ファイルの情報を読み込む
// 開いてから閉じるまで、一度読み込んだら暗記終了まで読み込まない
void read_file() {
	FILE* fp;
	errno_t err;
	char file_name[500];

	cout << "ファイル名を入力してください" << endl;
	cin >> file_name;

	err = fopen_s(&fp, file_name, "r");
	if (err == EOF) {
	    cout << "ファイルオープンエラー" << endl;
		return;
	}


}

int main() {
	// ファイル読み込み
	read_file();

	// 並び替え

	// 暗記フェーズ

	
	return 0;
}