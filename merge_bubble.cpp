#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &a)
{
    int n = a.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int> &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
#pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2)
            {
                if (a[j] > a[j + 1])
                {
                    swap(a[j], a[j + 1]);
                }
            }
        }
        else
        {
#pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2)
            {
                if (a[j] > a[j + 1])
                {

                    swap(a[j], a[j + 1]);
                }
            }
        }
    }
}

void merge(vector<int> &a, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = a[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = a[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1)
    {
        a[k++] = L[i++];
    }
    while (j < n2)
    {
        a[k++] = R[j++];
    }
}

void mergeSort(vector<int> &a, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void parallelMergeSort(vector<int> &a, int l, int r, int depth = 0)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        if (depth < 4)
        {
#pragma omp parallel sections
            {
#pragma omp section
                parallelMergeSort(a, l, m, depth + 1);
#pragma omp section
                parallelMergeSort(a, m + 1, r, depth + 1);
            }
        }
        else
        {
            mergeSort(a, l, m);
            mergeSort(a, m + 1, r);
        }
        merge(a, l, m, r);
    }
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i)
        cin >> original[i];

    vector<int> a;

    a = original;
    bubbleSort(a);
    cout << "\nSequential Bubble Sort output:\n";
    for (int x : a)
        cout << x << ' ';
    cout << '\n';

    a = original;
    parallelBubbleSort(a);
    cout << "\nParallel Bubble Sort output:\n";
    for (int x : a)
        cout << x << ' ';
    cout << '\n';

    a = original;
    mergeSort(a, 0, n - 1);
    cout << "\nSequential Merge Sort output:\n";
    for (int x : a)
        cout << x << ' ';
    cout << '\n';

    // Parallel Merge Sort
    a = original;
    parallelMergeSort(a, 0, n - 1);
    cout << "\nParallel Merge Sort output:\n";
    for (int x : a)
        cout << x << ' ';
    cout << '\n';

    return 0;
}