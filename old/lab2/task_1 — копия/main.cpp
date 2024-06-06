#include "Functions.h"

using namespace std;

int main() {
    vector<float> numbers = ReadArrayFromStream(cin);

    if (!DivideByHalfMax(numbers))
    {
        return 1;
    }

    SortVector(numbers);
    WriteVectorToStream(numbers, cout);

    return 0;
}
