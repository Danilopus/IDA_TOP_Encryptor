#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace InputHandle
{

	/// Преобразует аргументы
		/**
		Преобразует входящие аргументы из строк в удобные представления для дальнейшего анализа
		*/
	class Arguments
	{
	public:
		enum class _ActionType { encrypt, decrypt } _action_type = _ActionType::encrypt;
		std::string _application_path;
		std::string _path_to_read;
		std::string _password;
		enum class _AlgoType {  CEASER, DES, AES, help	} _algo_type = _AlgoType::CEASER;
		std::string _new_name;
		//public:
		std::vector <std::string> arguments_vec;
		Arguments(int argc, char* argv[]);
		int Initialise(std::string str, int);
		std::string Initialise(const std::string& str);
		std::string Initialise(std::string& str);
		bool Are_Arguments_valid();
	};

}