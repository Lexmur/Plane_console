#include "plane_console_functios.h"


void find_passanger(vector<plane>& aircraft_base, int size_of_park)
{
	system("cls");
	if (size_of_park == 0)
	{
		cout << "В парке нет активных самолётов" << endl;
		system("pause");
		return;
	}
	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;

	while (exit != 0)
	{
		system("cls");
		int flag = 1;
		planes(aircraft_base, flag, size_of_park);//Вывод доступных самолётов
		cout << "\nВыход";
		gotoxy(0, ActiveMenuItem);

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}

		switch (ch)
		{
		case 72: ActiveMenuItem--; break;//Стрелка вверх

		case 80: ActiveMenuItem++; break;//Стрелка вниз

		case 13://Клавиша enter
			if (ActiveMenuItem == size_of_park + 1)
			{
				exit = 0;
				break;
			}
			plane local_plane = aircraft_base[ActiveMenuItem - 1];

			system("cls");

			int j = 0;
			if (local_plane.plane_type == "Airbus")
			{
				if (local_plane.occupied_places.size() == 0)
				{
					cout << "Нет занятых мест";
					system("pause");
					return;
				}
				//Печать посадочных мест
				for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
				{
					if (j % 3 == 0 && j != 0)
						cout << "\t";//Проход для пассажиров
					if (j % 6 == 0 && j != 0)
						cout << endl;
					if (local_plane.free_places.find(i) != local_plane.free_places.end())
					{
						cout.width(4);
						cout << "x";//Если место занято 
						j++;
						continue;
					}
					cout.width(4);//Ширина поля вывода посадочного места места 
					cout << i;
					j++;
				}
			}
			else//if type == SuperJet
			{
				if (local_plane.occupied_places.size() == 0)
				{
					cout << "Нет занятых мест";
					return;
				}
				int spec_2 = 2;//Флаг для вывода пробела после 2 сиденья слева
				int spec_5 = 5;//Флаг для переноса ряда
				//Печать посадочных мест
				for (int i = 1; i <= local_plane.free_places.size() + local_plane.occupied_places.size(); i++)
				{

					if (j == spec_2)
					{
						cout << "    ";//Проход для пассажиров
						spec_2 += 5;
					}
					if (j == spec_5)
					{
						cout << endl;
						spec_5 += 5;
					}
					if (local_plane.free_places.find(i) != local_plane.free_places.end())
					{
						cout.width(4);
						cout << "x";//Если место занято 
						j++;
						continue;
					}
					cout.width(4);//Ширина поля вывода посадочного места места 
					cout << i;
					j++;
				}
			}

			int num_of_place = 0;
			int Colunm = 3;
			int Row = 0;
			int realplace = 1;
			while (!num_of_place)
			{
				gotoxy(Colunm, Row);

				ch = _getch();
				if (ch == 224)
				{
					ch = _getch();
				}

				switch (ch)
				{
				case 72: Row--; realplace -= local_plane.place_in_row; break;//Стрелка вверх

				case 80: Row++; realplace += local_plane.place_in_row; break;//Стрелка вниз

				case 75://Стрелка влево 
					if (local_plane.plane_type == "SuperJet")
					{
						Colunm - 4 == 11 ? Colunm -= 8 : Colunm -= 4;
						realplace--;
					}
					else
					{
						Colunm - 4 == 15 ? Colunm -= 8 : Colunm -= 4;
						realplace--;
					}
					break;

				case 77://Стрелка вправо
					if (local_plane.plane_type == "SuperJet")
					{
						Colunm + 4 == 11 ? Colunm += 8 : Colunm += 4;
						realplace++;
					}
					else
					{
						Colunm + 4 == 15 ? Colunm += 8 : Colunm += 4;
						realplace++;
					}
					break;

				case 13://Enter
					if (local_plane.free_places.find(realplace) != local_plane.free_places.end())
					{
						num_of_place = 0;
						break;
					}
					else
					{
						passenger tourist = local_plane.list_of_passangers[realplace - 1];
						cout << "\nИмя: " << tourist.name;
						cout << "\nФамилия: " << tourist.surname;
						cout << "\nВозраст: " << tourist.age;
						num_of_place = 1;
						system("pause");
					}

				}
				position_checking(Row, Colunm, realplace, local_plane);

			}
			//Обработка выход за границы меню

		}
		if (ActiveMenuItem < 1) ActiveMenuItem = 1;
		if (ActiveMenuItem > size_of_park + 1) ActiveMenuItem = size_of_park + 1;
	}//while

}