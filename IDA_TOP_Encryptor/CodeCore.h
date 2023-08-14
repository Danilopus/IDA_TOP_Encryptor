#pragma once
#include <iostream>
#include <fstream>

namespace CodeCore
{
	class Crypto_Interface
	{
	public:
		virtual bool Encrypt(std::ifstream& read_stream, std::ofstream& write_stream) = 0;
		virtual bool Decrypt(std::ifstream& read_stream, std::ofstream& write_stream) = 0;
	};

	class Ceaser_Cryptor : virtual public Crypto_Interface
	{
	public:

		bool Encrypt(std::ifstream& read_stream, std::ofstream& write_stream) override
		{
			std::string tmp_str;
			while (!read_stream.eof())
			{			
				char ch = EncryptionEngine(read_stream.get());
				if (ch != 2) tmp_str += ch;
				//write_stream << CryptoEngine(read_stream.get());
			}
			write_stream << tmp_str;
			//write_stream << tmp_str.c_str();
			return true;
		}

		bool Decrypt(std::ifstream& read_stream, std::ofstream& write_stream) override
		{
			std::string tmp_str;
			while (read_stream.eof() != 1)
			{
				char ch = DecryptionEngine(read_stream.get());
				if (ch != -4) tmp_str += ch;				
			}
			write_stream << tmp_str;
			//write_stream << tmp_str.c_str();
			return true;
		}


		/// Криптографический движок этого класса
		/**
		Возращает символ с кодом +3 от входящего, если это не пробел
		*/
		char EncryptionEngine(char ch)
		{
			return ch != 32 ? ch + 3 : ch;
		}
		char DecryptionEngine(char ch)
		{
			return ch != 32 ? ch - 3 : ch;
		}
	};

	class DES_Cryptor : virtual public Crypto_Interface
	{
		bool Decrypt(std::ifstream& read_stream, std::ofstream& write_stream) override { return false; }
		
			bool Encrypt(std::ifstream& read_stream, std::ofstream& write_stream) override
		{
			return false;
		}		

	};



}
