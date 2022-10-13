#!/bin/bash
make re

echo TEST 1 - без аргументов
./ff

echo TEST 1 - много аргументов
./ff fff fff fff

echo "             Тесты с одним аргументом"

echo "             Тесты без специальных символов"
echo TEST 1 - "./ff "123.c" "
./ff "123.c"

echo TEST 2 - "./ff "123.cpp" "
./ff "123.cpp"

echo Спец символы отправляю в программу экранируя ковычками, чтобы shell не раскрыл их самостоятельно


echo "             Тесты с *"
echo TEST 1 - "./ff "*.c" "
./ff "*.c"

echo TEST 2 - "./ff "*.c*" "
./ff "*.c*"

echo TEST 3 - "./ff ".*" "
./ff ".*"

echo TEST 4 - "./ff ".g*" "
./ff ".g*"

echo TEST 5 - "./ff "*g*" "
./ff "*g*"

echo TEST 6 - "./ff "*file*" "
./ff "*file*"

echo TEST 7 - "./ff "*f*e*" "
./ff "*file*"

echo TEST 8 - "./ff  "*" "
./ff  "*"

echo TEST 9 - "./ff "*******f******e*******" "
./ff "*******f******e*******"

echo TEST 10 - "./ff "****"  | wc -l"
./ff "****"  | wc -l

echo TEST 11 - "./ff "*"  | wc -l"
./ff "*"  | wc -l

echo TEST 12 - "./ff "****"  >file1"
./ff "****"   >file1

echo TEST 13 - "./ff "*"  >file2"
./ff "*"   >file2

echo  - "diff file1 file2"
diff file1 file2



echo "             Тесты с экранированной *"
echo TEST 1 - "./ff "'*'.c*" "
./ff "'*'.c*"

echo TEST 2 - "./ff "*'*'.c*" "
./ff  "*'*'.c*"


echo "             Тесты с ?"
echo TEST 1 - "./ff "?.cpp" "
./ff "?.cpp"

echo TEST 2 - "./ff "?.c??" "
./ff "?.c??"

echo TEST 3 - "./ff "???.?" "
./ff "???.?"

echo TEST 3 - "./ff "?????" "
./ff "?????"

echo "             Тесты с экранированным ?"
echo TEST 1 - "./ff "1'?'.c??" "
./ff "1'?'.c??"

echo TEST 2 - "./ff "??'?'.c" "
./ff  "??'?'.c"

echo "             Тесты с * и ?"
echo TEST 1 - "./ff "*.c??" "
./ff "*.c??"

echo TEST 2 - "./ff "*?c" "
./ff "*?c"

echo TEST 3 - "./ff "*.???" "
./ff "*.???"

echo "             Тесты с двумя аргументами"

echo TEST 1 - "./ff "*.c" dir1"
./ff "*.c" dir1

echo TEST 2 - "./ff "*.c??" dir1"
./ff "*.c??" dir1

echo TEST 3 - "./ff ".*" dir1"
./ff ".*" dir1

echo TEST 4 - "./ff "*4*" dir1"
./ff  "*4*" dir1

echo TEST 5 - "./ff "?" dir1"
./ff "." dir1

echo "             Тесты с нерабочими кейсами"

echo TEST 1 - "./ff "*.cpp?""
./ff "*.cpp?"

echo TEST 2 - "./ff "*.c???" "
./ff "*.c???"

echo TEST 3 - "./ff "*file" dir1"
./ff "*file" dir1

echo TEST 4 - "./ff "*4?" dir1"
./ff  "*4?" dir1

echo TEST 5 - "./ff "*1*" "
./ff "*1*"

echo TEST 6 - "./ff "..*" dir1"
./ff "..*" dir1

echo TEST 5 - "./ff "*1*" dir1"
./ff "*1*" dir1

echo TEST 6 - "./ff "*..*" dir1"
./ff "*..*" dir1

echo TEST 7 - "./ff "*.." dir1"
./ff "*.." dir1

echo TEST 8 - "./ff "*." dir1"
./ff "*." dir1

echo TEST 9 - "./ff "*123*" dir1"
./ff "*123*" dir1