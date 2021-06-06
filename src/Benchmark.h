//
// Created by Wladyslaw Nowak on 27.05.2021.
//

#ifndef SDIZO2_BENCHMARK_H
#define SDIZO2_BENCHMARK_H

#include <windows.h>
#include <string>
#include <iostream>
#include <random>
#include "AlgType.h"
#include "GraphRepresentations/MatrixRepresentation.h"
#include "GraphRepresentations/ListRepresentation.h"
#include "IO/CSVWriter.h"
#include "Algorithms/BellmanFord/BellmanFordMatrix.h"
#include "Algorithms/BellmanFord/BellmanFordList.h"
#include "Algorithms/Dijsktra/DijsktraMatrix.h"
#include "Algorithms/Dijsktra/DijsktraList.h"
#include "Algorithms/FordFulkerson/FordFulkersonMatrix.h"
#include "Algorithms/FordFulkerson/FordFulkersonList.h"
#include "Algorithms/Kruskal/KruskalMatrix.h"
#include "Algorithms/Kruskal/KruskalList.h"
#include "Algorithms/Prims/PrimsMatrix.h"
#include "Algorithms/Prims/PrimsList.h"


using namespace std;
class Benchmark {
private:
    /**
     * Class-specific performance counter.
     */
    LARGE_INTEGER* performanceCounter;
    mt19937 randNumGen;
    uniform_int_distribution<int> numberDistribution;

    AlgType type;

    /**
     * Amount of times the tests should be run - then the values are averaged.
     */
    int testNumber;

    /**
     * Initial size to start tests from.
     */
    int initialSize;

    /**
     * Step to increment size by every iteration.
     */
    int step;

    /**
     * Multiplier to multiply size by every iteration.
     */
    float multiplier;

    /**
     * Max size to be reached.
     */
    int maxSize;

    /**
     * Expected iteration number.
     */
    int iterationNumber{};

    /**
    * Should produce output to csv file.
    */
    bool isWriteToFile;

    /**
     * Start counting time.
     */
    void startTimer();

    /**
     * Stop counting time and return it in us (micro-seconds).
     * @return Time passed since last startTimer call.
     */
    double stopTimer();

    /**
     * Calculate amount of required iterations to meet input requirements.
     * This function initializes iterationNumber.
     */
    void calcIterationNumber();

    /**
     * Get next random int number generated by given distribution.
     * @param dist Distribution to be used.
     * @return Random value.
     */
    int getNextRandom(uniform_int_distribution<int>& dist);

    uniform_int_distribution<int> getRandomInRange(int a, int b);

    /**
     * Function that prepares data and sends it to CSVWriter.
     * @param testName This is name of file to be generated (suffix .csv will be appended).
     * @param data Array containing time results to be written.
     * @param size Array containing corresponding sizes of data structures.
     */
    void
    writeToFile(string testName, double* resultArrayMatrix25, double* resultArrayList25, double* resultArrayMatrix50,
                double* resultArrayList50, double* resultArrayMatrix75, double* resultArrayList75,
                double* resultArrayMatrix99, double* resultArrayList99, int* size);
public:
    Benchmark(AlgType type, bool writeToFile, int initialSize, int step, float multiplier, int testNumber, int maxSize);

    void startTest();

    void generatePopulation(double d, MatrixRepresentation *mRepresentation, ListRepresentation *lRepresentation1,
                            bool directed, int vertSize);
};


#endif //SDIZO2_BENCHMARK_H
