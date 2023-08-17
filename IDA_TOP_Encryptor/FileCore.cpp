#include "FileCore.h"

FileCore::Encrypt_Stream::Encrypt_Stream(const std::string path, const std::string new_name, bool _overwright_regime): _OVERWRITE_FLAG_(_overwright_regime)
{
	ifstream_ptr = &(Get_read_stream(path));
	ofstream_ptr = &(Get_write_stream(new_name));
	_read_path = path;
}

FileCore::Encrypt_Stream::~Encrypt_Stream()
{
	if (ofstream_ptr->is_open()) ofstream_ptr->close();
	if (ifstream_ptr->is_open()) ifstream_ptr->close();
}

std::ofstream& FileCore::Encrypt_Stream::Get_write_stream(std::string new_name)
{
	if (_DEFAULT_NAMES_FLAG_)
	{
		new_name = "default_sample.txt_crypt.txt";
	}
	std::ofstream& ostream_obj = *new std::ofstream(new_name, std::ios::out);
	if (ostream_obj.is_open())
		return ostream_obj;
	//return nullptr;
}

std::ifstream& FileCore::Encrypt_Stream::Get_read_stream(std::string path_to_read)
{
	std::ifstream& istream_obj = *new std::ifstream(path_to_read, std::ios::in);
	if (istream_obj.is_open())
		return istream_obj;
	else
	{
		std::ofstream test_file_stream(_default_name);
		if (test_file_stream.is_open())
			test_file_stream << "Defualt generated test file with test text, just because cannot open " << path_to_read;
		test_file_stream.close();
		std::cout << "\nCouldn't open " << path_to_read << " - default generated\n";
		_DEFAULT_NAMES_FLAG_ = true;
	}
	return Get_read_stream(_default_name);
}

bool FileCore::Encrypt_Stream::is_overwrite_mode()
{
	return _OVERWRITE_FLAG_;
}

void FileCore::Encrypt_Stream::delete_origin()
{
	if (ifstream_ptr->is_open()) ifstream_ptr->close();
	if (_DEFAULT_NAMES_FLAG_) std::remove(_default_name.c_str());
	else std::remove(_read_path.c_str());
}

FileCore::Decrypt_Stream::~Decrypt_Stream()
{
	if (ofstream_ptr->is_open()) ofstream_ptr->close();
	if (ifstream_ptr->is_open()) ifstream_ptr->close();
}

FileCore::Decrypt_Stream::Decrypt_Stream(const std::string path_to_read, const std::string new_name)
{
	try
	{
		ifstream_ptr = &(Get_read_stream(path_to_read));
		ofstream_ptr = &(Get_write_stream(new_name));
	}
	catch (int exc_code)
	{
		switch (exc_code)
		{
		case 1:
			std::cout << "\nCouldn't create " << new_name;
			_getch();
			std::exit(1);
			break;
		case 2:
			std::cout << "\nCouldn't open " << path_to_read;
			_getch();
			std::exit(1);
			break;
		}
	}
}

std::ofstream& FileCore::Decrypt_Stream::Get_write_stream(std::string new_name)
{
	std::ofstream& ostream_obj = *new std::ofstream(new_name, std::ios::out);
	if (ostream_obj.is_open())
		return ostream_obj;
	else throw 1;
}

std::ifstream& FileCore::Decrypt_Stream::Get_read_stream(std::string path_to_read)
{
	std::ifstream& istream_obj = *new std::ifstream(path_to_read, std::ios::in);
	if (istream_obj.is_open())
		return istream_obj;
	else throw 2;
	//return Get_read_stream("");
}
