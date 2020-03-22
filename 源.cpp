#include"Model.h"

using namespace std;

const string code[3] = { "GBK","BIG5","UTF8" };
int main()
{
	/*RecEncode recEncode;
	string code=recEncode.getEncode("C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\UTF8.txt", false);
	cout<<"ʶ��ı���Ϊ��" << code;*/

	ifstream ifs("C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\ans.txt");
	string line;
	getline(ifs, line);

	double score[3] = {0,0,0};

	Model modelGBK;
	modelGBK.generate("C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\GBK.txt","C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\GBKout.txt");
	score[0] = modelGBK.getSentenceScore(line);
	cout << "GBK�÷֣�" << score[0] << endl;

	Model modelBIG5;
	modelBIG5.generate("C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\BIG5.txt", "C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\BIG5out.txt");
	score[1] = modelBIG5.getSentenceScore(line);
	cout << "BIG5�÷֣�" << score[1] << endl;

	Model modelUTF8;
	modelUTF8.generate("C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\UTF8.txt", "C:\\Users\\С��\\Documents\\��Ȼ���Դ���\\UTF8out.txt");
	score[2] = modelUTF8.getSentenceScore(line);
	cout << "UTF8�÷֣�" << score[2] << endl;

	int index = score[0] < score[1] ? 0 : 1;
	index = score[index] < score[2] ? index : 2;
	cout << "���ļ�����Ϊ��" << code[index] << endl;

}