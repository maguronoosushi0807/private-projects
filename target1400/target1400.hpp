#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

struct Word
{
	int num = 0;
	string headword_e{};
	vector<string>headword_j{};

	vector<string>derivative_e{};
	vector<string>derivative_j{};

	vector<string>example_e{};
	vector<string>example_j{};

	Word() {};
	Word(int _num, string _str) {
		num = _num;
		headword_e = _str;
		headword_j.push_back(_str);
		derivative_e.push_back(_str);
		derivative_j.push_back(_str);
		example_e.push_back(_str);
		example_j.push_back(_str);
	};
	void print() {
		cout << "単語番号:" << num << endl;

		cout << "見出し語 e:" << headword_e;
		cout << " j:";
		for (auto& s : headword_j)cout << s << " ";
		cout << endl;

		cout << "派生語:" << endl;
		for (int i = 0; i < derivative_e.size(); i++) {
			cout << "e:" << derivative_e[i] << " j:" << derivative_j[i] << endl;
		}

		cout << "例文:" << endl;
		for (auto& s : example_e)cout << s << endl;
		for (auto& s : example_j)cout << s << endl;
	};
};

struct Problem {
	string problem{};
	string collect{};
};

int loadWords(vector<Word>& word_list) {

	ifstream word_file(L"assets/words.txt");
	if (word_file.fail()) {
		cout << "リソースファイルの読み込みに失敗した" << endl;
		return -1;
	}

	string line{};
	int i = 1;
	while (getline(word_file, line)) {
		if (line.find("{") == string::npos) {
			Word word{ i,"\033[31m__loading_err__\033[m" };
			word_list.push_back(word);
			//word.print();
			i++;
			continue;
		}
		// 単語番号
		cout << "word_num:" << i << " line:" << line << endl;
		Word word{};
		auto index = line.find("{");
		word.num = stoi(line.substr(0, index));
		index++;
		line.erase(line.begin(), line.begin() + index);

		// 見出し語 英
		index = line.find("=");
		word.headword_e = line.substr(0, index);
		line.erase(line.begin(), line.begin() + index + 1);

		// 見出し語 日
		while (line.find("|") < line.find("}")) {
			index = line.find("|");
			//if (index == string::npos) index = line.find("}");
			word.headword_j.push_back(line.substr(0, index));
			line.erase(line.begin(), line.begin() + index + 1);
		}

		// 派生語
		line.erase(0, line.find("{") + 1);
		while (line.find("&") < line.find("}")) {
			index = line.find("=");
			word.derivative_e.push_back(line.substr(0, index));
			line.erase(0, index + 1);
			index = line.find("&");
			word.derivative_j.push_back(line.substr(0, index));
			line.erase(0, index + 1);
		}

		// 例文
		line.erase(0, line.find("{") + 1);
		while (line.find("&") < line.find("}")) {
			index = line.find("=");
			word.example_e.push_back(line.substr(0, index));
			line.erase(0, index + 1);
			index = line.find("&");
			word.example_j.push_back(line.substr(0, index));
			line.erase(0, index + 1);
		}

		word.print();
		word_list.push_back(word);
		i++;
	}
	cout << "loaded!" << endl << endl;

	return 0;
};

void makeProblems(vector<Problem>& problem_list, vector<Word>& word_list, int begin, int end) {
	cout << word_list.size() << endl;
	for (int i = begin - 1; i < end; i++) {
		Problem problem{};
		// 見出し語
		for (auto& s : word_list[i].headword_j) {
			problem.problem = s;
			problem.collect = word_list[i].headword_e;
			problem_list.push_back(problem);
		}

		// 派生語
		for (int j = 0; j < word_list[i].derivative_e.size(); j++) {
			problem.problem = word_list[i].derivative_j[j];
			problem.collect = word_list[i].derivative_e[j];
			problem_list.push_back(problem);
		}
		// 例文
		for (int j = 0; j < word_list[i].example_j.size(); j++) {
			problem.problem = word_list[i].example_j[j];
			problem.collect = word_list[i].example_e[j];
			problem_list.push_back(problem);
		}
		cout << "word num:" << i + 1 << " added";
	}

	return;
};