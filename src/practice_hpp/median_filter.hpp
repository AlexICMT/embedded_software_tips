/* help_cpp
 * /help_cpp/src/practice_hpp/median_filter.hpp
 * median_filter.hpp
 * 
 *  Created on: 7 апр. 2022 г.
 *  	  Time: 08:12:04
 *      Author: AlexICMT
 *
 *      Info: 	This kind of median filters was adopted from
 *      		https://embeddedgurus.com/stack-overflow/2010/10/median-filtering/
 *      		and modified by kga according to C++14
 */

#ifndef PRACTICE_HPP_MEDIAN_FILTER_HPP_
#define PRACTICE_HPP_MEDIAN_FILTER_HPP_

#include <stdio.h>
#include <iostream>

#define USER_NULL 0
#define STOPPER 0
#define MEDIAN_FILTER_SIZE 11

template <typename T>
class MedianFilter
{

public:
	  MedianFilter(int s);
	  //~MedianFilter();
	  T calculation(T);

private:
	struct pair{
	  struct pair *point; /* Pointers forming list linked in sorted order */
	  T value; /* Values to sort */
	};

	  //static int MEDIAN_FILTER_SIZE;
	 /* Buffer of nwidth pairs */
	  //struct pair *buffer;
	  //buffer = new struct pair [asd];
	 /*Size filtr*/
	  int size;
	 /* Buffer of nwidth pairs */
	  //struct pair buffer[MEDIAN_FILTER_SIZE];// = {0};!!!
	  struct pair *buffer;
	 /* Pointer into circular buffer of data */
	  struct pair *datpoint;// = buffer;!!!
	 /* Chain stopper */
	  struct pair small;// = {USER_NULL, STOPPER};!!!
	 /* Pointer to head (largest) of linked list.*/
	  struct pair big;// = {&small, 0};!!!

	 /* Pointer to successor of replaced data item */
	  struct pair *successor;
	 /* Pointer used to scan down the sorted list */
	  struct pair *scan;
	 /* Previous value of scan */
	  struct pair *scanold;
	 /* Pointer to median */
	  struct pair *median;

};

template <typename T>
MedianFilter<T>::MedianFilter(int s)
{
	switch(s)
	{
	   case 3:
	   case 5:
	   case 7:
	   case 9:
	   case 11:
	   case 13:
	   case 15:
		   size = s;
		   std::cout << "size = " << s << std::endl;
	   break;
	   default:
		   size = 5;
		   std::cout << "size = " << s << std::endl;
	   break;
	}
	buffer = new pair[size];
	datpoint = buffer;
	small = {USER_NULL, STOPPER};
	big = {&small, 0};
	big = {&small, 0};
}

template <typename T>
T MedianFilter<T>::calculation(T datum)
{
	int i;
	std::cout << __PRETTY_FUNCTION__ << "\n";

	if (datum == STOPPER){
	   datum = STOPPER + 1; /* No stoppers allowed. */
	}

	 if ( (++datpoint - buffer) >= MEDIAN_FILTER_SIZE){
	   datpoint = buffer; /* Increment and wrap data in pointer.*/
	 }
	 //std::cout << " addr_datpoint = " << datpoint << std::endl;
	 //std::cout << " addr_buffer = " << buffer << std::endl;

	 datpoint->value = datum; /* Copy in new datum */
	 //std::cout << "datpoint->value = " << datpoint->value << std::endl;
	 successor = datpoint->point; /* Save pointer to old value's successor */
	 //std::cout << "datpoint->point = " << datpoint->point << std::endl;
	 //std::cout << "addr_successor = " << successor << std::endl;
	 median = &big; /* Median initially to first in chain */
	 //std::cout << "addr_median = " << median << std::endl;
	 scanold = USER_NULL; /* Scanold initially null. */
	 //std::cout << "addr_scanold = " << scanold << std::endl;
	 scan = &big; /* Points to pointer to first (largest) datum in chain */
	 //std::cout << "addr_scan = " << scan << std::endl;

	 /* Handle chain-out of first item in chain as special case */
	 if (scan->point == datpoint){
	   scan->point = successor;
	   //std::cout << "scan->point = " << scan->point << std::endl;
	 }

	 scanold = scan; /* Save this pointer and */
	 scan = scan->point ; /* step down chain */
	 //std::cout << "scan->point = " << scan->point << std::endl;

	 /* Loop through the chain, normal loop exit via break. */
	 for (i = 0 ; i < MEDIAN_FILTER_SIZE; ++i){
	  /* Handle odd-numbered item in chain */
	  if (scan->point == datpoint){
	    scan->point = successor; /* Chain out the old datum.*/
	  }

	  if (scan->value < datum){ /* If datum is larger than scanned value,*/
	    datpoint->point = scanold->point; /* Chain it in here. */
	    //std::cout << "datpoint->point = " << datpoint->point << std::endl;
	    scanold->point = datpoint; /* Mark it chained in. */
	    //std::cout << "scanold->point = " << scanold->point << std::endl;
	    datum = STOPPER;
	  };

	  /* Step median pointer down chain after doing odd-numbered element */
	  median = median->point; /* Step median pointer. */
	  //std::cout << "median->point = " << median->point << std::endl;
	  if (scan == &small){
	    break; /* Break at end of chain */
	  }
	  scanold = scan; /* Save this pointer and */
	  //std::cout << "scanold->point = " << scanold->point << std::endl;
	  scan = scan->point; /* step down chain */
	  //std::cout << "scan = " << scan << std::endl;

	  /* Handle even-numbered item in chain. */
	  if (scan->point == datpoint){
	    scan->point = successor;
	    //std::cout << "scan->point = " << scan->point << std::endl;
	  }

	  if (scan->value < datum){
	    datpoint->point = scanold->point;
	    //std::cout << "datpoint->point = " << datpoint->point << std::endl;
	    scanold->point = datpoint;
	    //std::cout << "scanold->point = " << scanold->point << std::endl;
	    datum = STOPPER;
	  }

	  if (scan == &small){
	    break;
	  }

	  scanold = scan;
	  //std::cout << "scanold = " << scanold << std::endl;
	  scan = scan->point;
	  //std::cout << "scan = " << scan << std::endl;
	  //std::cout << "median = " << median << std::endl;
	}

	return median->value;
}

#endif /* PRACTICE_HPP_MEDIAN_FILTER_HPP_ */
