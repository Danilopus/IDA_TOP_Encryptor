#include "Arguments.h"
#include <algorithm>

InputHandle::Arguments::Arguments(int argc, char* argv[])
{
	for (int count{ 0 }; count < argc; ++count)
	{
		arguments_vec.push_back(argv[count]);
	}
	if (arguments_vec.size()) _application_path = arguments_vec[0];
	else return;

	int just_int_parametr{0};
	int result = Initialise("/action", just_int_parametr);
	if (result == -1)
		result = Initialise("/a", just_int_parametr);
	_action_type = static_cast<Arguments::_ActionType>(--result);
	
	_path_to_read = Initialise("/file");
	if (_path_to_read=="")	_path_to_read = Initialise("/f");

	_password = Initialise("/password");
	if (_password == "")	_password = Initialise("/p");

	
	result = Initialise("/method", just_int_parametr);
	if (result == -1)
		result = Initialise("/m", just_int_parametr);
	_algo_type = static_cast<Arguments::_AlgoType>(result);

	_new_name = Initialise("/name");
	if (_new_name == "")	_new_name = Initialise("/n");

	result = Initialise("/regime", just_int_parametr);
	if (result == -1)
		result = Initialise("/r", just_int_parametr);
	_overwright_regime = result;

}

int InputHandle::Arguments::Initialise(std::string str, int)
{
	for (int i = 1; i < arguments_vec.size(); ++i)
	{
		if (arguments_vec[i].find(str) != std::string::npos)
		{
			// Ищем в строке знак =
			int substr_begin = arguments_vec[i].find("=", (arguments_vec[i].find(str) + str.size()));
			// И все после этого знака (для этого инкеремент) читаем в возвращаемую строку			
			std::string result = arguments_vec[i].substr(++substr_begin);
			if (result == "") return -1;
			if(has_only_digits(result)) return (std::stoi(result) - 1);			
			to_lower(result);
			if (result == "encryption") return 1;
			if (result == "decryption") return 2;

	

			
		}
	}
	return -1;
}
bool InputHandle::Arguments::has_only_digits(const std::string& s)
{
	return (s.find_first_not_of("0123456789") == std::string::npos);
}
void InputHandle::Arguments::to_lower(std::string& temp_str)
{
	std::for_each(
		temp_str.begin(),
		temp_str.end(),
		[](char& c) {
			c = ::tolower(c);
		});
}

std::string InputHandle::Arguments::Initialise(const std::string& str)
{
	for (int i = 1; i < arguments_vec.size(); ++i)
	{
		if (arguments_vec[i].find(str) != std::string::npos)
		{
			// Ищем в строке знак =
			size_t substr_begin = arguments_vec[i].find("=", (arguments_vec[i].find(str) + str.size()));		
			// И все после этого знака (для этого инкеремент) читаем в возвращаемую строку
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
		std::cout << "\nObligatory /file parameter is missed\n";
		throw 1;
	}
	if (_password == "")
	{
		std::cout << "\nObligatory /password parameter is missed\n";
		throw 1;
	}
	// Если новое имя пустое - задаем значение по умолчанию
	if (_new_name == "")
		_new_name = Name_by_default();
	
}
	std::string InputHandle::Arguments::Name_by_default()
	{
		std::string _ActionType_AlgoType;
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
		// отладочная версия генерации имени для удобства открытия блокнотом
		return (_path_to_read + _ActionType_AlgoType + ".txt");
		// основная версия генерации имени
		//_new_name = _path_to_read + _ActionType_AlgoType; 
	}

