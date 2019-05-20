# include "theMap.h"
#include <iostream>

using namespace std;

void theMap::buildTheMap(int n, int m)
{   
	width = m;
	height = n;
	data = new int* [n];
	for (int i = 0; i < n; ++i)
	{
		data[i] = new int[m];
		for(int j=0;j<m;++j)
			data[i][j]=0;
	}

}


theMap::~theMap()
{
	for (int i = 0; i < height; ++i)
		delete  [] data[i];      // [] (data+i);
	delete []data;
}


int theMap::getHeight()
{
	return height;
}


int theMap::getWidth()
{
	return width;
}


void theMap::printTheMap()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
			if (data[i][j] < 0)cout << char(-data[i][j] + 'A' -1) << " ";
			else cout << data[i][j]<<" ";

		cout << endl;
	}
}

void theMap::setHeight(int n)
{
	height = n;
}

void theMap::setWidth(int n)
{
	width = n;
}

void theMap::setThing(int lin, int col,int n)
{
	data[lin][col] = n;
	 
}


int theMap::getValue(int lin, int col)
{
	return data[lin][col];

}