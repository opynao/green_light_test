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

## Подходы к решению задачи

1. **async с future**
   
В этом подходе можно асинхронно запускать дочерний поток с помощью std::async, который возвращает std::future. 

    `auto futureResult = std::async(std::launch::async, countAndSortTags, htmlContent);
    printTagCounts(futureResult.get());`

3. **thread с promise**
   
В этом случае создается поток с помощью std::thread, который использует std::promise для передачи результатов выполнения обратно в родительский поток. 

    `std::promise<tagsCount_t> resultPromise;
    std::future<tagsCount_t> resultFuture = resultPromise.get_future();

    std::thread childThread(countAndSortTags, htmlContent, std::move(resultPromise));

    const tagsCount_t tagCounts = resultFuture.get();
    childThread.join();
    printTagCounts(tagCounts);`

Я написала обе реализации. thread с promise подходит, если нужна гибкость и полный контроль над потоками. async с future обеспечивает простоту и легкость в использовании.

    
