#pragma once
#include<iostream>
#include<string>
#include<queue>


enum ToDoType
{
	as = 0, re = 1, mi = 2 
};


class To_DoNode
{
private:
	std::string title;
	ToDoType type;
	std::string desc;
public:
	To_DoNode()
	{
		title = "";
		type = as;
		desc = "";
	}
	To_DoNode(std::string title, ToDoType type, std::string desc)
	{
		this->title = title;
		this->type = type;
		this->desc = desc;
	}

	bool setNode(std::string title, ToDoType type, std::string desc)noexcept
	{
		this->title = title;
		this->type = type;
		this->desc = desc;
		return true;
	}

	void printNode()
	{
		std::cout << title << " (" << type << ")\n";
		std::cout << desc;
	}
};

class To_DoList
{
private:
	std::queue<To_DoNode> tasks;
public:
	To_DoList() = default;
};