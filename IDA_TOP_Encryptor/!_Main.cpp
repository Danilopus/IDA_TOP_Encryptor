#include <iostream>


//temporary including
#include <conio.h>
#include "Controller.h"



/// Course project ENCRYPTOR
/** 
* explanatory note
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

/? - вызов помощи
/h
/help
/help?


/action=encryption
+ /path="filename.ext"
+ /password="new_password"
+ [/algo=(1|CEASER,2|DES, 3|AES)] // default - CEASER
+ [/name="new_file_name"] //default - overwrite existing file


/action=decryption
+ /path="filename.ext"
+ /password="new_password"
+ [/name="new_file_name"] //otherwise - overwrite existing file


*/

///Actual test arguments:
/**

Project->Properties->Configuration Properties->Debugging->Command Arguments:

---Encrypt
/action=1 /path="sample.txt" /password="123" /algo=1 /name="sample_crypt.txt"
/action=1 /path="sample.txt" /password="123"

/path=1 /password=123


---Decrypt
/action=2 /path="sample_crypt.txt" /password="123" /algo=1


/path=1 /password=123


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