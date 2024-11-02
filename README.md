#  Подсчет html-тегов с потоковой обработкой

Этот проект представляет собой программу на C++, которая анализирует HTML-файл для подсчета и сортировки HTML-тегов с использованием многопоточности.

## Необходимые инструменты для сборки
-   **CMake**
-   **Компилятор C++**

## Сборка проекта и запуск
В корне есть index.html для теста программы.

    git clone git@github.com:opynao/green_light_test.git
    cd green_light_test
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ./tests/tests // запуск тестов
    ./src/green_light_project ../index.html // запуск программы
