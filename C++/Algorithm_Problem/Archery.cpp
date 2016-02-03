#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Segment {
	long long x1;
	long long y1;
	long long x2;
	long long y2;
};

//global vars

int Radiuses_n = 0, Segments_n = 0;
long long Qs_n = 0;

vector<long long> Radiuses = vector<long long>();
vector<Segment> Segments = vector<Segment>();


int getQsForSegment(Segment s)
{
    if (( s.x2 - s.x1 == 0) && (s.y2 - s.y1 == 0))
        return 0; //segment is a dot

	//first point
    long long dist1 = s.x1 * s.x1 + s.y1 * s.y1;

    //second point
    long long dist2 =  s.x2 * s.x2 + s.y2 * s.y2;

    //make dist2 >= dist1
    if(dist1 > dist2)
    	swap(dist2, dist1);

    vector<long long>::iterator begin_it = lower_bound(Radiuses.begin(), Radiuses.end(), dist1);
    vector<long long>::iterator end_it = upper_bound(Radiuses.begin(), Radiuses.end(), dist2);

    //difference between bounds is how many radiuses will cross segment with Q
    return end_it - begin_it;
}


void readData() {
	cin>>Radiuses_n;

	long long r;
	for(int i=0; i<Radiuses_n; i++) {
		cin>>r;
		Radiuses.push_back(r*r);
	}

	cin>>Segments_n;

	Segment s;
	for(int i=0; i<Segments_n; i++) {
		cin>>s.x1>>s.y1>>s.x2>>s.y2;
		Segments.push_back(s);
	}
}

void printSolution() {
	cout<<Qs_n;
}

void solve() {
	sort(Radiuses.begin(), Radiuses.end());

	Segment s;

	for(int i=0; i<Segments_n; i++) {
		s = Segments[i];
		Qs_n += getQsForSegment(s);
	}
}

int main() {
	readData();
	solve();
	printSolution();
	return 0;
}

