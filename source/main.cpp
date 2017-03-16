#include <stdio.h>
#include <vector>
#include <fstream>
#include <numeric>

#ifdef  _WIN32
    #include "gettime.h"
#else
    #include <sys/time.h>
#endif

void quickSort(std::vector<int> &vector, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = vector[(left + right) / 2];

    while (i <= j) {
        while (vector[i] < pivot)
            i++;
        while (vector[j] > pivot)
            j--;
        if (i <= j) {
            tmp = vector[i];
            vector[i] = vector[j];
            vector[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(vector, left, j);
    if (i < right)
        quickSort(vector, i, right);
}


int main(int argc, char* argv[]) {
    std::string fileName;

    if (argv[1] == NULL) {
        printf("Enter the file name as a first argument.\n");
        return 1;
    } else {
        fileName = argv[1];
    }

    struct timeval startTime, finishTime;
    long int min = 0, max = 0;
    double mean = 0, avg = 0, elapsedTime = 0;
    std::vector<int> numbers;
    std::string line;
    std::ifstream file(fileName);

    gettimeofday(&startTime, NULL);

    if (file.is_open()) {
        while (getline(file, line)) {
            numbers.push_back(atoi(line.c_str()));
        }
        file.close();
    } else {
        printf("Error when opening file.\n");
        return 1;
    }

    quickSort(numbers, 0, numbers.size() - 1);

    min = numbers.front();
    max = numbers.back();
    mean = (numbers.at(numbers.size() / 2 - 1) + numbers.at(numbers.size() / 2)) / 2.0;
    avg = 1.0 * std::accumulate(numbers.begin(), numbers.end(), 0LL) / numbers.size();

    printf("Min value: %ld\n", min);
    printf("Max value: %ld\n", max);
    printf("Mean value: %f\n", mean);
    printf("Average value: %f\n", avg);

    gettimeofday(&finishTime, NULL);
    elapsedTime = (finishTime.tv_sec - startTime.tv_sec) * 1000 + (finishTime.tv_usec - startTime.tv_usec) / 1000;
    printf("Elapsed time: %fms\n", elapsedTime);
    return 0;
}