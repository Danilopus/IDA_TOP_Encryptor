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
		static void Initialise(int argc, char* argv[])
		{
			Arguments* current_arguments = new Arguments(argc, argv);
			
			try
			{
				current_arguments->Are_Arguments_valid();
			}
			catch (int exc_num)
			{
				COUT_Help();
				std::exit(1);
			}
			

			
			//*
			std::cout << "There are " << argc << " arguments:\n";		
			for (int i{ 0 }; i < current_arguments->arguments_vec.size(); ++i)
				std::cout << current_arguments->arguments_vec[i] << "\n";
			//*/



			/// Передача управления в главную функцию класса
			Control(current_arguments);



		}
		static void Control(const Arguments* current_arguments)
		{
			
			
			CodeCore::Crypto_Interface* crypto_obj_ptr = nullptr;
			switch (current_arguments->_algo_type)
			{
			case Arguments::_AlgoType::help:
				COUT_Help();
				break;
			case Arguments::_AlgoType::CEASER:

				crypto_obj_ptr = new CodeCore::Ceaser_Cryptor();

				break;
			case Arguments::_AlgoType::DES:
				crypto_obj_ptr = new CodeCore::DES_Cryptor();
				break;
			}


			switch (current_arguments->_action_type)
			{
			case Arguments::_ActionType::encrypt: 
				{
					FileCore::Encrypt_Stream encrypt_stream_maker(current_arguments->_path_to_read, current_arguments->_new_name);
					bool status = crypto_obj_ptr->Encrypt(encrypt_stream_maker.Get_read_stream(), encrypt_stream_maker.Get_write_stream());
					std::cout << (status ? "\nEncryption succesfull\n" : "\nEncryption failed\n");
					break;
				}
			case Arguments::_ActionType::decrypt: 
				{
					FileCore::Decrypt_Stream decrypt_stream_maker(current_arguments->_path_to_read, current_arguments->_new_name);
					bool status = crypto_obj_ptr->Decrypt(decrypt_stream_maker.Get_read_stream(), decrypt_stream_maker.Get_write_stream());
					std::cout << (status ? "\nDecryption succesfull\n" : "\nDecryption failed\n");
					break;
				}
			}




			// не хочет удалять объект, вроде я его создал - мне и удалять??? 
			// Exception thrown at 0x00007FFA6AEAB1ED (ucrtbased.dll) in IDA_TOP_Encryptor.exe: 0xC0000005: Access violation reading location 0x0000000100000000.
			// A breakpoint instruction (__debugbreak() statement or a similar call) was executed in IDA_TOP_Encryptor.exe.
			//delete crypto_obj_ptr;
		}
		
		static void COUT_Help()
		{
			std::cout << "\n\n///Program keys\n\n";

			std::cout << std::endl << "--- HELP";
			std::cout << std::endl << "/? -";
			std::cout << std::endl << "/h";
			std::cout << std::endl << "/help";
			std::cout << std::endl << "/help?";

			std::cout << std::endl << "--- Encryption";
			std::cout << std::endl << "/action=1:encryption";
			std::cout << std::endl << "+ /path=\"filename.txt\"";
			std::cout << std::endl << "+ /password=\"password\"";
			std::cout << std::endl << "+ [/algo=(1:CEASER,2:DES, 3:AES)] // default - CEASER";
			std::cout << std::endl << "+ [/name=\"new_filename\"] //default name=\"#filename_encrypt_#algorithm\"]";

			std::cout << std::endl << "--- Decryption";
			std::cout << std::endl << "/action=2:decryption";
			std::cout << std::endl << "+ /path=\"filename.txt\"";
			std::cout << std::endl << "+ /password=\"password\"";
			std::cout << std::endl << "+ [/name=\"new_file_name\"] // default name=\"#filename_decrypt_#algorithm\"]";
		}

	};

}

