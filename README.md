# pract_sem_5
Делаю учебную практику в 5 семестре

## Requires
1. C++ 20 or higher
2. cmake 3.27 or higher (pip install cmake)
3. conan 1.60 or higher (pip install conan)
4. g++ 8 or higher


## IDE build
1. Определить CmakeLists.txt
2. Перейти в папку сборки
3. `conan install .. --build=missing`
4. Запустить сборку проекта в IDE

## Raw build
1. `mkdir build`
2. `cd build`
3. `conan install .. --build=missing`
4. `cmake -D CMAKE_BUILD_TYPE=Debug ..`, instead of {Debug} can be used {Release}
5. `cmake --build .`
