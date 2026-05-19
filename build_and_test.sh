#!/bin/bash

echo "=== Building and Testing Monster Project ==="

# Очистка
rm -rf build

# Сборка
mkdir build
cd build
cmake .. -DBUILD_TESTS=ON
make

# Запуск теста
echo ""
echo "=== Running Tests ==="
./monster_tests

# Проверка результата
if [ $? -eq 0 ]; then
    echo ""
    echo "SUCCESS: Build and tests passed!"
else
    echo ""
    echo "FAILED: Tests failed!"
    exit 1
fi

# Запуск программы
echo ""
echo "=== Running Program ==="
./monster_demo
