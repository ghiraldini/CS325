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

/*****************************************************************
 * Things to consider
 *    1.  Command line options
 *
 ******************************************************************/

void readFile(char *, std::vector<std::pair<int,int> > *);
void write_file(std::ofstream *, std::vector<int>*, int);

double getDistance(std::pair<int,int> c1, std::pair<int,int> c2){
    double ans = sqrt( pow(c1.first - c2.first,2) + pow(c1.second - c2.second,2) );
    //ans+=0.5;
    return ans;
    //return sqrt( pow(c1.first - c2.first,2) + pow(c1.second - c2.second,2) );
}

double getMinDist(std::vector<std::pair<int,int> > *,
               int *, int *, int ,
               std::vector<double> *,
               std::map<double,int> *);

std::vector<int> mst(std::vector<std::pair<int,int> > *, double *);
bool myfunction (int i,int j) { return (i<j); }
bool vertexFound(std::vector<int> , int);

// GLOBAL CONSTS
static const bool DEBUG = false;
static const int ex_1 = 108159;
static const int ex_2 = 2579;
static const int ex_3 = 1573084;

/******************************************************
 * DESCRIPTION:
 * INPUTS:
 * OUTPUTS:
 *
 ******************************************************/
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
    double totalDist = 0;
    std::vector<int> mstTour = mst(&cityPair, &totalDist);

    std::cout << "Total Dist Travel: " << totalDist << std::endl;
    std::cout << "Ratio: " << (double)totalDist/ex_2;

    write_file(&outfile, &mstTour, totalDist);

    outfile.close();
	return 0;
}

/******************************************************
 * DESCRIPTION:
 * INPUTS:
 * OUTPUTS:
 *
 ******************************************************/
std::vector<int> mst(std::vector<std::pair<int,int> > *cityPair, double *tDist){
    std::vector<int> mSet;
    mSet.push_back(0);
    std::vector<double> tempCityVec;
    std::map<double,int> tempCityMap;
    int c1=0, c2=0, nextMin=0;

    while(mSet.size() < cityPair->size()-1){
        double tempDist = getMinDist(cityPair, &c1, &c2, nextMin, &tempCityVec, &tempCityMap);
        if(!vertexFound(mSet,c2)){
            std::sort(tempCityVec.begin(), tempCityVec.end(), myfunction);
            c2 = tempCityMap[tempCityVec.at(nextMin)];
            tempDist = tempCityVec.at(nextMin);
        }
        while(!vertexFound(mSet,c2)){
            nextMin++;
            c2 = tempCityMap[tempCityVec.at(nextMin)];
            tempDist = tempCityVec.at(nextMin);
        }
        mSet.push_back(c2);
        *tDist += round(tempDist);
/*        std::cout   << "New Vertex: " << c2
                    << "\tTour Size: " << mSet.size()
                    << "\tDistance: " << *tDist
                    << "\tDistance: " << round(*tDist) << std::endl;
*/
        tempCityVec.clear();
        tempCityMap.clear();
        nextMin = 0;
        c1 = c2;
        c2 = 0;
    }
    *tDist += round(getDistance(cityPair->at(mSet.size()), cityPair->at(0)));
    return mSet;
}

/***************** HELPER FUNTIONS ********************/


/******************************************************
 * DESCRIPTION:
 * INPUTS:
 * OUTPUTS:
 *
 ******************************************************/
double getMinDist(std::vector<std::pair<int,int> > *cityPair, int *startIdx, int *endCity, int nextMin,
               std::vector<double> *cityVec, std::map<double,int> *cityMap){

    double minDist = 2e8;
    if(DEBUG) std::cout << "Looking for Min Dist from city " << *startIdx << std::endl;

    for(int i = 0; i < (int)cityPair->size(); i++){
        if(*startIdx != i){
            // Push all distances from city1 to all cities
            double d = getDistance(cityPair->at(*startIdx), cityPair->at(i));
            cityVec->push_back(d); // Vector of distances
            (*cityMap)[d] = i; // Map[dist, city]
            minDist = std::min(minDist, d);
        }
    }
    *endCity = (*cityMap)[minDist];
    return minDist; // return min distance
}


/******************************************************
 * DESCRIPTION:
 * INPUTS:
 * OUTPUTS:
 *
 ******************************************************/
bool vertexFound(std::vector<int> mSet, int c2){
    for(unsigned int i = 0; i < mSet.size(); i++){
        if(c2 == mSet.at(i)){
            if(DEBUG) std::cout << "Vertex " << c2 << " already in MAP!!!" << std::endl;
            return false;
        }
    }
    return true;
}


/******************************************************
 * DESCRIPTION:
 * INPUTS:
 * OUTPUTS:
 *
 ******************************************************/
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

/******************************************************
 * DESCRIPTION:
 * INPUTS:
 * OUTPUTS:
 *
 ******************************************************/
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
