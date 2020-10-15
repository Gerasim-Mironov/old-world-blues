#pragma once
#include<iostream>
#include<string>
#include<queue>
#include<fstream>



class To_DoNode
{
private:
	std::string title;
	std::string tag;
	std::string desc;
	std::string date;

	std::string cherry;


	std::string getFilePath()
	{
		std::string path;
		path += title;
		path += ".txt";

		return path;
	}
public:
	To_DoNode()
	{
		title = "";
		tag = "";
		desc = "";
		date = "";

		cherry = "";
	}
	To_DoNode(std::string title, std::string type, std::string desc, std::string date)
	{
		this->title = title;
		this->tag = type;
		this->desc = desc;
		this->date = date;

		cherry = getFilePath();
	}

	bool setNode(std::string title, std::string type, std::string desc, std::string date)noexcept
	{
		this->title = title;
		this->tag = type;
		this->desc = desc;
		this->date = date;

		cherry = getFilePath();

		return true;
	}

	void saveNode()
	{
		std::ofstream os("fileRoutes.txt", std::ios_base::app);
		os << cherry << "\n";
		os.close();

		std::ofstream osw(cherry);
		osw << title << " (on run)\n";
		osw << tag << "\n";
		osw << "finish until: " << date << "\n";
		osw << desc << "\n";

		osw.close();
	}
	void beatIt()
	{
		std::ofstream osw(cherry, std::ios_base::app);
		osw << title <<"       (finished)                                      ";
		osw.close();
	}
	bool displayNode()noexcept
	{
		std::ifstream is(cherry);
		while (!is.eof())
		{
			std::string data = "";
			std::getline(is, data);
			std::cout << data;
		}

		return true;
	}
};

class To_DoList
{
private:
	static To_DoList* instance;
	std::queue<To_DoNode> tasks;

	To_DoList() {}
	To_DoList(const To_DoList*) = delete;

	To_DoList& operator=(const To_DoList*) = delete;

	~To_DoList() {}
public:
	static To_DoList* getInstance()
	{
		if (To_DoList::instance == nullptr)
			To_DoList::instance = new To_DoList();
		else
			return To_DoList::instance;
	}
	static void deleteInstance()
	{
		if (To_DoList::instance != nullptr)
		{
			delete To_DoList::instance;
			To_DoList::instance = nullptr;
		}
	}
};