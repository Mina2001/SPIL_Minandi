#include "Shape.h"
#include <cmath>
#include <algorithm>
#include <vector>

Shape::Shape(const std::string& shapeName) : name(shapeName) {}

//Function to add points to the shape
void Shape::addPoint(double x, double y) {
	points.emplace_back(x, y);
}

//Function to calculate the area
double Shape::calculateArea() const {
	double area = 0;
	int n = points.size();
	for (int i = 0; i < n; ++i) {
		double x1 = points[i].first;
		double y1 = points[i].second;
		double x2 = points[(i + 1) % n].first;
		double y2 = points[(i + 1) % n].second;
		area += x1 * y2 - x2 * y1;
	}
	return std::abs(area) / 2.0;
}

// Function to check the overlap
bool Shape::checkOverlap(const Shape& shape1, const Shape& shape2) {
	auto getBoundingBox = [](const Shape& shape) {
		double minX = shape.points[0].first, minY = shape.points[0].second;
		double maxX = shape.points[0].first, maxY = shape.points[0].second;
		for (const auto& p : shape.points) {
			minX = std::min(minX, p.first);
			minY = std::min(minY, p.second);
			maxX = std::max(maxX, p.first);
			maxY = std::max(maxY, p.second);
		}
		return std::make_tuple(minX, minY, maxX, maxY);
	};

	double minX1, minY1, maxX1, maxY1;
	double minX2, minY2, maxX2, maxY2;
	std::tie(minX1, minY1, maxX1, maxY1) = getBoundingBox(shape1);
	std::tie(minX2, minY2, maxX2, maxY2) = getBoundingBox(shape2);

	return !(maxX1 < minX2 || maxX2 < minX1 || maxY1 < minY2 || maxY2 < minY1);
}

std::string Shape::getName() const {
	return name;
}

// Function to check if points are in clockwise order
bool Shape::isClockwise(const std::vector<std::pair<int, int>>& points) {
	int n = points.size();
	if (n < 3) return false; // Not enough points to form a polygon

	// Calculate the signed area of the polygon
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int x1 = points[i].first;
		int y1 = points[i].second;
		int x2 = points[(i + 1) % n].first;
		int y2 = points[(i + 1) % n].second;
		sum += (x2 - x1) * (y2 + y1);
	}

	// If sum is negative, points are in clockwise order; otherwise, counterclockwise
	return sum > 0;
}
