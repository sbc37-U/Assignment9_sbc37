
#include <iostream>
#include <stdexcept>

using namespace std;

// Template class for numerical data types.
template <typename T>
class GenericArray
{
private:
    T* values;       // Pointer to dynamically allocated array.
    int arraySize;   // Number of elements in the array.

public:
    // Default constructor: create an empty array.
    GenericArray()
    {
        values = nullptr;
        arraySize = 0;
    }

    // Copy constructor: create an independent copy.
    GenericArray(const GenericArray<T>& other)
    {
        arraySize = other.arraySize;
        values = new T[arraySize];

        for (int i = 0; i < arraySize; i++)
        {
            values[i] = other.values[i];
        }
    }

    // Copy assignment operator: prevent shallow copies.
    GenericArray<T>& operator=(const GenericArray<T>& other)
    {
        if (this != &other)
        {
            T* newValues = new T[other.arraySize];

            for (int i = 0; i < other.arraySize; i++)
            {
                newValues[i] = other.values[i];
            }

            delete[] values;
            values = newValues;
            arraySize = other.arraySize;
        }

        return *this;
    }

    // Destructor: release dynamically allocated memory.
    ~GenericArray()
    {
        delete[] values;
    }

    // Add an element to the end of the array.
    void addElement(T element)
    {
        // Allocate a new array with one additional element.
        T* newValues = new T[arraySize + 1];

        // Copy existing elements into the new array.
        for (int i = 0; i < arraySize; i++)
        {
            newValues[i] = values[i];
        }

        // Add the new element at the end.
        newValues[arraySize] = element;

        // Delete the old array to avoid memory leaks.
        delete[] values;

        // Update the pointer and size.
        values = newValues;
        arraySize++;
    }

    // Return the element at a zero-based index.
    T at(int index) const
    {
        if (index < 0 || index >= arraySize)
        {
            throw out_of_range("Index is out of bounds.");
        }

        return values[index];
    }

    // Return the number of elements.
    int size() const
    {
        return arraySize;
    }

    // Calculate the sum of all elements.
    T sum() const
    {
        T total = T{};

        for (int i = 0; i < arraySize; i++)
        {
            total += values[i];
        }

        return total;
    }

    // Find the maximum element.
    T max() const
    {
        if (arraySize == 0)
        {
            throw out_of_range("Array is empty.");
        }

        T maximum = values[0];

        for (int i = 1; i < arraySize; i++)
        {
            if (values[i] > maximum)
            {
                maximum = values[i];
            }
        }

        return maximum;
    }

    // Find the minimum element.
    T min() const
    {
        if (arraySize == 0)
        {
            throw out_of_range("Array is empty.");
        }

        T minimum = values[0];

        for (int i = 1; i < arraySize; i++)
        {
            if (values[i] < minimum)
            {
                minimum = values[i];
            }
        }

        return minimum;
    }

    // Return a new array containing the selected slice.
    // Use one-based positions, as shown in Canvas.
    // Both begin and end are included.
    T* slice(int begin, int end) const
    {
        // Check that both positions are valid.
        if (begin < 1 || end > arraySize || begin > end)
        {
            throw out_of_range("Invalid slice bounds.");
        }

        int sliceSize = end - begin + 1;

        // Allocate independent memory for the slice.
        T* slicedArray = new T[sliceSize];

        // Copy the requested elements into the new array.
        for (int i = 0; i < sliceSize; i++)
        {
            slicedArray[i] = values[begin - 1 + i];
        }

        return slicedArray;
    }
};

// Main function: test all required functions.
int main()
{
    cout << "ECE 231L - Assignment 9: Generic Programming\n";

    // Create an integer array using the template class.
    GenericArray<int> int_array;

    // Add 12 elements using dynamic memory allocation.
    for (int i = 1; i <= 12; i++)
    {
        int_array.addElement(i * 2);
    }

    // Print the entire integer array.
    cout << "\nInteger array: ";

    for (int i = 0; i < int_array.size(); i++)
    {
        cout << int_array.at(i) << " ";
    }

    cout << endl;

    // Demonstrate the basic functions.
    cout << "Size of array is: "
         << int_array.size() << endl;

    cout << "Sum of array is: "
         << int_array.sum() << endl;

    cout << "Maximum of array is: "
         << int_array.max() << endl;

    cout << "Minimum of array is: "
         << int_array.min() << endl;

    cout << "Element at index 3 is: "
         << int_array.at(3) << endl;

    // Slice positions 5 through 10, inclusive.
    int begin = 5;
    int end = 10;

    int* sliced_array = int_array.slice(begin, end);

    cout << "\nSliced array (positions 5 to 10): ";

    for (int i = 0; i < end - begin + 1; i++)
    {
        cout << sliced_array[i] << " ";
    }

    cout << endl;

    // Free the memory allocated by slice().
    delete[] sliced_array;

    // Demonstrate the template with double values.
    GenericArray<double> double_array;

    double_array.addElement(1.5);
    double_array.addElement(2.5);
    double_array.addElement(3.5);
    double_array.addElement(4.5);

    cout << "\nDouble array: ";

    for (int i = 0; i < double_array.size(); i++)
    {
        cout << double_array.at(i) << " ";
    }

    cout << endl;

    cout << "Size: " << double_array.size() << endl;
    cout << "Sum: " << double_array.sum() << endl;
    cout << "Maximum: " << double_array.max() << endl;
    cout << "Minimum: " << double_array.min() << endl;

    // Demonstrate that invalid slice bounds are rejected.
    try
    {
        int* invalidSlice = int_array.slice(10, 20);
        delete[] invalidSlice;
    }
    catch (const out_of_range& error)
    {
        cout << "\nBounds checking: "
             << error.what() << endl;
    }

    // Demonstrate that the copy constructor works.
    GenericArray<int> copied_array(int_array);

    cout << "Copied array size: "
         << copied_array.size() << endl;

    return 0;
}
