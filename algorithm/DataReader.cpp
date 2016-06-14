//
// Created by Martyna on 2016-06-08.
//

#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
//#include <rpcndr.h>
#include "DataReader.h"
using namespace std;

vector<vector<double>> intoDoubles2(vector<vector<string>> vec) {
    vector<vector<double>> vectorx;
    vector<vector<string>>::iterator it;
    vector<string>::iterator it2;

    for (it = vec.begin(); it != vec.end(); ++it) {
        vector<double> vecd;
        for (it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
            vecd.push_back(atof((*it2).c_str()));
        }
        vectorx.push_back(vecd);
    }

    return vectorx;
}

bool isNumeric(const std::string& input) {
    return std::none_of(input.begin(), input.end(), ::isalpha);
}

vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}


auto normalize(vector<vector<string>> data, vector<bool> & typeOfAttribute, double &alpha) {
    int numberOfItems = 0;
    vector<shared_ptr<Point>> points;
    std::map<string,int> mapOfNonNumericalAttributes;

    vector<double> oneRow;
    int i = 0;

    for (vector<string> vector : data) {

        oneRow.clear();

        int column = 0;

        // for each string
        for (string s : vector) {
            // if string is a number then
            if (isNumeric(s) ){
                // change it to double
                double doubleValue = atof(s.c_str());//s,s.end());
                // mark boolean vector as 0 => numerical value
                if (i < vector.size())
                    typeOfAttribute.push_back(0);// = 0;
                //add to vector
                oneRow.push_back(doubleValue);

                cout<<"numeric"<<endl;
             }
            else  {
                // find instance in map
                std::map<string,int>::iterator it = mapOfNonNumericalAttributes.find(to_string(column)+" "+s);

                // if not found
                if (it == mapOfNonNumericalAttributes.end()) {
                    int nextValue = 1;
                    //count the max value in the db
                    for(auto ent1 : mapOfNonNumericalAttributes) {
                        std::vector<std::string> elems = split(ent1.first, ' ');
                        // getfirst caracter
                        string key = elems[0];
                        int first = atoi(key.c_str());

                        if (first == column) {
                            if (ent1.second > nextValue)
                                nextValue = ent1.second;
                        } else
                            continue;
                    }
                    ++nextValue;
                    mapOfNonNumericalAttributes.insert(std::pair<string,int>(to_string(column)+" "+s,nextValue));
                    oneRow.push_back(nextValue);
                } else {
                    oneRow.push_back(it->second);
                }

                if (i < vector.size())
                    typeOfAttribute.push_back(1);

                cout<<"non"<<endl;
            }
            i++;
            column++;
        }


        column = 0;

        double magnitude = 0;
        for (auto value : oneRow) {
            if (typeOfAttribute.at(column) == 0) {
                magnitude += value*value;
            }

            ++column;
        }

        magnitude = sqrt(magnitude);

        cout <<magnitude<<endl;

        column = 0;
        for (auto &value : oneRow) {
            if (typeOfAttribute.at(column) == 0) {
                value = value/magnitude * alpha;
            }
            ++column;
        }

        Point poiunt = Point(oneRow,numberOfItems);
        points.push_back(&poiunt);

        ++numberOfItems;
    }


    return points;

}

auto DataReader::readDatasetFile(string const& filename, vector<bool>& typeOfAttribute, double& alpha) -> std::shared_ptr<Dataset>
{
    std::vector<std::vector<string> > values;
    std::ifstream fin(filename);
    for (std::string line; std::getline(fin, line); ) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values.push_back(
                std::vector<string>(std::istream_iterator<string>(in),
                                    std::istream_iterator<string>()));
    }


    int i = 1;
    //vector<std::shared_ptr<Point>> points = normalize(values, typeOfAttribute, alpha);
  //  vector<Point> pointz = normalize(values, typeOfAttribute, alpha);
    vector<std::shared_ptr<Point>> pointz = normalize(values, typeOfAttribute, alpha);
    return std::shared_ptr<Dataset>(new Dataset(pointz));
}
/*
bool isOnlyDouble(string str)
{
    char* endptr = 0;
    strtod(str, &endptr);

    if(*endptr != '\0' || endptr == str)
        return false;
    return true;
}
*/





vector<string> DataReader::readReferencePointFile(Dataset& dataset, vector<bool>& typeOfAttribute, string const& filename) {
    std::vector<string> values;
    std::ifstream fin(filename);
    for (std::string line; std::getline(fin, line); ) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values = std::vector<string>(std::istream_iterator<string>(in), std::istream_iterator<string>());
    }

    return values;
}



