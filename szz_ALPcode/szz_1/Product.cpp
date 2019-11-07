
#include<vector>
#include<string>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include <random>

#include "City.h"
#define CITY_NUM 1000 //City对象数量大于1000个


using namespace std;

//年份为2009年
int year = 2009;

/*第一题，产生City对象的类
将产生的City对象（数量大于1000个）填充至一个容器，容器的类型自选。
对于City对象的具体属性值通过创建发生器来生成。
*/
//名称由4-8个英文小写字符随机构成
string rand_name()
{
	string name;
	int i, n;
	n = rand() % 5;
	for (i = 0; i < n + 4; ++i)
	{
		char c = 'a' + rand() % 26;
		name = name + c;
	}
	return name;
}

//人口在范围[300000,10000000)内随机选取
int rand_population()
{
	int population;
	population = rand() % (10000000 - 300000 + 1);
	return population;
}

//海拔高度在范围[0,5000)米内随机选取
int rand_altitude()
{
	int altitude;
	altitude = rand() % (5000 - 0 + 1) + 0;
	return altitude;
}

//名称、人口、海拔均不可重复，判断去重
template <typename T> bool checkRepeat(vector<T> dataSet, T value) {
	typename vector<T>::iterator position = find(dataSet.begin(), dataSet.end(), value);
	if (position >= dataSet.end())
		return false;
	else
		return true;
};

//天气在枚举常量表中{ Rainy,Snowy,Cloudy,Sunny }随机选取（1年天气取12个值，即每月一个值）
weatherType * rand_weather()
{
	weatherType *weather;
	static weatherType w[12];
	int i = 0;
	for (; i < 12; i++)
	{
		int n = rand() % 4;
		weatherType wea = (enum weatherType)(n);
		w[i] = wea;
	}
	weather = w;
	return weather;
}



/*第二题，根据2006年的人口数生成2006-2015年的人口数据
*/


//利用rand生成随机浮点数
double rand_n(int min, int max)
{
	double m1 = (double)(rand() % 101) / 101; // 计算 0，1之间的随机小数,得到的值域近似为(0,1)
	min++;//将 区间变为(min+1,max),
	double m2 = (double)((rand() % (max - min + 1)) + min);//计算 min+1,max 之间的随机整数，得到的值域为[min+1,max]
	m2 = m2 - 1;//令值域为[min,max-1]
	return m1 + m2;//返回值域为(min,max),为所求随机浮点数
}

//从2009年至2019年间，各城市人口按照n%的速度进行变化,n的值在-10到+10间随机选取
 City op_city(City c)
 {
	double n = rand_n(-10, 10);
	c.year++;
	City new_c(c.name, floor(c.population*(1 + n / 100)), c.altitude, rand_weather(), c.year);
	return new_c;
}




/*第三题，找出这10年里人口最多、最少和人口处于中位数的各个城市

*/

//采用operator<从小到大排序
 bool operator<(const City& c1, const City& c2)
 {
	 return  c1.population < c2.population; 
 }

 /*第六题
 海拔排序,升序
 */
 template<class City> struct sortAsc
 {
	 bool operator()(const City& c1, const City& c2) const
	 {
		 return (c1.altitude < c2.altitude);
	 }
 };


int product()
{
	/*---------------------------------------第1题-------------------------------------*/
	cout << "1、产生City对象开始------------" << endl;
	srand((unsigned)time(NULL));//使用随机数发生器
	vector<City> ve;
	vector<string>nameVe(CITY_NUM);//用于名称去重
	vector<int>altitudeVe(CITY_NUM);//用于海拔去重
	vector<int>populationVe(CITY_NUM);//用于人口去重

	



	for (int i = 0; i < CITY_NUM; i++)  //将随机获取每个城市的数据写入vector中
	{
		//名称
		string input_name = rand_name();
		while (checkRepeat(nameVe, input_name)) {
			input_name = rand_name();
		}
		nameVe.push_back(input_name);

		//人口
		int input_population = rand_population();
		while (checkRepeat(populationVe, input_population)) {
			input_population = rand_population();
		}
		populationVe.push_back(input_population);

		//海拔
		int input_altitude = rand_altitude();
		while (checkRepeat(populationVe, input_altitude)) {
			input_altitude = rand_altitude();
		}
		altitudeVe.push_back(input_altitude);

		weatherType *input_weather;
		input_weather = rand_weather();
		int input_year = year;
		City c(input_name, input_population, input_altitude, input_weather, input_year);
		ve.push_back(c);

	}

	//容器填充完毕后，将其内容写入一个名为City.txt的文件

	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "./file/City.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp, "年份   城市名称   城市人口   海拔高度   1月天气   2月天气    3月天气    4月天气    5月天气    6月天气    7月天气    8月天气    9月天气    10月天气   11月天气   12月天气\n");

	for (int i = 0; i < CITY_NUM; i++)
	{
		fprintf(fp, "%d%10s%10d%10d", ve[i].year, ve[i].name.c_str(), ve[i].population, ve[i].altitude);
		for (int j = 0; j < 12; j++)
		{
			fprintf(fp, "%11s", ve[i].weather[j].c_str());
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	cout << "City.txt文件写入完毕------------" << endl;
	system("pause");

	/*-----------------------------------第2题--------------------------------------------------*/

	//用transform算法完成人口计算
	cout << "2、从2009年至2019年人口统计开始--------------" << endl;
	vector< vector<City> > v(11, vector<City>( CITY_NUM));//2009年至2019年共11年
	v[0] = ve;
	
	for (int i = 0; i < 10; i++)
	{
		transform(v[i].begin(), v[i].end(), v[i + 1].begin(), op_city);
		//transform(v[i].begin(), v[i].end(), v[i + 1].begin(), [](City c) { double n = rand_n(-10, 10);  c.population = floor(c.population*(1 + n / 100));  c.year++;
		//return c; });
	}
	
	//写入文件
	FILE *fp2;
	errno_t err2;
	err2 = fopen_s(&fp2, "./file/City2009_2019.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp2, "年份   城市名称   城市人口   海拔高度   1月天气   2月天气    3月天气    4月天气    5月天气    6月天气    7月天气    8月天气    9月天气    10月天气   11月天气   12月天气\n");
	for (int k = 0; k < 11; k++)//11年
	{
		for (int i = 0; i < CITY_NUM; i++)//CITY_NUM个城市
		{
			fprintf(fp2, "%d%10s%10d%10d", v[k][i].year, v[k][i].name.c_str(), v[k][i].population, v[k][i].altitude);
			for (int j = 0; j < 12; j++)//12个月
			{
				fprintf(fp2, "%11s", v[k][i].weather[j].c_str());
			}
			fprintf(fp2, "\n");
		}

	}
	fclose(fp2);
	cout << "从2009年至2019年City数据写入City2009_2019.txt完毕--------------" << endl;
	system("pause");

	/*-----------------------------------第3题-------------------------------------------*/
	//找出这10年里人口最多、最少和人口处于中位数的各个城市并写入文件
	cout << "3、从2009年至2019年找出人口最多、最少和人口处于中位数的各个城市开始--------------" << endl;
	FILE *fp3;
	errno_t err3;
	err3 = fopen_s(&fp3, "./file/Population.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp3, "年份   最多人口城市名称   最少人口城市名称   中位数人口城市名称\n");
	for (int k = 0; k < 11; k++)//11年
	{
		sort(v[k].begin(), v[k].end());
		fprintf(fp3, "%d%16s%16s%16s", v[k][0].year, v[k][CITY_NUM - 1].name.c_str(), v[k][0].name.c_str(), v[k][CITY_NUM/2].name.c_str());
		fprintf(fp3, "\n");
	}
	fclose(fp3);
	cout << "Population.txt文件写入完毕------------" << endl;
	system("pause");

	/*-----------------------------------第4题----------------------------------------------*/
	//查找2009年到2019年的10年间，每年拥有最好天气数量的城市（即Sunny最多），结果写入文件Weather.txt
	cout << "4、从2009年至2019年找出每年拥有最好天气数量的城市（即Sunny最多）开始--------------" << endl;
	FILE *fp4;
	errno_t err4;
	err4 = fopen_s(&fp4, "./file/Weather.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp4, "年份   城市名称  Sunny数量\n");
	for (int k = 0; k < 11; k++)
	{
		string sunny_city;//该年天气最好的城市名
		int max_sum_summy = 0;
		for (int i = 0; i < CITY_NUM; i++)//CITY_NUM个城市,比较sunny数量
		{
			int sum_sunny = 0 ;
			for (int j = 0; j < 12; j++)//12个月，统计sunny数量
			{
				if (v[k][i].weather[j] == "sunny") sum_sunny++;
			}
			if (sum_sunny > max_sum_summy)
			{
				max_sum_summy = sum_sunny;
				sunny_city = v[k][i].name;
			}
		}

		fprintf(fp4, "%d%10s%10d", v[k][0].year, sunny_city.c_str(), max_sum_summy);
		fprintf(fp4, "\n");

	}

	fclose(fp4);
	cout << "Weather.txt文件写入完毕------------" << endl;
	system("pause");

	/*------------------------------第5题-------------------------------------------------*/
	//找出所有海拔在1000-3500米的城市写入文件altitude.txt
	cout << "5、找出所有海拔在1000-3500米的城市开始--------------" << endl;
	FILE *fp5;
	errno_t err5;
	err5 = fopen_s(&fp5, "./file/altitude.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp5, "城市名称  海拔\n");

	for (int i = 0; i < CITY_NUM; i++)//CITY_NUM个城市,比较海拔
	{
		if (v[0][i].altitude >= 1000 && v[0][i].altitude <= 3500)
		{
			fprintf(fp5, "%10s%10d", v[0][i].name.c_str(), v[0][i].altitude);
			fprintf(fp5, "\n");
		}
		
	}
	fclose(fp5);
	cout << "altitude.txt文件写入完毕------------" << endl;
	system("pause");

	/*------------------------------第6题-------------------------------------------------*/
	//使用<functional>中的函数对象，至少使用两种不同的方式按照海拔对城市进行排序（升序和降序各一次，并展示结果）
	cout << "6、按照海拔对城市进行排序开始--------------" << endl;
	cout << "按照海拔对城市进行排序,升序" << endl;
	cout << "城市名称  海拔高度" << endl;
	FILE *fp6;
	errno_t err6;
	err5 = fopen_s(&fp6, "./file/altitudeSort.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp6, "升序排序\n");
	fprintf(fp6, "城市名称  海拔\n");
	stable_sort(ve.begin(), ve.end(), sortAsc<City>());
	for (int i = 0; i < CITY_NUM; i++)
	{
		cout.width(8);
		cout << ve[i].name;
		cout.width(8);
		cout<< ve[i].altitude << endl;
		fprintf(fp6, "%10s%10d", ve[i].name.c_str(), ve[i].altitude);
		fprintf(fp6, "\n");

	}
	cout << "按照海拔对城市进行排序,降序" << endl;
	cout << "城市名称  海拔高度" << endl;
	fprintf(fp6, "升序排序\n");
	fprintf(fp6, "城市名称  海拔\n");
	//冒泡法排序
	City temp;
	for (int i = 0; i < CITY_NUM - 1; i++) {
		for (int j = 0; j < CITY_NUM - 1 - i; j++)
		{
			if (ve[j].altitude < ve[j+1].altitude)
			{ 
				temp = ve[j];
				ve[j] = ve[j + 1];
				ve[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < CITY_NUM; i++)
	{
		cout.width(8);
		cout << ve[i].name;
		cout.width(8);
		cout << ve[i].altitude << endl;
		fprintf(fp6, "%10s%10d", ve[i].name.c_str(), ve[i].altitude);
		fprintf(fp6, "\n");
	}
	fclose(fp6);
	cout << "按照海拔对城市进行排序并写入altitudeSort.txt结束--------------" << endl;

	system("pause");

	/*------------------------------第7题-------------------------------------------------*/
	/*规则
	1、好天气（Sunny数量）排前100（2009-2019年间好天气的平均值）；
	2、海拔高度在0-2500米；
	3、选中城市中不能有两个城市的海拔高度相差100米，有则选取海拔较低的城市。
	4、人口数量排前100 （2009-2019年间人口数的平均值）
	*/
	cout << "7、选取建立机场城市开始--------------" << endl;
	int top = 100;//排前100
	int weather_ave[CITY_NUM] = { 0 };//记录天气数量
	int population_ave[CITY_NUM] = { 0 };//记录人口数量

	//统计各城市好天气及人口
	for (int i = 0; i < CITY_NUM; i++) {//城市
		for (int j = 0; j < 11; j++) {//年份
			for (int k = 0; k < 12; k++) {
				if (v[j][i].weather[k] == "sunny") {
					weather_ave[i] = weather_ave[i] + 1;
				}
			}
			population_ave[i] = population_ave[i] + v[j][i].population;
		}
		weather_ave[i] = weather_ave[i] / 11;//求均值
		population_ave[i] = population_ave[i] / 11;;//求均值

	}

	int sequence_w[CITY_NUM] = { 0 };//按照天气数量排序时记录顺序
	int sequence_p[CITY_NUM] = { 0 };//按照人口数量排序时记录顺序
	//初始化
	for (int i = 0; i < CITY_NUM; i++)
	{
		sequence_w[i] = i;
		sequence_p[i] = i;
	}

	//规则1，好天气排前100的城市
	for (int i = 0; i < top; i++) {//按好天气从大到小对城市排序，冒泡法排到前100即可
		int temp1,temp2;
		for (int j = 0; j < CITY_NUM - i - 1; j++) {
			if (weather_ave[i] > weather_ave[i + 1]) {
				temp1 = weather_ave[j];
				weather_ave[j] = weather_ave[j + 1];
				weather_ave[j + 1] = temp1;
				//交换序列号
				temp2 = sequence_w[j];
				sequence_w[j] = sequence_w[j + 1];
				sequence_w[j + 1] = temp2;
			}
		}
	}

	//规则4，人口数量排前100的城市
	for (int i = 0; i < top; i++) {//按人口数量从大到小对城市排序，冒泡法排到前100即可
		int temp1, temp2;
		for (int j = 0; j < CITY_NUM - i - 1; j++) {
			if (weather_ave[i] > weather_ave[i + 1]) {
				temp1 = population_ave[j];
				population_ave[j] = population_ave[j + 1];
				population_ave[j + 1] = temp1;
				//交换序列号
				temp2 = sequence_p[j];
				sequence_p[j] = sequence_p[j + 1];
				sequence_p[j + 1] = temp2;
			}
		}
	}

	//筛选出同时满足规则1（天气）和规则4（人口）的城市
	vector<City> airport_preparation;

	for (int i = 0; i < top; i++)
	{
		for (int j = 0; j < top; j++)
		{
			if (sequence_w[i] == sequence_p[j])
			{
				airport_preparation.push_back(v[0][sequence_w[i]]);
				break;
			}
		}
	}

	//规则2，海拔高度在0-2500米

	int size = airport_preparation.size();
	for (int i = 0; i < size; i++)
	{
		if (airport_preparation[i].altitude >= 2500)
		{
			airport_preparation[i].name = "0";//不满足规则2，name变为“0”，标记不选取的城市
		}
		
	}

	//规则3，选中城市中不能有两个城市的海拔高度相差100米，有则选取海拔较低的城市。
	
	for (int i = 0; i < size; i++)
	{
		if (airport_preparation[i].name != "0") 
			for (int j = 0; j < size; j++)
			{
				if (airport_preparation[j].name != "0") 
				{
					int d = abs(airport_preparation[i].altitude - airport_preparation[j].altitude);
					if (d <= 100) {
						if (airport_preparation[i].altitude > airport_preparation[j].altitude)
						{
							airport_preparation[i].name = "0";//按规则3筛选，name变为“0”，标记不选取的城市
						}
					}
				}
				
			}
		
	}

	FILE *fp7;
	errno_t err7;
	err7 = fopen_s(&fp7, "./file/Airport.txt", "w");//打开一个空文件以进行写入。如果该文件存在，其内容将被销毁。
	fprintf(fp7, "建立机场选取城市名称\n");
	for (int i = 0; i < size; i++) {
		if (airport_preparation[i].name != "0")
		{
			fprintf(fp7,airport_preparation[i].name.c_str());
			fprintf(fp7, "\n");
		}
		
	}
	

	fclose(fp7);
	cout << "Airport.txt文件写入完毕------------" << endl;
	system("pause");

	return 0;


}


int main() {
	product();
	return 0;
}