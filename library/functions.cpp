#include "functions.hpp"

int randomNumber(int start, int end)
{
    auto rand = bind(uniform_int_distribution<int>{start, end},
                     default_random_engine{random_device()()});

    return rand();
}

void vectorData(vector<int> &numbers, int size, int start, int end)
{
    int counter = 0;

    while (counter < size)
    {
        numbers.push_back(randomNumber(start, end));

        counter++;
    }
}

void showVector(vector<int> &numbers)
{
    if (numbers.empty())
        return;

    cout << "Numbers [ ";

    for (int &number : numbers)
        cout << number << " ";

    cout << "]" << endl;
}

short int breadManager(int counter1, int counter2, vector<short int> &breads, int max, int value)
{
    if (value == 0 || value == 1)
        breads[counter1 * max + counter2] = value;

    return breads[counter1 * max + counter2];
}

vector<int> breadSort(vector<int> &numbers, int size)
{
    // Get the max element
    int max = *max_element(numbers.begin(), numbers.end());

    // Create the breads (exponential)
    vector<short int> breads(max * size);

    // Initialize the breads
    fill(breads.begin(), breads.end(), 0);

    // Mark the breads
    for (int counter_size = 0; counter_size < size; counter_size++)
        for (int counter_element = 0; counter_element < numbers[counter_size]; counter_element++)
            breadManager(counter_size, counter_element, breads, max, 1);

    for (int counter_max = 0; counter_max < max; counter_max++)
    {
        // Count the breads
        int total = 0;

        for (int counter_size = 0; counter_size < size; counter_size++)
        {
            total += breadManager(counter_size, counter_max, breads, max, -1);

            breadManager(counter_size, counter_max, breads, max, 0);
        }

        for (int counter_numbers = size - total; counter_numbers < size; counter_numbers++)
            breadManager(counter_numbers, counter_max, breads, max, 1);
    }

    // Get sorted values
    for (int counter_size = 0; counter_size < size; counter_size++)
    {
        int counter_max = 0;

        for (; counter_max < max && breadManager(counter_size, counter_max, breads, max, -1); counter_max++)
            ;

        numbers[counter_size] = counter_max;
    }

    return numbers;
}