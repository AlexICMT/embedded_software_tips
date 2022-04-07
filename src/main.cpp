/* help_cpp
 * /help_cpp/src/main.cpp
 * main.cpp
 * 
 *  Created on: 29 мар. 2022 г.
 *  	  Time: 08:42:16
 *      Author: AlexICMT
 */

#include <iostream>
#include <vector>
#include <cstdint>
#include <type_traits>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <tuple>
#include <string>
#include <cmath>

#include "median_filter.hpp"


int main()
{
	MedianFilter<int> filter_i(11);
	PeakDetector<int> detector(11);
	int i1[11] = {2048, 2051, 2045, 2067, 2091, 2030, 2020, 2010, 2001, 2022, 2211};
	int out {}, max {};
	for(int i:i1)
	{
		out = filter_i.calculation(i);
		max = detector.calculation(i);
	}
	std::cout << out << std::endl;
	std::cout << max << std::endl;
	return 0;
}

