/*
City类，数据成员为名称、人口、海拔高度、天气、年份
*/
#include<string>

using namespace std;

enum weatherType { rainy = 0, snowy = 1, cloudy = 2, sunny = 3 };

class City
{

public:
	string name;//名称
	int population;//人口
	int altitude;//海拔高度
	string weather[12];//天气
	int year;//年份



public:

	City(string input_name, int input_population, int input_altitude, weatherType *input_weather, int input_year);
	City();
	~City();
};

