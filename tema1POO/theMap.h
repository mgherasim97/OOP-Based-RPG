#pragma once
class theMap
{
	int height, width;
	int **data;

    public:
		theMap() {};
		~theMap();

		void buildTheMap(int n, int m);
		void printTheMap();
		int getHeight();
		int getWidth();
		int getValue(int lin,int col); //gets the value from the data[lin][col] 
		
		void setWidth(int n);
		void setHeight(int n);
		void setThing(int lin, int col,int n);
		
};