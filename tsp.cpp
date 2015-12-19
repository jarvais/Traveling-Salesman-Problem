#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <climits>
#include <fstream>
#include <limits>
#include <cfloat>
using namespace std;

double getDistance(pair<double, double> &a, pair<double, double> &b)
{
	return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

double calculateCost(vector<int> &tour, vector< pair<double, double> > &points)
{
	double totalCost = 0;
	for (int i = 0; i < tour.size()-1; i++)
	{
		totalCost += getDistance(points[tour[i]], points[tour[i+1]]);
	}
	return totalCost;
}

void optSwap(vector<int> &tour,int s,int e)
{
	//cout<<"swapping "<<s<<" to "<<e<<endl;
	int n=tour.size();
	//cout<<endl;
	/*for (int i = 0; i < n; i++)
	{
		cout << tour[i]  << " ";
	}*/
	vector<int> reverser(e-s+1);
	for(int i=s;i<=e;i++)
		reverser[i-s]=tour[i];
	for(int i=s;i<=e;i++)
		tour[i]=reverser[e-i];
	/*for (int i = 0; i < n; i++)
	{
		cout << tour[i]  << " ";
	}*/
	//cout<<"swapped"<<endl;
}

void insert(vector<int> &tour,int a,int b)
{
	int n=tour.size();
	vector<int> modified(n);
	for(int i=0;i<a;i++)
		modified[i]=tour[i];
	modified[a]=tour[b+1];
	for(int i=a;i<=b;i++)
		modified[1+i]=tour[i];
	for(int i=b+2;i<n;i++)
		modified[i]=tour[i];
	tour=modified;
}

int main()
{
	cout.precision(10);
	ifstream fin;
	//cout<<"day 0"<<endl;
	fin.open("tmp.data");
	//Number of points
	int n;
	fin >> n;
	//cout<<"starting"<<endl;
	vector<pair<double, double> > points(n);
	//Taking co-ordinates of the points as input
	for (int i = 0; i<n; i++)
	{
		//cout<<i<<" ";
		fin >> points[i].first >> points[i].second;
	}
	fin.close();
	//cout<<endl<<"input taken"<<endl;
	//creating and initializing tour array
	int t=1;
	double cost=DBL_MAX;
	vector<int> bestTour(n+1);
	srand(time(NULL));
	while(t--)
	{
		//cout<<t<<endl;
		
		vector<int> tour(n+1);
		vector<int> avail(n-1);
		for (int i = 0; i<n-1; i++)
		{
			avail[i] = i+1;
		}
		tour[n] = tour[0]= 0;
		for(int i=0;i<n-1;i++)
		{
			int item=rand()%avail.size();
			int extracted=avail[item];
			tour[i+1]=extracted;
			avail.erase(avail.begin()+item);
		}
		/*for (int i = 0; i < n; i++)
		{
			cout << tour[i]  << " ";
		}*/
		double oldCost = 0;
		double currentCost = 1.0;
		while (oldCost != currentCost)
		{
			oldCost = currentCost=calculateCost(tour, points);
			//cout<<oldCost<<endl;
			bool modified = false;
			for (int i = 1; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					if(getDistance(points[tour[i-1]],points[tour[j]])+getDistance(points[tour[i]],points[tour[j+1]])>=getDistance(points[tour[i-1]],points[tour[i]])+getDistance(points[tour[j]],points[tour[j+1]]))continue;
					optSwap(tour, i,j);
					currentCost = calculateCost(tour, points);
				}
			}
			//cout<<currentCost<<endl;
		}
		if(oldCost==currentCost)
		{
			for(int i=1;i<n;i++)
			{
				for(int j=i+1;j<n-1;j++)
				{
					if(getDistance(points[tour[i-1]],points[tour[j+1]])+getDistance(points[tour[i]],points[tour[j+1]])+ getDistance(points[tour[j]],points[tour[j+2]])>=getDistance(points[tour[i-1]],points[tour[i]])+getDistance(points[tour[j]],points[tour[j+1]]) + getDistance(points[tour[j+2]],points[tour[j+1]]))continue;
					insert(tour,i,j);
					currentCost=calculateCost(tour,points);
				}
			}
		}

		if(cost>currentCost)
		{
			cost=currentCost;
			bestTour=tour;
			//cout<<10000-t<<" "<<cost<<endl;
		}
	}
	//cout << "Tour is: ";
	cout<<cost<<" "<<0<<endl;
	for (int i = 0; i < n; i++)
	{
		cout << bestTour[i]  << " ";
	}
	cout << endl;
	//cout << "With a cost of " << currentCost << endl;
	return 0;

}
