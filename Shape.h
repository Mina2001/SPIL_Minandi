#include <string>
#include <vector>
#include <tuple>

class Shape {
public:
	Shape() = default; // Default constructor
	Shape(const std::string& shapeName);

	void addPoint(double x, double y);

	double calculateArea() const;

	static bool checkOverlap(const Shape& shape1, const Shape& shape2);

	std::string getName() const;

	static bool isClockwise(const std::vector<std::pair<int, int>>& points);

private:
	std::string name;
	std::vector<std::pair<double, double>> points;
};

