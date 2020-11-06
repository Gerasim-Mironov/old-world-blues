#include"To_Do.hpp"
#include<conio.h>

extern std::string getchCin(std::string mz)
{
	char key;
	while (0x29a)
	{
		key = _getch();
		if (key == 13)
			break;
		if (key == 8)
		{
			mz[mz.size() - 1] = '\0';
		}
		std::cout << key;
		mz += key;
	}

	return mz;
}
int main()
{
#pragma region
	setlocale(0, "");
#pragma endregion
	

	return 0xd;
}