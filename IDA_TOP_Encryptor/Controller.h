#pragma once
#include <iostream>
#include <vector>



namespace InputHandle
{


	class Arguments
	{
		std::string _path;
		std::string _password;
		enum class _CryptType { CEASER, DES, AES } _crypt_type;
		std::string _new_name;
	public:
		std::vector <std::string> arguments_vec;
		Arguments(int argc, char* argv[])
		{
			for (int count{ 0 }; count < argc; ++count)
			{
				arguments_vec.push_back(argv[count]);
			}
			if (arguments_vec.size()) _path = arguments_vec[0];

		}

	};

	class Controller
	{
	public:
		static void Initialise(int argc, char* argv[])
		{
			Arguments* current_arguments = new Arguments(argc, argv);
			
						
			std::cout << "There are " << argc << " arguments:\n";

			// Перебираем все аргументы и
			// выводим номер и значение каждого из них
			
			for (int i{ 0 }; i < current_arguments->arguments_vec.size(); ++i)
				std::cout << current_arguments->arguments_vec[i] << "\n";

			


			Control(current_arguments);





	/*		for (int count{ 0 }; count < argc; ++count)
			{
				std::cout << count << ' ' << argv[count] << '\n';
			}*/
		}
		static void Control(Arguments* current_arguments)
		{

		}
	};


}

