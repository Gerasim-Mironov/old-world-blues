#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include<vector>
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
			if (data != "")
			{
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
			
			mtd++;
		}
		is.close();
	}
	void beatIt()
	{
		std::ifstream is("fileRoutes.txt");
		std::vector<Msg> ul;

		Msg data;
		while (!is.eof())
		{
			data = "";
			getline(is, data);
			if (data != "")
				ul.push_back(data);
		}
		is.close();

		for (int i = 0; i<ul.size(); i++)
		{
			if (ul[i] == cherry)
			{
				ul.erase(ul.begin() + i);
			}
		}

		std::ofstream os("fileRoutes.txt");
		for(int i = 0; i < ul.size(); i++)
		{
			os << ul[i] << "\n";
		}
		os.close();
	}
	bool displayNode()noexcept
	{
		std::cout<<"//////////////////////////////////////////////////////////////////////\n";
		std::cout << title << "\n";
		std::cout << tag << "\n";
		std::cout << date << "\n";
		std::cout << desc << "\n";

		return true;
	}
	/*void displayNode(To_DoNode node) no sense if it's not static
	{
		std::cout << node.title<<"\n";
		std::cout << node.tag << "\n";
		std::cout << "finish until: " << node.date << "\n";
		std::cout << node.desc << "\n";
	}*/
	friend std::ostream& operator<<(std::ostream os, To_DoNode node)
	{
		os << node.title << " (on run)\n";
		os << node.tag << "\n";
		os << "finish until: " << node.date << "\n";
		os << node.desc << "\n";

		return os;
	}

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
		mtd = 0;
		loadList();
		mainMenu();
	}
	void mainMenu()
	{
		while (true)
		{
			std::cout << "1-> показать все дела\n2-> создать дело\n3-> закрыть дело\n4-> найти дело\n5-> уйти\n(не жмите Enter после выбора)\n";
			char sym = _getch();
			switch (sym)
			{
			case '1':
			{
				system("cls");
				for (int i = 0; i < mtd; i++)
				{
					tasks[i].displayNode();
				}
				_getch();
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
				expandArray(nge);
				std::cout << "ок\n";
				_getch();
			}break;
			case '3':
			{
				system("cls");
				std::cout << "выбери номер дела: ";
				for (int i = 0; i < mtd; i++)
				{
					const char mtd = (const char)i+48;
					std::cout << "//" << mtd;
				}
				std::cout << "//\n";

				char ch = _getch();
				int unl = (int)ch - 48;
				tasks[unl].beatIt();
				decreaseArray(unl);

				std::cout << "\n\nего практически больше не сущевствует.\n";
				_getch();
			}break;
			case '4':
			{
				system("cls");

				Msg seekingFor = "";
				std::cout << "что ты ищещь?: ";
				getline(std::cin, seekingFor);
				Msg seekingItemType = "";
				std::cout << "по какому €рлыку ты ищещь?: ";
				getline(std::cin, seekingItemType);

				seekTask(seekingFor, seekingItemType).displayNode();
				_getch();
			}break;
			case '5':
			{
				exit(0);
			}
			}
			system("cls");
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
				expandArray(nge);
			}
			else
				break;
		}
	}

	void expandArray(To_DoNode node)
	{
		auto temp = new To_DoNode[mtd + 1];
		for (unsigned int i = 0; i < mtd; i++)
			temp[i] = tasks[i];
		temp[mtd] = node;
		++mtd;
		delete[]tasks;
		tasks = temp;
	}
	void decreaseArray(int toKill)
	{
		tasks[toKill].beatIt();
		int eclipse = mtd - 1;
		To_DoNode* temp = new To_DoNode[eclipse];
		for (int i = 0; i < mtd; i++)
		{
			if (i != toKill)
			{
				temp[i] = tasks[i];
			}
		}

		for (int u = 0; u < eclipse; u++)
		{
			tasks[u] = temp[u];
		}
		mtd--;
		delete[]temp;
	}

	To_DoNode seekTask(Msg seekingFor, Msg seekingItemType)
	{
		if (seekingItemType == "title" || seekingItemType == "Title")
		{
			seekingFor += " (on run)";
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
			seekingFor = "finish until: " + seekingFor;
			for (int i = 0; i < mtd; i++)
			{
				if (tasks[i].getDate() == seekingFor)
				{
					return tasks[i];
				}
			}
		}
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

};