#include <cstdlib>
#include <vector>
#include <climits>
#include <string>
#include <ctime>
#include <fstream>
#include <ostream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <map>
#include <algorithm>

/*
 * Things to consider
 *    1.  Command line options
 *    2.  Nearest int? Save (x,y) as doubles and round distance?
 *
 */

void readFile(char *, std::vector<std::pair<int,int> > *);
void write_file(std::ofstream *, std::vector<int>*, int);

int getDistance(std::pair<int,int>, std::pair<int,int>);
int getMinDist(std::vector<std::pair<int,int> > *, int *, int *, int);
std::vector<int> mst(std::vector<std::pair<int,int> > *, int *);

bool myfunction (int i,int j) { return (i<j); }


int main(int argc, char* argv[])
{
    std::ofstream outfile;
    std::vector<std::pair<int,int> > cityPair;

	char output[80];

	strcpy(output, argv[1]);
	strcat(output, ".tour");
	outfile.open(output);

	std::cout.precision(6);

    readFile(argv[1], &cityPair);
    int totalDist = 0;
    std::vector<int> mstTour = mst(&cityPair, &totalDist);

    std::cout << "Total Dist Travel: " << totalDist << std::endl;
    std::cout << "City Tour: " << std::endl;
    for(unsigned int i = 0; i < mstTour.size()-1; i++){
        std::cout << "City[" << mstTour.at(i) << "] to City[" << mstTour.at(i+1) << "]" << std::endl;
    }
    write_file(&outfile, &mstTour, totalDist);

    outfile.close();
	return 0;
}


void readFile(char *fileName, std::vector<std::pair<int,int> > *cityPair){
    std::ifstream file(fileName);
    std::string line;
    std::pair<int,int> tempPair;
    int city=0,x=0,y=0;

    while(std::getline(file, line))
    {
        std::vector<int> lineData;
        std::stringstream lineStream(line);

        while(lineStream >> city >> x >> y)
        {
            tempPair = std::make_pair(x,y);
            cityPair->push_back(tempPair);
        }
    }
    file.close();
    return;
}

int getDistance(std::pair<int,int> c1, std::pair<int,int> c2){
    return sqrt( pow(c1.first - c2.first,2) + pow(c1.second - c2.second,2) );
}

int getMinDist(std::vector<std::pair<int,int> > *cityPair, int *startIdx, int *endCity, int nextMin){
    std::vector<int> mins;
    std::map<int,int> cityMap;
    //std::cout << "Looking for "<< nextMin <<" Min Dist from city " << *startIdx << std::endl;

    for(int i = 0; i < (int)cityPair->size(); i++){
        if(*startIdx != i){
            // Push all distances from city1 to all cities
            int d = getDistance(cityPair->at(*startIdx), cityPair->at(i));
            mins.push_back(d); // Vector of dist
            cityMap[d] = i; // Map[dist, city]
        }
    }
    // Sort vector of distances to find minimums
    std::sort(mins.begin(), mins.end(), myfunction);

/*    std::cout << "Distances in order: " << std::endl;
    for(int i = 0; i < mins.size(); i++){
        std::cout << mins.at(i) << std::endl;
    }
*/
    //std::cout << "City Idx @ dist: " << mins.at(nextMin) << " is City: " << cityMap[mins.at(nextMin)] << std::endl;
    *endCity = cityMap[mins.at(nextMin)];

    /*std::cout << "Min Distance of City[" << *startIdx
                << "] is to \tCity[" << *endCity << "] with length:\t" << mins.at(nextMin) << std::endl;
    */
    return mins.at(nextMin);
}

std::vector<int> mst(std::vector<std::pair<int,int> > *cityPair, int *tDist){
    std::vector<int> mSet;
    mSet.push_back(0);
    int c1=0, c2=0, nextMin=0;
    bool vertexFound = true;

    while(mSet.size() != cityPair->size()){
        //std::cout << "Getting next Vertex" << std::endl;
        int tempDist = getMinDist(cityPair, &c1, &c2, nextMin);

        for(unsigned int i = 0; i < mSet.size(); i++){
            if(c2 == mSet.at(i)){
                std::cout << "Vertex " << c2 << " already in MAP!!! - Find Min " << nextMin << std::endl;
                if(nextMin == (int)cityPair->size()-2){
                    break;
                }
                nextMin++;
                vertexFound = false;
            }
        }
        if(vertexFound){
            std::cout << "New Vertex: " << c2 << std::endl;
            mSet.push_back(c2);
            //totalDist += tempDist;
            *tDist += tempDist;
            nextMin = 0;
            c1 = c2;
            c2 = 0;
        }
        vertexFound = true;
    }
    /*
    std::cout << "City Tour: " << std::endl;
    for(unsigned int i = 0; i < mSet.size()-1; i++){
        std::cout << "City[" << mSet.at(i) << "] to City[" << mSet.at(i+1) << "]" << std::endl;
    } */
    //std::cout << "Total Tour Distance: " << *tDist << std::endl;
    return mSet;
}


void write_file(std::ofstream *outfile, std::vector<int>* array, int tdist)
{
	std::string buffer;
	std::stringstream out;
	int size = array->size();

	// Print Total Dist traveled
	out.str("");
    out << tdist;
	buffer = out.str();
	outfile->write(buffer.c_str(), buffer.length());
	outfile->write("\n", 1);

	// Print City Tour
	for(int i = 0; i < size - 1; i++){
		out.str("");
		out << array->at(i);
		buffer = out.str();
		outfile->write(buffer.c_str(), buffer.length());
		outfile->write("\n", 1);
	}
	out.str("");
	out << array->at(size-1);
	buffer = out.str();
	outfile->write(buffer.c_str(), buffer.length());
	outfile->write("\n", 2);

    return;
}
