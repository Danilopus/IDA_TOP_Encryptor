#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "CodeCore.h"
#include "FileCore.h"
#include "Arguments.h"

/// namespace InputHandle
/**
Пространство имен InputHandle содержит классы для обработки комманд, поступающих через аргументы заппуска (командной строки)
Также содержит класс Controller - выполненный по шаблону Контроллер - который исходя из поступивших аргументов вызывает
методы классов пространства имен CodeCore - для кодирования, и namespace FileCore - для работы с файловой системой
*/
namespace InputHandle
{	
	///Управляет работой приложения
	/**
	Выполнен по шаблону Контроллер - содержит основную логику управления работой приложения
	*/
	class Controller
	{
	public:
		static void Initialise(int argc, char* argv[]);
		static void Control(const Arguments* current_arguments);		
		static void COUT_Help();
		// В дальнейшем как-то автоматизировать функцию выбора криптообъекта для простого подключения новых классов-шифраторов
		static CodeCore::Crypto_Interface* _algo_type_handler(const Arguments::_AlgoType& _type);
		static bool Do_action(const Arguments* current_arguments, CodeCore::Crypto_Interface* crypto_obj_ptr);

	};

}

