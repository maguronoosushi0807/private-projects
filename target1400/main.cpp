#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

int main() {
	ifstream file("assets/words.txt");
	if (file.fail()) {
		cout << "���\�[�X�t�@�C���̓ǂݍ��݂Ɏ��s����" << endl;
		return -1;
	}

	int range_begin = 0, range_end = 0, derivative = false;
	cout << "�͈�(�P��ԍ�)" << endl << "begin:";
	cin >> range_begin;
	range_begin = range_begin < 1 ? 1 : range_begin;
	range_begin = range_begin > 1400 ? 1400 : range_begin;
	cout << "end:";
	cin >> range_end;
	range_end = range_end < 1 ? 1 : range_end;
	range_end = range_end > 1400 ? 1400 : range_end;
	cout << "�h����(0/1)" << endl << "<";
	cin >> derivative;

	bool training = false;
	training = true;

	string input{};
	string collect = "val";
	while (derivative) {
		cin >> input;
		if (input == collect) {
			training = false;
		}
	}
	return 0;
}