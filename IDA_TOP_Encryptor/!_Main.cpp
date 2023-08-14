#include <iostream>


//temporary including
#include <conio.h>
#include "Controller.h"



/// Course project ENCRYPTOR

/**
\file
Principles to implement:

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

Properties->Configuration Properties->Debugging->Command Arguments:


/action=1 /path="sample.txt" /password="123" /algo=1 /name="sample_crypt.txt"

/action=2 /path="sample_crypt.txt" /password="123" /algo=1


/help

/?

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
    
    //InputHandle::Arguments::Read();    	

    _getch();
return 0;
}