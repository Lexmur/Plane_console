#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#undef max//Решает конфликт пространства имён
#include <conio.h>

using namespace std;


int size_of_park = 0; //Размер авиапарка компании

struct passenger//Класс пассажир
{
	unsigned place = 0;
	string name;
	string surname;
	unsigned age = 0;
};

struct plane
{
	//Основные харакетристики
	string name_of_plane; 
	unsigned place_in_row = 0; //Кол-во мест в одном ряду
	set <int> free_places; // Кол-во свободных мест
	set <int> occupied_places; //Кол-во занятых мест
	int all_places = 0;

	//Вспомогательные
	vector <passenger> list_of_passangers; // Cписок пассажиров
	string plane_type; //Тип самолёта 
};

void position_checking(int& Row, int& Colunm, int& realplace, const plane & local_plane)
{
	if (Row < 0)
	{
		Row = 0;
		realplace += local_plane.place_in_row;
	}
	if (Row > ((local_plane.all_places - 1) / local_plane.place_in_row))
	{
		Row--;
		realplace -= local_plane.place_in_row;
	}
	if (Colunm < 3)
	{
		Colunm = 3;
		realplace++;
	}
	if (Colunm > local_plane.place_in_row * 4 + 3)
	{
		Colunm = local_plane.place_in_row * 4 + 3;
		realplace--;
	}
	if (realplace > local_plane.all_places)
	{
		while (realplace != local_plane.all_places)
		{
			if (local_plane.plane_type == "SuperJet" && Colunm == 15)
			{
				Colunm -= 4;
			}
			else if (local_plane.plane_type == "Airbus" && Colunm == 19)
			{
				Colunm -= 4;
			}
			Colunm -= 4;
			realplace--;
		}
	}
}

void gotoxy(int x, int y)//Функция манипуляции курсором
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void create_plane(vector<plane>& aircraft_base)//Функция добавления самолёта в парк авиакомпании
{
	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;
	while(exit != 0)
	{
		system("cls");
		cout << "Выберите тип самолёта:";
		cout << "\n1. Airbus A320";
		cout << "\n2. Superjet 100";
		cout << "\n3. Назад";

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
			if(ActiveMenuItem == 1)
			{
				system("cls");
				plane Airbus;
				size_of_park += 1;
				cout << "\tНазвание самолёта: Airbus_" << size_of_park;
				Airbus.name_of_plane = "Airbus" + to_string(size_of_park);
				cout << "\nВведите кол-во мест, но не более 180: ";
				int seats;
				cin >> seats;
				while (cin.fail() || seats > 180 || seats <= 0)//Обработка ошибочного ввода позиции
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

void planes(vector<plane>& aircraft_base,int flag)
{
system("cls");

	if (size_of_park == 0)
	{
		cout << "\n\tАктивных самолётов в базе пока нет." << endl;
		return;
	}
	if (flag == 1)
	{
		cout << "Выберите самолёт";
	}
	else if (flag == 0)
	{
		cout << "\nСамолёты в базе";
	}
	for (int i = 0; i < size_of_park; i++)
	{
		plane local_plane = aircraft_base[i];
		cout << "\n" << i+1 << ". Самолёт: " << local_plane.name_of_plane << ", количесвто cвободных мест - " << local_plane.free_places.size() << ", количество занятых мест - " << local_plane.occupied_places.size();
	}
	
}

void add_passanger(vector<plane>& aircraft_base)
{
	system("cls");
	if (size_of_park == 0)
	{
		cout << "В парке пока нет самолётов для регистрации пассажиров" << endl;
		system("pause");
		return;
	}
	passenger tourist;

	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;

	while(exit!= 0)
	{
		system("cls");
		int flag = 1;
		planes(aircraft_base, flag);//Вывод доступных самолётов
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

			if (local_plane.all_places == local_plane.occupied_places.size())
			{
				system("cls");
				cout << "Нет свободных мест"<<endl;
				system("pause");
				break;
			}

			//Регистрация пассажира
			system("cls");
			cout << "Имя пассажира: ";
			cin >> tourist.name;//Считывание имени пассажира
			cout << "\nФамилия пассажира: ";
			cin >> tourist.surname;//Считывние фамилии пассажира
			cout << "\nВозраст пассажира: ";
			cin >> tourist.age;//Считывание возраста пассажира
			while (cin.fail() || tourist.age < 0)
			{
				cout << "\nНекорректный ввод возраста";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nПопробуйте ещё раз: ";
				cin >> tourist.age;

			}
			system("cls");
			int j = 0;
			if (local_plane.plane_type == "Airbus")
			{
				//Печать посадочных мест
				for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
				{
					if (j % 3 == 0 && j != 0)
						cout << "\t";//Проход для пассажиров
					if (j % 6 ==  0 && j != 0)
						cout << endl;
					if (local_plane.occupied_places.find(i) != local_plane.occupied_places.end())
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
					if (local_plane.occupied_places.find(i) != local_plane.occupied_places.end())
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
			tourist.place = 0;
			int Colunm  = 3;
			int Row = 0;
			int realplace = 1;
			while (!tourist.place)
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

				case 13:
					if (local_plane.occupied_places.find(realplace) != local_plane.occupied_places.end())
					{
						tourist.place = 0;
						break;
					}
					tourist.place = realplace;
					system("cls");
					cout << "Вы выбрали место: " << tourist.place;
					cout << "\nИмя: " << tourist.name;
					cout << "\nФамилия: " << tourist.surname;
					cout << "\nВозраст: " << tourist.age << endl;
					local_plane.list_of_passangers[tourist.place - 1] = tourist;
					local_plane.free_places.erase(tourist.place);//удаляем свободное место в списке свободных кресел
					local_plane.occupied_places.insert(tourist.place);//добавление в список занятых кресел место пассажира
					aircraft_base[ActiveMenuItem - 1] = local_plane;
					system("pause");
					break;

				}
				position_checking(Row, Colunm, realplace, local_plane);
			}
			//Обработка выход за границы меню
			
		}
		if (ActiveMenuItem < 1) ActiveMenuItem = 1;
		if (ActiveMenuItem > size_of_park+1) ActiveMenuItem = size_of_park+1;
	}//while
	
}

void find_passanger(vector<plane>& aircraft_base)
{
	system("cls");
	if (size_of_park == 0)
	{
		cout << "В парке нет активных самолётов"<<endl;
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
		planes(aircraft_base, flag);//Вывод доступных самолётов
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

void del_passenger(vector <plane> &aircraft_base)
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
		planes(aircraft_base, flag);//Вывод доступных самолётов
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
					cout << "Нет занятых мест"<<endl;
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
						local_plane.list_of_passangers.erase(local_plane.list_of_passangers.begin() + realplace - 1);
						local_plane.free_places.insert(realplace);//Добавляем свободное место в список свободных кресел
						local_plane.occupied_places.erase(realplace);//Удаляем занятое место из списка занятых
						aircraft_base[ActiveMenuItem - 1] = local_plane;
						num_of_place = 1;
						break;
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

int main()
{
	setlocale(LC_ALL ,"Russian");//Подключаем русский язык

	vector<plane> aircraft_base;//Создаём массив для хранения самолётов
	//Вспомогательные переменные
	int exit = 1;
	int ActiveMenuItem = 3;
	int ch = 0;

	//Реализация консоли
	while(exit != 0)
	{
		system("cls");
		cout << "\n\tКонсоль сотрудника аэропорта" << endl;
		cout << "\n 1. Добавить самолёт";
		cout << "\n 2. Cамолёты авиакомпании";
		cout << "\n 3. Зарегестрировать человека на рейс";
		cout << "\n 4. Просмотреть занятое место";
		cout << "\n 5. Отменить регистрацию пассажира";
		cout << "\n 0. Выйти" << endl;
		//cout << "\n  "
		cout << "\n Введите номер пункта меню, используя стрелочки клавиатуры. Для перехода по пункту нажмите Enter";

		

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

			if (ActiveMenuItem == 3)
			{
				create_plane(aircraft_base);
				cout << endl;
				system("pause");
			}
			else if (ActiveMenuItem == 4)
			{
				int flag = 0;
				planes(aircraft_base, flag);
				cout << endl;
				system("pause");
			}
			else if (ActiveMenuItem == 5)
			{
				add_passanger(aircraft_base);
			}
			else if (ActiveMenuItem == 6)
			{
				find_passanger(aircraft_base);
				cout<<endl;
			}
			else if (ActiveMenuItem == 7)
			{
				del_passenger(aircraft_base);
				cout << endl;
			}
			else if (ActiveMenuItem == 8)
			{
				exit = 0;
			}
			break;
		}
		//Ограничение по скачкам пунктов меню
		if (ActiveMenuItem < 3) ActiveMenuItem = 3;
		if (ActiveMenuItem > 8) ActiveMenuItem = 8;
	}

	return 0;

}