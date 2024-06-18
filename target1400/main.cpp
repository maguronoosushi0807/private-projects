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
			cout << "���o����_�p{(to)(�P��ԍ�|���o����_�p)}\t:";
			//cin >> input; __exit�Ŕ������Ȃ�
			getline(cin, input);
			if (input.empty())getline(cin, input); // ���̍s�������Ƃ����Ɠ����Ȃ�
			if (input == "__exit" || input == "__e") break;
			if (input.find("to") == 0) {
				num = stoi(input.substr(2, input.size()));
				cout << "�P��ԍ�:" << num << " ���o����_�p:";
				// cin >> input;
				getline(cin, input);
				if (input.empty())getline(cin, input);
			}
			Word word{};
			word.num = num;
			word.headword_e = input;
			while (input != "_") {
				cout << "���o����_��{(_)���o����}\t\t:";
				// cin >> input;
				getline(cin, input);
				if (input == "_") break;
				string buf = input;
				word.headword_j.push_back(buf);
			}

			// �h����
			string en{}, jp{};
			while (en != "_") {
				cout << "�h����{(_)en}\t\t\t\t:";
				// cin >> en;
				getline(cin, en);
				if (en == "_") break;
				word.derivative_e.push_back(en);
				cout << "�h����{jp}\t\t\t\t:";
				// cin >> jp;
				getline(cin, jp);
				word.derivative_j.push_back(jp);
			}

			// �ᕶ
			string ans{};
			en = "";
			while (en != "_") {
				cout << "�ᕶ{(_)en}\t\t\t\t:";
				// cin >> en;
				getline(cin, en);
				if (en == "_") break;
				cout << "�ᕶ(ans)\t\t\t\t:";
				//cin >> ans;
				getline(cin, ans);
				cout << "�ᕶ(jp)\t\t\t\t:";
				// cin >> jp;
				getline(cin, jp);
				word.example_e.push_back(en);
				word.example_ans.push_back(ans);
				word.example_j.push_back(jp);
			}

			cout << endl;
			word.print();
			cout << endl << endl;
			string output = to_string(word.num) + " {" + word.headword_e + "=";
			for (auto& s : word.headword_j)output += s + "|";
			output += "}{";
			for (int i = 0; i < word.derivative_e.size(); i++)output += word.derivative_e[i] + "=" + word.derivative_j[i] + "&";
			output += "}{";
			for (int i = 0; i < word.example_e.size(); i++)output += word.example_e[i] + "-" + word.example_ans[i] + "=" + word.example_j[i] + "&";
			output += "}";
			cout << output;
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
			if (input.empty()) getline(cin, input);
			// cout << "line:" << input << ".";
			cout << "\033[m";
			if (input == "__exit" || input == "__e") return 0;
			else if (input != problem.collect)cout << "\033[31m �s���� \033[m" << endl;
			else {
				cout << "\033[36m����\033[m" << endl;
				collected = true;
			}
			j++;
		}
		if (j == 3 && !collected)cout << "����:" << problem.collect << endl;

	}

	return 0;
}