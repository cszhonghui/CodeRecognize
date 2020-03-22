#pragma once
#define COUNT_LENGTH 2
#include<iostream>
#include<sstream>
#include<io.h>
#include<string>
#include<codecvt>
#include<fstream>
#include<map>
#include<utility>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<set>
using namespace std;
class Model {
private:
	map<string, long long> cnt[COUNT_LENGTH];//统计每个key出现的次数
	long long different_cnt[COUNT_LENGTH];//统计每个长度的序列共有多少个不同的值
	map<string, double> score;
public:
	Model() {
		for (int i = 0; i < COUNT_LENGTH; i++)different_cnt[i] = 0;
	}

	/*
	生成模型
	*/
	bool generate(string data_path , string out_path) {
		string line;
		ifstream ifs(data_path);
		while (!ifs.eof()) {
			getline(ifs, line);
			int len = line.length();
			for (int i = 0; i < len; ++i)
				for (int j = 0; j < COUNT_LENGTH; j++) {
					if (i + j >= len)break;
					string tmp = line.substr(i, j + 1);
					if (!cnt[j].count(tmp)) {
						cnt[j][tmp] = 0;
						different_cnt[j]++;
					}
					cnt[j][tmp]++;
				}
		}
		FILE* fp;
		fopen_s(&fp, out_path.c_str(),"w");
		for (int i = 0; i < COUNT_LENGTH; i++) fprintf(fp, "%lld\n", different_cnt[i]);
		for (int i = 1; i < COUNT_LENGTH; i++)
			for (auto it = cnt[i].begin(); it != cnt[i].end(); it++) {
				double p = abs(log((it->second * 1.0 + 1) / (cnt[i - 1][(it->first).substr(0, i)] + different_cnt[i - 1])));
				fprintf(fp, "%s %lf\n", it->first, score[it->first] = p);
			}
		fclose(fp);
		return true;
	}

	/*
	获取p(wi|wi-1)或p(wi|wi-2wi-1)
	*/
	double getScore(string s) {
		if (s.length() > COUNT_LENGTH)
			s = s.substr(s.length() - COUNT_LENGTH);
		double sc;
		if (score.count(s))sc = score[s];//平滑方法
		else if(s.length()==1)
			sc= abs(log(1.0 / different_cnt[s.length() - 1]));
		else
			sc = abs(log(1.0 / different_cnt[s.length() - 2]));
		return sc;
	}

	/*
	获取p(s)
	*/
	double getSentenceScore(string s) {
		int len = s.length();
		double score = 0;
		for (int i = 1; i < len; i++) {
			string tmp = s.substr(0, i);
			score += getScore(tmp);
		}
		for (int i = min(len, COUNT_LENGTH); i > 1; i--) {
			string tmp = s.substr(len - i, i);
			score += getScore(tmp);
		}
		return score;
	}
};