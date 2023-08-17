#include <iostream>


//temporary including
#include <conio.h>
#include "Controller.h"



/// Course project ENCRYPTOR
/** 
* explanatory note
* 
* *** Изменения 18.08.2023:
* - добавлены короткие версии всех параметров (для этого даже изменено имя одного из параметров path->file)
* - добавлен параметр "режим работы" сохранения/удаления оригинального файла при шифрвании (дешифрации это не коснулось)
* - также теперь для любителей полного синтаксиса есть возможность /action=encryption 
* 
* 
*** Актуальное состояние 15.08.2023:
* - компилируется
* - работает с параметрами командной строки как отражено в /help
* - работает с одним алгоритмом: CEASER
* - читает и пишет файлы
* PS: практически полная функциональность в рамках одного алгоритма
* 
* 
*** Интерфейс пользователя:
* Программа шифратор файлов работает через параметры коммандной строки (/? - список комманд)
* 
* 
*** Логика работы:
* 1. Введенные аргументы коммандной строки проходят парсинг и первичный анализ в классе InputHandle::Arguments
* 2. Управляющий класс InputHandle::Controller исходя из аргументов:
*   2.1 создает необходимый крипто-объект: (криптор/декриптор) определенного шифра
*   2.2 запрашивает файловые потоки для ввода вывода через классы пространства FileCore
*   2.3 запускает метод шифрования/дешифрования созданный крипто-объект с передачей всех нужных ресурсов (потоки) и параметров
* 3. Как только объект классов из FileCore владеющий потоками выходит из зоны видимости - 
*    записываемая информация гарантировано попадает в файл (через закрытие потоков в деструкторе)
* 
* PS: программа имеет некоторую устойчивость к внешним раздражителям: неполные/кривые параметры, отсутствие нужных файлов/прав на старте
* 
*** TODO:
* 
* 1. Проработать мехнизм подключения новых алгоритмов шифорвания:
*   1.1 В первую очередь механизм удобного подключения к программе:
            1.1.1 Динамически изменяемый список доступных алгоритмов при выводе экрана /help
            1.1.2 Динамически изменяемый список доступных алгоритмов при определении, поиске и создании крипто-объектов в функции InputHandle::Controller::_algo_type_handler
            1.1.3 Как-то хранить в динамическом контейнере информацию 
*   1.2 Во вторую очередь доработать базовый class Crypto_Interface для более-менее универсальной работы с разными шифроалгоритмами (передача паролей, ключей и.т.п)
*       Чтобы вызов CodeCore::Any_Cryptor::Encrypt() через указатель на интерфейс был возможен для большинства предполагаемых новых классов-cryptor
*
* 2. Проработать защиты и обходчики для всяких исключительных ситуаций
* 
* 
*/


///Theory block
/**
Principles to  [try to implement] / [keep in mind]:

1. KISS = keep it short and simple | DRY = don't repeat yourself

2. SOLID

Single responsibility principle (принцип единственной ответственности);
Open-closed principle (принцип открытости/закрытости);
Liskov substitution principle (принцип подстановки Лисков);
Interface segregation principle (принцип разделения интерфейса);
Dependency inversion principle (принцип инверсии зависимостей).

3. GRASP (General Responsibility Assignment Software Patterns) — шаблоны проектирования, 
используемые для решения общих задач по назначению обязанностей классам и объектам.

GRASP состоит из 5 основных и 4 дополнительных шаблонов.

Основные шаблоны:
Information Expert
Creator
Controller
Low Coupling
High Cohesion

Дополнительные шаблоны:
Pure Fabrication
Indirection
Polymorphism
Protected Variations


*паттерн "Фасад"

*/

///Program keys
/**

see  Controller.cpp -> InputHandle::Controller::COUT_Help()

*/

///Actual test arguments:
/**

Project->Properties->Configuration Properties->Debugging->Command Arguments:

---Encrypt
/action=1 /file="sample.txt" /password="123" /method=1 /name="sample_crypt.txt"
/a=1 /f="sample.txt" /p="123" /m=1 /n="sample_crypt.txt" /r=1


/action=1 /file="sample.txt" /password="123"

/file=1 /p=123


---Decrypt
/action=2 /file="sample_crypt.txt" /password="123" /method=1
/a=2 /f="sample_crypt.txt" /p="123" /m=1


/file=1 /p=123


*/

/// Слои
/**

1. namespace InputHandle - обработка входящих аргументов, вызов CodeCore с сформированным набором аргументов
2. namespace CodeCore - шифрование выбранным методом входящего потока, возврат шифрованного потока 
3. namespace FileCore - работа с файловой системой чтение/запись/создание файлов

*/


int main(int argc, char* argv[])
{        
    InputHandle::Controller::Initialise(argc, argv);
    _getch();
return 0;
}  