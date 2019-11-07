#include "City.h"
/*city µœ÷¿‡*/
City::City() 
{
}

City::City(string input_name, int input_population, int input_altitude, weatherType *input_weather, int input_year) {
	name = input_name;
	population = input_population;
	altitude = input_altitude;
	weatherType *w = input_weather;
	for (int i = 0; i < 12; i++)
	{
		switch (w[i])
		{
		case 0:weather[i] = "rainy"; break;
		case 1:weather[i] = "snowy"; break;
		case 2:weather[i] = "cloudy"; break;
		case 3:weather[i] = "sunny"; break;
		default:weather[i] = "wrong weather"; break;
		}

	}
	//weather[12] = input_weather[12];
	year = input_year;
};

City::~City()
{
}


