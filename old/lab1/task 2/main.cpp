#include <iostream>
#include <vector>
#include <optional>
#include <sstream>

using namespace std;

optional<uint8_t> ParseCommandLine(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Argument required!" << endl;
        return nullopt;
    }

    stringstream arg2(argv[1]);
    int arg;
    arg2 >> arg;

    if (!arg2.eof()) {
        cout << "it's NOT number!" << endl;
        return nullopt;
    }

    if (arg < 0  || arg > 255)
    {
        cout << "number should >= 0 and number <= 255" << endl;
        return nullopt;
    }

    return arg;
}

uint8_t BitRevers(uint8_t byte)
{
    uint8_t result;
    result = (((byte & 0b00001111) << 4) | ((byte & 0b11110000) >> 4));
    result = (((result & 0b00110011) << 2) | ((result & 0b11001100) >> 2));
    result = (((result & 0b10010101) << 1) | ((result & 0b10101010) >> 1));

    return result;
}

int main(int argc, char* argv[])
{
    auto byte = ParseCommandLine(argc, argv);

    if (!byte.has_value())
    {
        return 0;
    }
    cout << (unsigned)BitRevers(byte.value()) << endl;

    return 0;
}