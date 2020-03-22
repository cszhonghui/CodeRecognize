#include"Model.h"

using namespace std;

const string code[3] = { "GBK","BIG5","UTF8" };
int main()
{
	/*RecEncode recEncode;
	string code=recEncode.getEncode("C:\\Users\\小新\\Documents\\自然语言处理\\UTF8.txt", false);
	cout<<"识别的编码为：" << code;*/

	ifstream ifs("C:\\Users\\小新\\Documents\\自然语言处理\\ans.txt");
	string line;
	getline(ifs, line);

	double score[3] = {0,0,0};

	Model modelGBK;
	modelGBK.generate("C:\\Users\\小新\\Documents\\自然语言处理\\GBK.txt","C:\\Users\\小新\\Documents\\自然语言处理\\GBKout.txt");
	score[0] = modelGBK.getSentenceScore(line);
	cout << "GBK得分：" << score[0] << endl;

	Model modelBIG5;
	modelBIG5.generate("C:\\Users\\小新\\Documents\\自然语言处理\\BIG5.txt", "C:\\Users\\小新\\Documents\\自然语言处理\\BIG5out.txt");
	score[1] = modelBIG5.getSentenceScore(line);
	cout << "BIG5得分：" << score[1] << endl;

	Model modelUTF8;
	modelUTF8.generate("C:\\Users\\小新\\Documents\\自然语言处理\\UTF8.txt", "C:\\Users\\小新\\Documents\\自然语言处理\\UTF8out.txt");
	score[2] = modelUTF8.getSentenceScore(line);
	cout << "UTF8得分：" << score[2] << endl;

	int index = score[0] < score[1] ? 0 : 1;
	index = score[index] < score[2] ? index : 2;
	cout << "该文件编码为：" << code[index] << endl;

}