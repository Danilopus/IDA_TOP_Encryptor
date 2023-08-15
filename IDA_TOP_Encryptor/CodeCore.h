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

		bool Encrypt(std::ifstream& read_stream, std::ofstream& write_stream) override;

		bool Decrypt(std::ifstream& read_stream, std::ofstream& write_stream) override;

		/// Криптографический движок этого класса
		/**
		Возращает символ с кодом +3 от входящего, если это не пробел
		*/
		char EncryptionEngine(char ch);
		char DecryptionEngine(char ch);
	};

	/// Проект класса, пока просто пустышка
	class DES_Cryptor : virtual public Crypto_Interface
	{
		bool Decrypt(std::ifstream& read_stream, std::ofstream& write_stream) override { return false; }		
		bool Encrypt(std::ifstream& read_stream, std::ofstream& write_stream) override	{return false;}	
	};



}
