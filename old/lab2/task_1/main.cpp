#include "Functions.h"

using namespace std;

int main() {
    auto numbers = ReadArrayFromStream(cin);

    if (!DivideByHalfMax(numbers))
    {
        return EXIT_FAILURE;
    }

    SortVector(numbers);
    WriteVectorToStream(numbers, cout);

    return EXIT_SUCCESS;
}
