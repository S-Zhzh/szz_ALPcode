/*
City�࣬���ݳ�ԱΪ���ơ��˿ڡ����θ߶ȡ����������
*/
#include<string>

using namespace std;

enum weatherType { rainy = 0, snowy = 1, cloudy = 2, sunny = 3 };

class City
{

public:
	string name;//����
	int population;//�˿�
	int altitude;//���θ߶�
	string weather[12];//����
	int year;//���



public:

	City(string input_name, int input_population, int input_altitude, weatherType *input_weather, int input_year);
	City();
	~City();
};

