#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

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

	auto startTime = std::chrono::steady_clock::now();  // Start timing

	while (true) {
		double x = getRandomDouble();
		double y = getRandomDouble();

		if (x * x + y * y < 1.0) {
			++insideCircle;
		}

		if (totalCount % 1000000 == 0) {
			auto currentTime = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);

			double piEstimate = 4.0 * insideCircle / totalCount;
			std::cout << std::fixed << std::setprecision(10)
					  << "~ PI " << piEstimate
					  << " Count: " << totalCount
					  << " Time: " << duration.count() << "ms" << std::endl;
		}
		++totalCount;
	}
	return 0;
}