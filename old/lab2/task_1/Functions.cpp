#include "Functions.h"

using namespace std;

vector<float> ReadArrayFromStream(istream& input)
{
    cout << "Input numbers: " << endl;
    return vector<float>{istream_iterator<float>(input), istream_iterator<float>()};
}

void SortVector(vector<float>& arr)
{
    sort(arr.begin(), arr.end());
}

void WriteVectorToStream(vector<float>& arr, ostream& output)
{
    copy(arr.begin(), arr.end(), ostream_iterator<float>(output << setprecision(3) << fixed, ", "));
}

bool DivideByHalfMax(vector<float>& numbers)
{
    if (numbers.empty())
    {
        cout << "Vector empty" << endl;
        return true;
    }

    const float maxNumber = *max_element(numbers.begin(), numbers.end());
    const float halfMaxNumber = maxNumber / 2;

    if (halfMaxNumber == 0)
    {
        cout << "halfMaxNumber = 0" << endl;
        return false;
    }

    for (float& number : numbers)
    {
        number /= halfMaxNumber;
    }

    return true;
}