#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>

namespace FileCore
{	
	
	class Encrypt_Stream
	{
		std::ofstream* ofstream_ptr = nullptr;
		std::ifstream* ifstream_ptr = nullptr;
		bool _DEFAULT_NAMES_FLAG_ = false;
	public:
		//Encrypt_Stream(std::string path, std::string new_name)
		Encrypt_Stream(const std::string path, const std::string new_name);
		~Encrypt_Stream();
		std::ofstream& Get_write_stream() { return *ofstream_ptr; }		
		std::ofstream& Get_write_stream(std::string new_name);
		std::ifstream& Get_read_stream() { return *ifstream_ptr; }
		std::ifstream& Get_read_stream(std::string path_to_read);
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