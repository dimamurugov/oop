@echo off

set OUT="%TEMP%\out.txt"

echo Test: Validate matrix
..\cmake-build-debug\task_3.exe matrix.txt > %OUT%
fc %OUT% "output_1.txt" || goto err

echo Test: Not validate matrix
..\cmake-build-debug\task_3.exe input_2.txt > %OUT%
fc %OUT% "output_2.txt" || goto err

echo Test: The determinant is zero!
..\cmake-build-debug\task_3.exe input_3.txt > %OUT%
fc %OUT% "output_3.txt" || goto err

echo Test: 4 x 4 matrix!
..\cmake-build-debug\task_3.exe input_4.txt > %OUT%
fc %OUT% "output_4.txt" || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1