#include <iostream>


//temporary including
#include <conio.h>
#include "Controller.h"



// Course project ENCRYPTOR

//Principles to implement:

/*
1. «keep it short and simple»

2. SOLID

Single responsibility principle (принцип единственной ответственности);
Open-closed principle (принцип открытости/закрытости);
Liskov substitution principle (принцип подстановки Лисков);
Interface segregation principle (принцип разделения интерфейса);
Dependency inversion principle (принцип инверсии зависимостей).

3. GRASP

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

//Ключи программы

/*

/? - вызов помощи

/action=decryption
+ /path="filename.ext" 
+ /password="new_password"
+ [/name="new_file_name"] //otherwise - overwrite existing file

/action=encryption
+ /path="filename.ext"
+ /password="new_password"
+ [/algo=(1|CEASER,2|DES, 3|AES)] // default - CEASER
+ [/name="new_file_name"] //default - overwrite existing file


*/

//Actual arguments:

/*

Properties->Configuration Properties->Debugging->Command Arguments:
/encryption /path = sample.txt /password = 123 /algo = DES /name = sample_crypt.txt

*/

// Слои

/*

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