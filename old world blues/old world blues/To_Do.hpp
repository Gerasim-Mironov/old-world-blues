#pragma once
#include<iostream>
#include<string>
#include<list>
#include<fstream>

typedef std::string Msg;


class To_DoNode
{
private:
	std::string title;
	std::string tag;
	Msg desc;
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
	To_DoNode(std::string title, std::string type, Msg desc, std::string date)
	{
		this->title = title;
		this->tag = type;
		this->desc = desc;
		this->date = date;

		cherry = getFilePath();
	}

	bool setNode(std::string title, std::string type, Msg desc, std::string date)noexcept
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
	void loadNode(std::string route)
	{
		std::ifstream is;
		is.open(route);

		int mtd = 0;
		Msg data = "";
		while (!is.eof())
		{ 
			data = "";

			std::getline(is, data);
			if (mtd == 0)
			{
				title = data;
			}
			else if (mtd == 1)
			{
				tag = data;
			}
			else if (mtd == 2)
			{
				date = data;
			}
			else
			{
				desc = data;
			}
		}
		is.close();
	}
	void beatIt()
	{
		std::ofstream osw(cherry, std::ios_base::app);
		osw << title <<"\0\0\0\0\0\0\0\(finished)\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
		osw.close();
	}
	bool displayNode()noexcept
	{
		std::ifstream is(cherry);
		while (!is.eof())
		{
			Msg data = "";
			std::getline(is, data);
			std::cout << data;
		}

		return true;
	}
	/*std::ostream operator <<(std::ostream os)
	{
		os << title << " (on run)\n";
		os << tag << "\n";
		os << "finish until: " << date << "\n";
		os << desc << "\n";

		return os;
	}*/

	std::string getTitle()
	{
		return title;
	}
	std::string getTag()
	{
		return tag;
	}
	std::string getDate()
	{
		return date;
	}
};

class To_DoList
{
private:
	static To_DoList* instance;
	To_DoNode* tasks;
	int mtd;

	To_DoList()
	{
		loadList();
		mainMenu();
	}
	void mainMenu()
	{
	    std::cout << "1-> показать все дела\n2-> создать дело\n3->закрыть дело\n4-> найти дело\n5-> уйти\n(не жмите Enter после нажати€ цифры)\n";
		char sym = _getch();
		switch (sym)
		{
		case '1':
		{
			for (int i = 0; i < mtd; i++)
			{
				tasks[i].displayNode();
			}
			system("pause");
		}break;
		case '2':
		{
			system("cls");
			std::cout << "название: ";
			std::string title = "";
			getline(std::cin, title);
			std::cout << "метки: ";
			std::string tag = "";
			getline(std::cin, tag);
			std::cout << "описание: ";
			Msg desc = "";
			getline(std::cin, desc);
			std::cout << "дата, до которой нужно сделать дело^:^ ";
			std::string date = "";
			getline(std::cin, date);

			To_DoNode nge(title, tag, desc, date);
			nge.saveNode();
			expandArray(tasks, nge);
			std::cout << "ок\n";
			_getch();
		}break;
		case '3':
		{
			Msg seekingFor = "";
			std::cout << "что ты ищещь?: ";
			getline(std::cin, seekingFor);
			Msg seekingItemType = "";
			std::cout << "по какому €рлыку ты ищещь?: ";
			getline(std::cin, seekingItemType);

			//std::cout << seekTask(seekingFor, seekingItemType);
		}break;
		case '4':
		{

		}break;
		case '5':
		{
			exit(0);
		}
		}

	}
	To_DoList(const To_DoList*) = delete;

	To_DoList& operator=(const To_DoList*) = delete;
	To_DoNode& operator[](int num)
	{
		return tasks[num];
	}

	void loadList()
	{
		std::ifstream is;
		is.open("fileRoutes.txt");
		Msg data = "";

		To_DoNode nge;
		while (!is.eof())
		{
			data = "";
			std::getline(is, data);

			if (data != "")
			{
				To_DoNode nge;
				nge.loadNode(data);
				expandArray(tasks, nge);
			}
			else
				break;
		}
	}

	void expandArray(To_DoNode* arr, To_DoNode node)
	{
		int newSize = mtd++;
		To_DoNode* temp = new To_DoNode[newSize];
		for (int i = 0; i < mtd; i++)
		{
			temp[i] = arr[i];
		}
		temp[newSize] = node;
		mtd++;
		for (int i = 0; i < newSize; i++)
		{
			arr[i] = temp[i];
		}
		delete[]temp;
	}

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

	int getSize()
	{
		return mtd;
	}
	auto seekTask(Msg seekingFor, Msg seekingItemType)
	{
		if (seekingItemType == "title"||seekingItemType=="Title")
		{
			for (int i = 0; i < mtd; i++)
			{
				if (tasks[i].getTitle() == seekingFor)
				{
					return tasks[i];
				}
			}
		}
	
		if (seekingItemType == "tag" || seekingItemType == "Tag")
		{
			for (int i = 0; i < mtd; i++)
			{
				if (tasks[i].getTag() == seekingFor)
				{
					return tasks[i];
				}
			}
		}

		if (seekingItemType == "date" || seekingItemType == "Date")
		{
			for (int i = 0; i < mtd; i++)
			{
				if (tasks[i].getDate() == seekingFor)
				{
					return tasks[i];
				}
			}
		}
	}

};