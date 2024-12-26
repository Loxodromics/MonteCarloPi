#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>

uint64_t calculatePoints(uint64_t pointsPerThread) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.0, 1.0);

	uint64_t localInside = 0;
	for (uint64_t i = 0; i < pointsPerThread; ++i) {
		double x = dis(gen);
		double y = dis(gen);
		if (x * x + y * y < 1.0) {
			++localInside;
		}
	}
	return localInside;
}

int main() {
	const uint64_t totalPoints = 10000000000;  // 10 billion points
	const unsigned numThreads = std::thread::hardware_concurrency();
	const uint64_t pointsPerThread = totalPoints;

	std::vector<std::thread> threads;
	std::vector<uint64_t> results(numThreads);

	auto startTime = std::chrono::steady_clock::now();

	/// Start threads
	for (unsigned i = 0; i < numThreads; ++i) {
		threads.emplace_back([i, pointsPerThread, &results]() {
			results[i] = calculatePoints(pointsPerThread);
		});
	}

	/// Wait for all threads to complete
	for (auto& thread : threads) {
		thread.join();
	}

	/// Sum up results
	uint64_t totalInside = 0;
	for (auto count : results) {
		totalInside += count;
	}

	auto endTime = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	double piEstimate = 4.0 * totalInside / (pointsPerThread * numThreads);

	std::cout << std::fixed << std::setprecision(10)
			  << "~ PI " << piEstimate
			  << " Count: " << totalPoints
			  << " Threads: " << numThreads
			  << " Time: " << duration.count() << "ms" << std::endl;

	return 0;
}