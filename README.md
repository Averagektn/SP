# System Programming
---
## Lab №1:
  * Studying event-driven architecture of windows applications, message handling mechanism, window drawing mechanism.
    - Develop a program that allows you to move a sprite using keyboard and mouse inside the working area of the window. 
    - Ensure the operation of the mouse wheel. 
    - Make the sprite move with a bounce from the window borders. 
    - Use hotkeys. 
    - Use keyboard shortcuts using acceleration tables.
  * Изучение событийной архитектуры windows приложений, механизма обработки сообщений, механизма прорисовки окна.
    - Разработать программу, позволяющую передвигать спрайт с помощью клавиатуры и мыши внутри рабочей области окна. 
    - Обеспечить работу колесика мыши. 
    - Придать спрайту движение с отскоком от границ окна. 
    - Использовать горячие клавиши. 
    - Использовать сочетание клавиш с использованием таблиц акселлерации.
---
## Lab №2:
  * Studying text output and fonts
    - Develop a program that inscribes a text table of n rows by m columns into a window such that all columns of the table are evenly distributed across the width of the window, and the height of the table rows is adjusted to accommodate the text of each cell. 
    - When the window is resized, the table is recalculated and redrawn.
    - Inscribe text in a circle
  * Изучение вывода текста и шрифтов
    - Разработать программу, которая вписывает в окно текстовую таблицу n строк на m столбцов таким образом, что все столбцы таблицы равномерно распределяются по ширине окна, а высота строк таблицы подбирается таким образом, чтобы вместить текст каждой ячейки. 
    - При изменении размеров окна таблица пересчитывается и перерисовывается.
    - Вписать текст в окружность
---
## Lab №3:
  * Изучение создание и использование динамически загружаемых библиотек
    - Создать dll с функцией поиска по всей виртуальной памяти заданной строки и заменой ее на другую
    - Разработать программу, которая выполняет статический импорт dll и вызывает ее функцию
    - Разработать программу, которая выполняет динамический импорт и вызов функции
    - Разработать программу, которая внедряет dll в заданный процесс и осуществляет ее вызов там
  * Explore the creation and use of dynamically loaded libraries
    - Create a dll with a function that searches all virtual memory for a given string and replaces it with another string
    - Develop a program that performs static import of a dll and calls its function
    - Develop a program that performs dynamic import and function call
    - Develop a program that injects a dll into a given process and calls it there
---
## Lab №4:
  * Изучение реестра
    - Разработать программу создания и открытия ключа
    - Чтение флагов, составляющих маску ключа
    - Закрытие ключа
    - Сохранение изменений
    - Добавление данных ключу 
    - Поиск ключа
    - Дополнительно: отслеживание изменений реестра
  * Register exploration
    - Develop a program to create and open a key
    - Read the flags that make up the key mask
    - Closing the key
    - Saving changes
    - Adding data to the key 
    - Searching for the key
    - Optional: tracking registry changes
---
## Lab №5
  * Изучение создание и использование потоков и механизмов синхронизации
    - Разработать очередь заданий в к-ой несколько потоков могут вставлять эл-ты атомарно
    - Разработать обработчик этой очереди, к-ый извлекает из нее задания и раздаёт заданному кол-ву потоков
    - Разработать программу к-ая использует очередь заданий и обработчик очереди для сортировки строк в тхт файле: входной поток читает файл в память, нарезает его на части и создаёт несколько заданий на сортировку по числу сортирующих потоков, входной поток помещает их в очередь заданий
    - Сортирующие потоки извлекают задание, сортируют свои части файла, отдают результаты выходному потоку. Выход ждёт все сортирующие части и мержит их методом сортирующего слияния.
  * Study the creation and use of threads and synchronization mechanisms
    - Develop a job queue in which several threads can insert items atomically.
    - Develop a handler for this queue that retrieves jobs from it and distributes them to a given number of threads.
    - Develop a program that uses a job queue and a queue handler to sort lines in a txt file: the input thread reads the file into memory, slices it into parts and creates several sorting jobs according to the number of sorting threads, the input thread places them in the job queue.
    - Sorting threads retrieve the job, sort their parts of the file, give the results to the output thread. The output waits for all sorting parts and merges them using the sort merge method.
---
## Additional
  * Создать многопоточное приложение, которое формирует картинку как баланс серого на исходной
  * Create a multithreaded application that generates a picture as a gray balance on the original
