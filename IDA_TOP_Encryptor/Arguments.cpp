#include "Arguments.h"

InputHandle::Arguments::Arguments(int argc, char* argv[])
{
	for (int count{ 0 }; count < argc; ++count)
	{
		arguments_vec.push_back(argv[count]);
	}
	if (arguments_vec.size()) _application_path = arguments_vec[0];
	else return;

	_action_type = static_cast<Arguments::_ActionType>(Initialise("/action", 1));
	_path_to_read = Initialise("/path");
	_password = Initialise("/password");
	_algo_type = static_cast<Arguments::_AlgoType>(Initialise("/algo", 1));
	_new_name = Initialise("/name");

	//Are_Arguments_valid();
}

int InputHandle::Arguments::Initialise(std::string str, int)
{
	for (int i = 1; i < arguments_vec.size(); ++i)
	{
		if (arguments_vec[i].find(str) != std::string::npos)
		{
			size_t substr_begin = arguments_vec[i].find("=", (arguments_vec[i].find(str) + str.size()));
			size_t substr_length = 1;
			str = arguments_vec[i].substr(++substr_begin, substr_length);
			//return std::stoi(arguments_vec[i].substr(substr_begin, substr_length));
			//return std::atoi(str.c_str());
			return str == "" ? 0 : (std::stoi(str) - 1);
		}
	}
	return 0;
}

std::string InputHandle::Arguments::Initialise(const std::string& str)
{
	for (int i = 1; i < arguments_vec.size(); ++i)
	{
		if (arguments_vec[i].find(str) != std::string::npos)
		{
			// Куда-то проподают кавычки из параметров командной строки
			//size_t substr_begin = arguments_vec[i].find("\"", (arguments_vec[i].find(str) + str.size()));
			size_t substr_begin = arguments_vec[i].find("=", (arguments_vec[i].find(str) + str.size()));
			//size_t substr_length = arguments_vec[i].rfind("\"");
			//return arguments_vec[i].substr(++substr_begin, substr_length);
			return arguments_vec[i].substr(++substr_begin);
		}
	}

	return "";
}

std::string InputHandle::Arguments::Initialise(std::string& str)

{
	for (int i = 1; i < arguments_vec.size(); ++i)
	{
		if (arguments_vec[i].find(str) != std::string::npos)
		{
			size_t substr_begin = arguments_vec[i].find("\"", (arguments_vec[i].find(str) + str.size()));
			size_t substr_length = arguments_vec[i].rfind("\"");
			return arguments_vec[i].substr(++substr_begin, substr_length);
		}
	}

	return "";
}

bool InputHandle::Arguments::Are_Arguments_valid()
{
	if (_path_to_read == "")
	{
		std::cout << "\nObligatory /path parameter is missed\n";
		throw 1;
	}
	if (_password == "")
	{
		std::cout << "\nObligatory /password parameter is missed\n";
		throw 1;
	}
	// Если новое имя пустое - задаем значение по умолчанию
	std::string _ActionType_AlgoType;
	if (_new_name == "")
	{
		switch (_algo_type)
		{
		case _AlgoType::CEASER: _ActionType_AlgoType = "CEASER"; break;
		case _AlgoType::DES: _ActionType_AlgoType = "DES"; break;
		case _AlgoType::AES: _ActionType_AlgoType = "AES"; break;
		}
		switch (_action_type)
		{
		case _ActionType::encrypt:
			_ActionType_AlgoType = _ActionType_AlgoType.insert(0, "_encrypt_");
			break;
		case _ActionType::decrypt:
			_ActionType_AlgoType = _ActionType_AlgoType.insert(0, "_decrypt_");
			break;
		}
		//_new_name = _path_to_read.substr(0, _path_to_read.find(".")) + _ActionType_AlgoType + ".txt";
		//int extension_offset = (_path_to_read.rfind(".") == std::string::npos) ? 0 : _path_to_read.rfind(".");
		//std::string extension = extension_offset ? _path_to_read.substr(extension_offset): "";
		//_new_name = _path_to_read.substr(0, _path_to_read.rfind(".")) + _ActionType_AlgoType + extension;
		_new_name = _path_to_read + _ActionType_AlgoType + ".txt"; // отладочная версия генерации имени для удобства открытия блокнотом
		//_new_name = _path_to_read + _ActionType_AlgoType; // основная версия генерации имени

	}
}
