#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

// Вариант №3 – findtext – 50 баллов
// Разработайте программу findtext.exe, выполняющую поиск указанной строки в файле. Формат командной строки:
// findtext.exe <file name> <text to search>
// Например:
// findtext.exe “Евгений Онегин.txt” “Я к Вам пишу”
// В случае, когда искомая строка в файле найдена, приложение возвращает нулевое значение и выводит в стандартный выводной поток номера всех строк (по одному номеру в каждой строке), содержащих искомую строку. В противном случае программа возвращает 1 и выводит в стандартный поток вывода «Text not found».
// При осуществлении поиска регистр символов имеет значение (это упрощает поиск). Слова «Онегин» и «онегин» являются разными.
// Программа должна корректно обрабатывать ошибки, связанные с файловыми операциями.
// В комплекте с программой должны обязательно поставляться файлы, позволяющие проверить корректность её работы в автоматическом режиме.

using namespace std;

struct Args
{
    string filePath;
    string searchString;
};


bool CheckArguments(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "File name and text required!" << endl;
        return true;
    }

    if (argv[2] == "") {
        cout << "2 argument must not be empty!" << endl;
        return true;
    }

    return false;
}

optional<Args> ParseCommandLine(int argc, char* argv[])
{
    if (CheckArguments(argc, argv)) {
        return nullopt;
    }

    Args args = {argv[1], argv[2]};
    return args;
}

vector<int> FindSearchText(istream &inputFile, const string& searchString)
{
    vector<int> foundIndexes;
    string line;

    for (int lineIndex = 1; getline(inputFile, line); ++lineIndex)
    {
        auto pos = line.find(searchString);
        if (pos != string::npos)
        {
            foundIndexes.push_back(lineIndex);
        }
    }
    return foundIndexes;
}

void PrintVectorToConsole(const vector<int>& numbers)
{
    for (int number : numbers)
    {
        cout << number << endl;
    }
}

bool FindStringInFile(ifstream & inputFile, const string& searchString)
{
    const vector<int> foundIndexes = FindSearchText(inputFile, searchString);
    inputFile.close();

    if (foundIndexes.empty())
    {
        cout << "Text not found" << endl;
        return false;
    }

    PrintVectorToConsole(foundIndexes);

    return true;
}

int main(int argc, char* argv[])
{
    const optional<Args> args = ParseCommandLine(argc, argv);

    ifstream inputFile(args->filePath);

    if (!inputFile.is_open()) {
        cout << "File not found!"<< endl;
        inputFile.close();
        return 1;
    }

    return FindStringInFile(inputFile, args->searchString);
}

// 0.55
// 0.77
// 0.9