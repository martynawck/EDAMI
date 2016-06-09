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


vector<vector<double>> intoDoubles(vector<vector<string>> vec) {
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
    if (it != (points.end()-1)) {
        point = *(++it);
        return true;
    }
    return false;
}

bool cmd(shared_ptr<Point> p1, shared_ptr<Point> p2) {
    return p1->getDistance() < p2->getDistance();
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

	// HARD CODED REFERENCE POINT
//	vector <double> vector1 (2, 0.0);
//	referencePoint = Point(vector1,-1);
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

/*
auto Dataset::readDatasetFile(string const& filename) -> std::shared_ptr<Dataset>
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
	for (auto const& it: intoDoubles(values)) {
		points.push_back(std::shared_ptr<Point>(new Point(it, i++)));
	}
	return std::shared_ptr<Dataset>(new Dataset(points));
}
*/


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


auto normalize(vector<vector<string>> data, vector<bool> & typeOfAttribute, double &alpha) {
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


		column = 0;

		double magnitude = 0;
		for (auto value : oneRow) {
			if (typeOfAttribute.at(column) == 0) {
				magnitude += value*value;
			}

			++column;
		}

		magnitude = sqrt(magnitude);

		column = 0;
		for (auto &value : oneRow) {
			if (typeOfAttribute.at(column) == 0) {
				value = value/magnitude * alpha;
				if (value < 0)
					value *= (-1);
			}
			++column;
		}

	//	std::shared_ptr<Point> point = Point(oneRow,numberOfItems);
		points.push_back(oneRow);

		++numberOfItems;
	}


	return points;

}

auto Dataset::readDatasetFile(string const& filename, vector<bool>& typeOfAttribute, double& alpha) -> std::shared_ptr<Dataset>
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
	for (auto const& it: normalize(values, typeOfAttribute, alpha)) {
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
	//return values;
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



