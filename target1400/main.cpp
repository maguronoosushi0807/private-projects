#include<algorithm>
#include<fstream>
#include<iostream>
#include<random>
#include<string>
#include<vector>

#include"target1400.hpp"

using namespace std;


int main() {
	// locale::global(locale("japanese"));
	// input

	cout << "����(��2-1�w�����l��)�̃e�X�g�͈�: 568-647";
	int range_begin = 568, range_end = 647, derivative = false;
	string cmd{};
	cout << "�͈�(�P��ԍ�)" << endl << "begin:";
	//cin >> range_begin;
	range_begin = range_begin < 1 ? 1 : range_begin;
	range_begin = range_begin > 1400 ? 1400 : range_begin;
	cout << "end:";
	//cin >> range_end;
	range_end = range_end < 1 ? 1 : range_end;
	range_end = range_end > 1400 ? 1400 : range_end;
	cout << "�h����(0/1)" << endl << "<";
	cout << endl;
	//cin >> derivative;
	cout << "cmd" << endl << "<";
	cin >> cmd;

	// writing
	if (cmd == "__write") {
		string num_str{};
		cout << "�P��ԍ�:";
		cin >> num_str;
		int num = stoi(num_str);
		string input{};
		while (num <= 1400) {
			// �P��ԍ��̌���
			cout << "�P��ԍ�:" << num << endl;
			cout << "���o����_�p(to+�P��ԍ��ŃX�L�b�v):";
			cin >> input;
			if (input == "exit") break;
			if (input.find("to") != string::npos) {
				num = stoi(input.substr(2, input.size()));
				cout << "�P��ԍ�:" << num << " ���o����_�p:";
				cin >> input;
			}
			Word word{};
			word.num = num;
			word.headword_e = input;
			cout << "���o����_��:";
			while (input[0] != 'e') {
				cin >> input;
				word.headword_j;
			}
			cout << endl;
			word.print();
			cout << endl;
			num++;
		}
	}

	// load
	vector<Word> word_list{};
	loadWords(word_list);

	vector<Problem> problem_list{};
	mt19937 get_rand_mt;
	cout << range_begin << " " << range_end << endl;
	makeProblems(problem_list, word_list, range_begin, range_end);
	shuffle(problem_list.begin(), problem_list.end(), get_rand_mt);
	for (auto& w : problem_list)cout << "j:" << w.problem << " e:" << w.collect << endl;

	// main
	bool training = true;
	int allow_num = 3;
	for (int i = 0; i < problem_list.size(); i++) {
		Problem problem = problem_list[i];
		// ���̑��ݔ���
		if (problem.problem == "\033[31m__loading_err__\033[m" || problem.collect == "\033[31m__loading_err__\033[m") {
			cout << "\033[31m���[�h�Ɏ��s�������̂��܂܂�Ă������ߖ����΂��܂��B\033[m" << endl;
			continue;
		}

		int j = 0;
		bool collected = false;
		string input{};
		while (j < allow_num && !collected) {
			cout << "�P��ԍ�:" << i + 1 << "-" << j + 1 << " \033[7m" << problem.problem << "\033[m\tans:";
			cout << "\033[7m";
			getline(cin, input);
			cout << "\033[m";
			if (input == "exit") return 0;
			else if (input != problem.collect)cout << "\033[31m �s���� \033[m" << endl;
			else {
				cout << "\033[36m����\033[m" << endl;
				collected = true;
			}
			j++;
		}
		if (j == 3)cout << "����:" << problem.collect << endl;

	}

	return 0;
}