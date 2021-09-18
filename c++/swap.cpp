#include <iostream>
#include <vector>
using namespace  std;
// Function returns the
// minimum number of swaps
// required to sort the array
int minSwaps(int arr[], int n)
{
    // Create an array of
    // pairs where first
    // element is array element
    // and second element
    // is position of first element
    pair<int, int> arrPos[n];
    for (int i = 0; i < n; i++)
    {
        arrPos[i].first = arr[i];
        arrPos[i].second = i;
    }

    // Sort the array by array
    // element values to
    // get right position of
    // every element as second
    // element of pair.
    sort(arrPos, arrPos + n);

    // To keep track of visited elements.
    // Initialize
    // all elements as not visited or false.
    vector<bool> vis(n, false);

    // Initialize result
    int ans = 0;

    // Traverse array elements
    for (int i = 0; i < n; i++)
    {
        // already swapped and corrected or
        // already present at correct pos
        if (vis[i] || arrPos[i].second == i)
            continue;

        // find out the number of  node in
        // this cycle and add in ans
        int cycle_size = 0;
        int j = i;
        while (!vis[j])
        {
            vis[j] = 1;

            // move to next node
            j = arrPos[j].second;
            cycle_size++;
        }

        // Update answer by adding current cycle.
        if (cycle_size > 0)
        {
            ans += (cycle_size - 1);
        }
    }

    // Return result
    return ans;
}

int findMinSwaps(int arr[], int n)
{
    // Array to store count of zeroes
    int noOfZeroes[n];
    memset(noOfZeroes, 0, sizeof(noOfZeroes));

    int i, count = 0;

    // Count number of zeroes
    // on right side of every one.
    noOfZeroes[n - 1] = 1 - arr[n - 1];
    for (i = n - 2; i >= 0; i--) {
        noOfZeroes[i] = noOfZeroes[i + 1];
        if (arr[i] == 0)
            noOfZeroes[i]++;
    }

    // Count total number of swaps by adding number
    // of zeroes on right side of every one.
    for (i = 0; i < n; i++) {
        if (arr[i] == 1)
            count += noOfZeroes[i];
    }

    return count;
}
// Driver program to test the above function
int main()
{
    int arr[] = {1, 5, 4, 3, 2};
    int n = (sizeof(arr) / sizeof(int));
    cout << minSwaps(arr, n) << endl;

    int arrs[] = { 0, 0, 1, 0, 1, 0, 1, 1 };
    int n1 = sizeof(arrs) / sizeof(arrs[0]);
    cout << findMinSwaps(arrs, n1) <<endl;
    return 0;
    return 0;
}