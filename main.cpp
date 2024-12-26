#include <iostream>
#include <random>
#include <iomanip>

double getRandomDouble() {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dis(0.0, 1.0);
	return dis(gen);
}

int main()
{
	uint64_t totalCount = 1;
	uint64_t insideCircle = 0;

	while (true) {
		double x = getRandomDouble();
		double y = getRandomDouble();

		if (x * x + y * y < 1.0) {
			++insideCircle;
		}

		if (totalCount % 1000000 == 0) {
			double piEstimate = 4.0 * insideCircle / totalCount;
			std::cout << std::fixed << std::setprecision(10)  // Set to however many decimals you want
					  << "~ PI " << piEstimate << " Count: " << totalCount << std::endl;
		}
		++totalCount;
	}
	return 0;
}
