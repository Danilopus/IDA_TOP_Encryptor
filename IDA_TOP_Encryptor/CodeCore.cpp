#include "CodeCore.h"

bool CodeCore::Ceaser_Cryptor::Encrypt(std::ifstream& read_stream, std::ofstream& write_stream)
{
	std::string tmp_str;
	while (!read_stream.eof())
	{
		char ch = EncryptionEngine(read_stream.get());
		// !read_stream.eof() - срабатывает не так, как я ожидаю и цикл заходит еще на итерацию в конце файла и получает get() = -1
		if (ch != 2) tmp_str += ch;
		// write_stream << CryptoEngine(read_stream.get());
	}
	write_stream << tmp_str;
	//write_stream << tmp_str.c_str();
	return true;
}

bool CodeCore::Ceaser_Cryptor::Decrypt(std::ifstream& read_stream, std::ofstream& write_stream)
{
	std::string tmp_str;
	while (read_stream.eof() != 1)
	{
		char ch = DecryptionEngine(read_stream.get());
		// !read_stream.eof() - срабатывает не так, как я ожидаю и цикл заходит еще на итерацию в конце файла и получает get() = -1
		if (ch != -4) tmp_str += ch;
	}
	write_stream << tmp_str;
	//write_stream << tmp_str.c_str();
	return true;
}

char CodeCore::Ceaser_Cryptor::EncryptionEngine(char ch)
{
	return ch != 32 ? ch + 3 : ch;
}

char CodeCore::Ceaser_Cryptor::DecryptionEngine(char ch)
{
	return ch != 32 ? ch - 3 : ch;
}
