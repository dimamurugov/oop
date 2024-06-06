@echo off

set OUT="%TEMP%\out.txt"

:: Тестируем поиск слова
echo Test: search for the word "Line"
findText.exe input_1.txt line > %OUT% || goto err
fc %OUT% output_1.txt || goto err

:: Тестируем поиск словосочетания
echo Test: search for the phrase "Third line"
findText.exe input_2.txt "Third line" > %OUT% || goto err
fc %OUT% output_2.txt || goto err

:: Тестируем обработку ошибки пустой строки
echo Test: empty string error
findText.exe input_3.txt "" > %OUT% || goto err
fc %OUT% output_3.txt || goto err

:: Тестируем случай отсутствия пути к файлу
echo Test: no first argument
findText.exe test > %OUT% || goto err
fc %OUT% output_4.txt || goto err

:: Тестируем случай когда искомый текст не найден
echo Test: search text not found
findText.exe input_5.txt test > %OUT% || goto err
fc %OUT% output_5.txt || goto err

:: Тестируем случай отсутствия второго аргумента
echo Test: no second argument
findText.exe input_1.txt > %OUT% || goto err
fc %OUT% output_6.txt || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1