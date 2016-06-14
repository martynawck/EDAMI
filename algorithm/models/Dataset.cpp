//
// Created by Martyna on 2016-05-21.
//

#include <algorithm>
#include <fstream>
#include <istream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <cfloat>
#include "Dataset.h"

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

Dataset::Dataset(std::vector<std::shared_ptr<Point>> data): points(data), referencePoint(Point())
{
}

std::vector<std::shared_ptr<Point>> Dataset::getPoints() {
    return points;
}

void Dataset::setPoints(std::vector<std::shared_ptr<Point>>) {
    this->points = points;
}

int Dataset::getPointsSize() {
    return points.size();
}

int Dataset::getDistanceMeasure() {
    return this->distanceMeasure;
}

void Dataset::setDistanceMeasure(int measure) {
    this->distanceMeasure = measure;
}

bool Dataset::PrecedingPoint(shared_ptr<Point>& point) const {
	auto it = find(points.begin(), points.end(), point);
    if (it != points.begin()) {
        point = *(--it);
        return true;
    }
    return false;
}

bool Dataset::FollowingPoint(std::shared_ptr<Point>& point) const {
    auto it = find(points.begin(), points.end(), point);
	auto end = --points.end();
    if (it != end) {
        point = *(++it);
        return true;
    }
    return false;
}

bool cmd(shared_ptr<Point> p1, shared_ptr<Point> p2) {
    return p1->getDistanceFromReference() < p2->getDistanceFromReference();
}

void Dataset::sortPoints(){
    sort(points.begin(), points.end(), cmd);
}

std::vector<bool> Dataset::getTypeOfAttributes() {
	return typeOfAttributes;
}
void Dataset::setTypeOfAttributes(std::vector<bool> attributes) {
	typeOfAttributes = attributes;
}

void Dataset::calculateRefPointDistance() {
    vector<std::tuple<Point, double>> result;

	for (auto it = points.begin(); it != points.end(); ++it) {

		double distance = referencePoint.calculateDistanceMeasure(**it, this->getDistanceMeasure(), this->getCMinkowski(), this->getTypeOfAttributes(), this->getImportanceOfNominal());
		it->get()->setDistanceFromReference(distance);
	}
}

double Dataset::getCMinkowski() {
    return  this->cMinkowski;
}

void Dataset::setCMinkowski(double c) {
    this->cMinkowski = c;
}

double Dataset::findMaxInAttributeColumn(int column, bool typeOfAttribute) {

	double maxValue = -DBL_MAX;

	if (typeOfAttribute == 0) {
		for (auto point: points) {
			if (point->getAttributes().at(column) > maxValue) {
				maxValue = point->getAttributes().at(column);
			}
		}
	} else {
		map <double, int> frequencyMap;

		for (auto point: points) {
			std::map<double,int>::iterator it = frequencyMap.find(point->getAttributes().at(column));
			if (it == frequencyMap.end()) {
				frequencyMap.insert(std::pair<double,int>(point->getAttributes().at(column),1));
			} else {
				frequencyMap[point->getAttributes().at(column)] +=1;
			}
		}

		double maxFrequency = 0;
		for(auto iter = frequencyMap.begin(); iter != frequencyMap.end(); ++iter) {
			if (iter->second > maxFrequency) {
				maxFrequency = iter->second;
				maxValue = iter->first;
			}
		}
	}
	return  maxValue;
}


double Dataset::findMinInAttributeColumn(int column, bool typeOfAttribute) {

	double minValue = DBL_MAX;

	if (typeOfAttribute == 0) {
		for (auto point: points) {
			if (point->getAttributes().at(column) < minValue) {
				minValue = point->getAttributes().at(column);
			}
		}
	} else {
		map <double, int> frequencyMap;

		for (auto point: points) {
			std::map<double,int>::iterator it = frequencyMap.find(point->getAttributes().at(column));
			if (it == frequencyMap.end()) {
				frequencyMap.insert(std::pair<double,int>(point->getAttributes().at(column),1));
			} else {
				frequencyMap[point->getAttributes().at(column)] +=1;
			}
		}

		double minFrequency = 0;
		for(auto iter = frequencyMap.begin(); iter != frequencyMap.end(); ++iter) {
			if (iter->second < minFrequency) {
				minFrequency = iter->second;
				minValue = iter->first;
			}
		}
	}
	return  minValue;
}


bool isNumeric(const std::string& input) {
	return std::none_of(input.begin(), input.end(), ::isalpha);
}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	std::stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}
	return internal;
}

// changes non numerical into numerical and everything into doubles
auto preNormalize(vector<vector<string>> data, vector<bool> & typeOfAttribute) {
	int numberOfItems = 0;
	//vector<shared_ptr<Point>> points;
	vector<vector<double>> points;
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
			}
			else  {
				// find instance in map
				std::map<string,int>::iterator it = mapOfNonNumericalAttributes.find(std::to_string(column)+" "+s);

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
					mapOfNonNumericalAttributes.insert(std::pair<string,int>(std::to_string(column)+" "+s,nextValue));
					oneRow.push_back(nextValue);
				} else {
					oneRow.push_back(it->second);
				}

				if (i < vector.size())
					typeOfAttribute.push_back(1);
			}
			i++;
			column++;
		}
		points.push_back(oneRow);
		++numberOfItems;
	}
	return points;

}

void rangeNormalization(vector<vector<double>>& data, vector<bool> typeOfAttributes){

	int size = typeOfAttributes.size();
	vector<double> mins(size, DBL_MAX);
	vector<double> maxs(size, -DBL_MAX);

	for (auto row : data) {
		int i = 0;
		for (auto d : row) {
			if (d < mins[i])
				mins[i] = d;
			if (d > maxs[i]) {
				maxs[i] = d;
			}
			++i;
		}
	}

	for (auto &row: data) {
		int i = 0;
		for (auto &val : row) {
			if (typeOfAttributes.at(i) == 0)
				val = (val - mins[i]) / (maxs[i] - mins[i]);
			++i;
		}
	}

}

void z_scoreNormalization(vector<vector<double>>& data, vector<bool> typeOfAttributes) {

	int size = typeOfAttributes.size();
	vector<double> u(size, 0);
	vector<double> S(size, 0);

	for (auto row : data) {
		int i = 0;
		for (auto d : row) {
			if (typeOfAttributes.at(i) == 0)
				u[i]+=d;
			++i;
		}
	}

	for (double &d : u) {
		d = d / data.size();
	}

	for (auto row : data) {
		int i = 0;
		for (auto d : row) {
			if (typeOfAttributes.at(i) == 0) {
				double val = d - u[i];
				if (val < 0)
					val *= (-1);
				S[i]+=val;
			}
			++i;
		}
	}

	for (double &d : S) {
		d = d / data.size();
	}

	for (auto& row : data) {
		int i = 0;
		for (auto& d : row) {
			if (typeOfAttributes[i] == 0)
				d = (d - u[i]) / S[i];
			++i;
		}
	}
}



void cosineNormalization(vector<vector<double>>& data, vector<bool> typeOfAttributes,double& alpha){
	int column = 0;

	for (auto &point : data) {
		double magnitude = 0;

		for (auto value : point) {
			if (typeOfAttributes.at(column) == 0) {
				magnitude += value*value;
			}
			++column;
		}

		magnitude = sqrt(magnitude);

		column = 0;
		for (auto &value : point) {
			if (typeOfAttributes.at(column) == 0) {
				value = (value/magnitude) * alpha;
			}
			++column;
		}

		column = 0;
	}
	int i =0;
}

void normalize(vector<vector<double>> &data, double& alpha, vector<bool>& typeOfAttribute, int normalizationType) {
	switch(normalizationType) {
		case 0:
			break;
		case 1:
			rangeNormalization(data, typeOfAttribute);
			break;
		case 2:
			z_scoreNormalization(data, typeOfAttribute);
			break;
		case 3:
			cosineNormalization(data, typeOfAttribute,alpha);
			break;
	}
}

auto Dataset::readDatasetFile(string const& filename, vector<bool>& typeOfAttribute, double alpha, int typeOfNormalization) -> std::shared_ptr<Dataset>
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
	vector<std::shared_ptr<Point>> points;


	auto data = preNormalize(values, typeOfAttribute);
	normalize(data, alpha, typeOfAttribute, typeOfNormalization);

	for (auto const& it: data){
		points.push_back(std::shared_ptr<Point>(new Point(it, i++)));
	}
	return std::shared_ptr<Dataset>(new Dataset(points));
}



void Dataset::readReferencePointFile(std::string const& filename, std::vector<bool>& typeOfAttribute) {
	std::vector<string> values;
	std::ifstream fin(filename);
	for (std::string line; std::getline(fin, line); ) {
		std::replace(line.begin(), line.end(), ',', ' ');
		std::istringstream in(line);
		values = std::vector<string>(std::istream_iterator<string>(in), std::istream_iterator<string>());
	}

	std::vector<double> refPointValues;

	for (int i = 0; i < values.size(); i++) {
		if (values.at(i) == "max" ) {
			refPointValues.push_back(findMaxInAttributeColumn(i, typeOfAttribute.at(i)));
		}
		else {
			refPointValues.push_back(findMinInAttributeColumn(i, typeOfAttribute.at(i)));
		}
	}
	setReferencePoint(Point(refPointValues, -1));
}



void Dataset::setImportanceOfNominal(double importance) {
	importanceOfNominal = importance;
}
double Dataset::getImportanceOfNominal() {
	return importanceOfNominal;
}

const Point& Dataset::getReferencePoint() const {
    return referencePoint;
}

void Dataset::setReferencePoint(const Point &referencePoint) {
    Dataset::referencePoint = referencePoint;
}



