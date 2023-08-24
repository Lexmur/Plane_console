#include "plane_console_functios.h"

int main()
{
	setlocale(LC_ALL ,"Russian");//Подключаем русский язык
	int size_of_park = 0; //Создаём счётчик парка самолётов
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
				create_plane(aircraft_base,size_of_park);
				cout << endl;
				system("pause");
			}
			else if (ActiveMenuItem == 4)
			{
				int flag = 0;
				planes(aircraft_base, flag,size_of_park);
				cout << endl;
				system("pause");
			}
			else if (ActiveMenuItem == 5)
			{
				add_passanger(aircraft_base,size_of_park);
			}
			else if (ActiveMenuItem == 6)
			{
				find_passanger(aircraft_base,size_of_park);
				cout<<endl;
			}
			else if (ActiveMenuItem == 7)
			{
				del_passenger(aircraft_base,size_of_park);
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