#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include "Shape.h"

// Function to read the data from files
void readShapesFromFile(const std::string& filename, std::vector<Shape>& shapes) {
	std::ifstream infile(filename);
	if (!infile) {
		std::cerr << "Error: Failed to open file '" << filename << "'" << std::endl;
		return;
	}

	std::string line;
	std::regex re("\\(([^)]+)\\)");

	while (std::getline(infile, line)) {
		std::istringstream iss(line);

		std::string shapeName;
		std::getline(iss, shapeName, ','); // Extract shape name

		Shape shape(shapeName); // Create a shape object with the extracted name

		std::string coordsStr;
		std::getline(iss, coordsStr);

		// Iterate through all matches of the regular expression
		std::sregex_iterator begin(coordsStr.begin(), coordsStr.end(), re);
		std::sregex_iterator end;

		std::vector<std::pair<int, int>> points;

		for (std::sregex_iterator i = begin; i != end; ++i) {
			std::smatch match = *i;
			std::string pairStr = match[1].str(); // Extract the matched content inside parentheses

			std::istringstream pairStream(pairStr);
			std::string xStr, yStr;

			std::getline(pairStream, xStr, ',');
			std::getline(pairStream, yStr, ',');

			int x = std::stoi(xStr);
			int y = std::stoi(yStr);

			points.emplace_back(x, y);
		}

		// Ensure points form a closed polygon in clockwise order
		if (!Shape::isClockwise(points)) {
			std::reverse(points.begin(), points.end()); // Reverse to make clockwise
		}

		// Add points to the shape object
		for (const auto& point : points) {
			shape.addPoint(point.first, point.second);
		}

		shapes.push_back(shape);
	}
}

int main() {
	std::vector<Shape> shapes;
	readShapesFromFile("data.txt", shapes);

	std::map<std::string, double> shapeAreas;
	std::set<std::string> overlappingShapes;

	for (const auto& shape : shapes) {
		double area = shape.calculateArea();
		shapeAreas[shape.getName()] = area;
		std::cout << "Shape: " << shape.getName() << ", Area: " << area << std::endl;
	}

	for (size_t i = 0; i < shapes.size(); ++i) {
		for (size_t j = i + 1; j < shapes.size(); ++j) {
			if (Shape::checkOverlap(shapes[i], shapes[j])) {
				overlappingShapes.insert(shapes[i].getName());
				overlappingShapes.insert(shapes[j].getName());
			}
		}
	}

	std::cout << "Overlapping shapes: ";
	for (const auto& name : overlappingShapes) {
		std::cout << name << " ";
	}
	std::cout << std::endl;

	return 0;
}

