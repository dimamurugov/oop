@echo off

set OUT="%TEMP%\out.txt"

echo Test: number 6
task_2.exe 6 > %OUT%
fc %OUT% "./tests/output_1.txt" || goto err

echo Test: number -19
task_2.exe -19 > %OUT%
fc %OUT% "./tests/output_2.txt" || goto err

echo Test: number 600
task_2.exe 600 > %OUT%
fc %OUT% "./tests/output_4.txt" || goto err

echo Test: empty param
task_2.exe > %OUT%
fc %OUT% "./tests/output_5.txt" || goto err

echo Test: 0
task_2.exe 0 > %OUT%
fc %OUT% "./tests/output_7.txt" || goto err

echo Test: 255
task_2.exe 255 > %OUT%
fc %OUT% "./tests/output_8.txt" || goto err

echo Test: 256
task_2.exe 256 > %OUT%
fc %OUT% "./tests/output_9.txt" || goto err

echo All tests passed
exit /B 0

:err
echo Program testing failed
exit /B 1