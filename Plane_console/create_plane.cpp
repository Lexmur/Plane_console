#include "plane_console_functios.h"

void create_plane(vector<plane>& aircraft_base, int& size_of_park)//Функция добавления самолёта в парк авиакомпании
{
	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;
	while (exit != 0)
	{
		system("cls");
		cout << "Выберите тип самолёта:";
		cout << "\n1. Airbus A320";
		cout << "\n2. Superjet 100";
		cout << "\nНазад";

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
			if (ActiveMenuItem == 1)
			{
				system("cls");
				plane Airbus;
				size_of_park += 1;
				cout << "\tНазвание самолёта: Airbus_" << size_of_park;
				Airbus.name_of_plane = "Airbus" + to_string(size_of_park);
				cout << "\nВведите кол-во мест, но не более 180: ";
				unsigned seats;
				cin >> seats;
				while (cin.fail() || seats > 180 || seats == 0)//Обработка ошибочного ввода позиции
				{
					cout << "\nОшибка ввода кол-ва мест" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Попробуйте ещё раз: ";
					cin >> seats;
				}
				Airbus.all_places = seats;
				//Создаём посадочные места
				for (int i = 0; i < seats; i++)
				{
					Airbus.free_places.insert(i + 1);
				}
				Airbus.place_in_row = 6;
				Airbus.plane_type = "Airbus";
				Airbus.list_of_passangers.resize(seats);
				aircraft_base.push_back(Airbus);//Добавляем самолёт в базу данных
				cout << "\nСамолёт успешно добавлен!" << endl;
				exit = 0;

			}
			if (ActiveMenuItem == 2)
			{
				system("cls");
				plane SuperJet;
				size_of_park += 1;
				cout << "\tНазвание самолёта: SuperJet_" << size_of_park;
				SuperJet.name_of_plane = "SuperJet" + to_string(size_of_park);
				cout << "\nВведите кол-во мест, но не более 100: ";
				int seats;
				cin >> seats;
				while (cin.fail() || seats > 100 || seats <= 0)//Обработка ошибочного ввода позиции
				{
					cout << "Ошибка ввода кол-ва мест" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Попробуйте ещё раз: ";
					cin >> seats;
				}
				//Создаём посадочные места
				for (int i = 0; i < seats; i++)
				{
					SuperJet.free_places.insert(i + 1);
				}
				SuperJet.place_in_row = 5;
				SuperJet.plane_type = "SuperJet";
				SuperJet.all_places = seats;
				SuperJet.list_of_passangers.resize(seats);
				aircraft_base.push_back(SuperJet);//Добавляем самолёт в базу данных
				cout << "\nСамолёт успешно добавлен!" << endl;
				exit = 0;
			}
			if (ActiveMenuItem == 3)
			{
				exit = 0;
			}
			break;
		}//switch
		//Обработка выход за границы меню
		if (ActiveMenuItem < 1) ActiveMenuItem = 1;
		if (ActiveMenuItem > 3) ActiveMenuItem = 3;
	}//while
}