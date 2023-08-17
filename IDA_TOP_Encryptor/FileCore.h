#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>

namespace FileCore
{	
	
	class Encrypt_Stream
	{
		std::string _default_name = "default_sample.txt";
		std::ofstream* ofstream_ptr = nullptr;
		std::ifstream* ifstream_ptr = nullptr;
		std::string _read_path;		
		bool _DEFAULT_NAMES_FLAG_ = false;
		bool _OVERWRITE_FLAG_ = true;

	public:
		//Encrypt_Stream(std::string path, std::string new_name)
		Encrypt_Stream(const std::string path, const std::string new_name, bool _overwright_regime);
		~Encrypt_Stream();
		std::ofstream& Get_write_stream() { return *ofstream_ptr; }		
		std::ofstream& Get_write_stream(std::string new_name);
		std::ifstream& Get_read_stream() { return *ifstream_ptr; }
		std::ifstream& Get_read_stream(std::string path_to_read);
		bool is_overwrite_mode();
		void delete_origin();
	};

	class Decrypt_Stream
	{
		std::ofstream* ofstream_ptr = nullptr;
		std::ifstream* ifstream_ptr = nullptr;;
	public:
		~Decrypt_Stream();
		Decrypt_Stream(const std::string path_to_read, const std::string new_name);
		std::ofstream& Get_write_stream() { return *ofstream_ptr; }		
		//Нужна защита на случай недопустимого имени
		std::ofstream& Get_write_stream(std::string new_name);
		std::ifstream& Get_read_stream() { return *ifstream_ptr; }
		std::ifstream& Get_read_stream(std::string path_to_read);
	};


}