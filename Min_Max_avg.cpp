#include <iostream>
#include <omp.h>
using namespace std;

int minval(int arr[], int n) {
    int minval = arr[0];
    #pragma omp parallel
    {
        int local_min = arr[0];
        #pragma omp for nowait
        for (int i = 1; i < n; i++) {
            if (arr[i] < local_min)
                local_min = arr[i];
        }
        #pragma omp critical
        {
            if (local_min < minval)
                minval = local_min;
        }
    }
    return minval;
}

int maxval(int arr[], int n) {
    int maxval = arr[0];
    #pragma omp parallel
    {
        int local_max = arr[0];
        #pragma omp for nowait
        for (int i = 1; i < n; i++) {
            if (arr[i] > local_max)
                local_max = arr[i];
        }
        #pragma omp critical
        {
            if (local_max > maxval)
                maxval = local_max;
        }
    }
    return maxval;
}

int sum(int arr[], int n) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

double average(int arr[], int n) {
    return (double)sum(arr, n) / n;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Minimum value: " << minval(arr, n) << endl;
    cout << "Maximum value: " << maxval(arr, n) << endl;
    cout << "Sum: " << sum(arr, n) << endl;
    cout << "Average: " << average(arr, n) << endl;

    return 0;
}
