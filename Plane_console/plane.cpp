#include <iostream>
#include <string>
#include <set>
#include <vector>

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

	//Вспомогательные
	vector <passenger> list_of_passangers; // Cписок пассажиров
	string plane_type; //Тип самолёта 
};

void create_plane(vector<plane>& aircraft_base)//Функция добавления самолёта в парк авиакомпании
{

	cout << "\nВыберите тип самолёта:";
	cout << "\n1. Airbus A320";
	cout << "\n2. Superjet 100";
	cout << endl;
	cout << "\nПункт номер: ";
	int n;
	cin >> n;
	while (cin.fail() || n > 2)//Обработка ошибочного ввода позиции
	{
		cout << "Ошибка выбора пункта" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Попробуйте ещё раз: ";
		cin >> n;
	}

	switch (n)
	{
	case 1://type airbus
	{
		plane Airbus;
		size_of_park += 1;
		cout << "\n Название самолёта: Airbus_" << size_of_park;
		Airbus.name_of_plane = "Airbus" + to_string(size_of_park);
		cout << "\nВведите кол-во мест, но не более 180: ";
		int seats;
		cin >> seats;
		while (cin.fail() || seats > 180 || seats <= 0)//Обработка ошибочного ввода позиции
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
			Airbus.free_places.insert(i + 1);
		}
		Airbus.place_in_row = 6;
		Airbus.plane_type = "Airbus";
		Airbus.list_of_passangers.resize(seats);
		aircraft_base.push_back(Airbus);//Добавляем самолёт в базу данных
		cout << "\nСамолёт успешно добавлен!" << endl;
		break;

	}
	case 2://type superjet
		plane SuperJet;
		size_of_park += 1;
		cout << "\n Название самолёта: SuperJet_" << size_of_park;
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
		SuperJet.list_of_passangers.resize(seats);
		aircraft_base.push_back(SuperJet);//Добавляем самолёт в базу данных
		cout << "\nСамолёт успешно добавлен!" << endl;
		break;
	}
}

void planes(vector<plane>& aircraft_base)
{

	if (size_of_park == 0)
	{
		cout << "\n\tАктивных самолётов в базе пока нет." << endl;
	}

	for (int i = 0; i < size_of_park; i++)
	{
		plane local_plane = aircraft_base[i];
		cout << "\n" << i+1 << ". Самолёт: " << local_plane.name_of_plane << ", количесвто cвободных мест - " << local_plane.free_places.size() << ", количество занятых мест - " << local_plane.occupied_places.size();
	}
	
}

void add_passanger(vector<plane>& aircraft_base)
{
	if (size_of_park == 0)
	{
		cout << "\nВ парке пока нет самолётов для регистрации пассажиров" << endl;
		return;
	}
	passenger tourist;
	cout << "\nВыберите самолёт: ";//Вывод доступных самолётов
	planes(aircraft_base);
	int NumPlane = 0;
	cout << "\nНомер: ";
	cin >> NumPlane;
	while (cin.fail() || NumPlane > size_of_park)//Обработка ошибочного ввода позиции
	{
		cout << "Ошибка выбора позиции" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Попробуйте ещё раз: ";
		cin >> NumPlane;
	}

	plane local_plane = aircraft_base[NumPlane-1];
	int j = 0;
	
	//Регистрация пассажира
	cout << "\nИмя пассажира: ";
	cin >> tourist.name;//Считывание имени пассажира
	cout << "\nФамилия пассажира: ";
	cin>> tourist.surname;//Считывние фамилии пассажира
	cout << "\nВозраст пассажира: ";
	cin >> tourist.age;//Считывание возраста пассажира
	while (cin.fail())
	{
		cout << "\nНекорректный ввод возраста";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nПопробуйте ещё раз: ";
		cin >> tourist.age;

	}
	
	if (local_plane.plane_type == "Airbus")
	{
		//Печать посадочных мест
		for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
		{
			if (j % 3 == 0)
				cout << "\t";//Проход для пассажиров
			if (j % 6 == 0)
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
				cout << "\t";//Проход для пассажиров
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
	cout << "\nВыберете место: ";
	cin >> tourist.place;
	while (cin.fail() || tourist.place > local_plane.free_places.size() + local_plane.occupied_places.size())
	{
		cout << "\nОшибка ввода места, попробуйте указать существующую позицию";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nПопробуйте ещё раз: ";
		cin >> tourist.place;
	}
	if (local_plane.occupied_places.find(tourist.place) != local_plane.occupied_places.end())
	{
		cout << "\nЭто место уже занято!";
		return;
	}
	cout << "\nВы выбрали: " << tourist.place;
	local_plane.list_of_passangers[tourist.place-1] = tourist;
	local_plane.free_places.erase(tourist.place);//Удаляем свободное место в списке свободных кресел
	local_plane.occupied_places.insert(tourist.place);//Добавление в список занятых кресел место пассажира
	aircraft_base[NumPlane - 1] = local_plane;
}

void find_passanger(vector<plane>& aircraft_base)
{
	planes(aircraft_base);
	if (size_of_park == 0)
	{
		return;
	}
	int NumPlane = 0;
	cout << "\nНомер: ";
	cin >> NumPlane;
	while (cin.fail() || NumPlane > size_of_park || NumPlane <= 0)//Обработка ошибочного ввода позиции
	{
		cout << "Ошибка выбора позиции" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Попробуйте ещё раз: ";
		cin >> NumPlane;
	}

	plane local_plane = aircraft_base[NumPlane - 1];
	
	int j = 0;
	if (local_plane.plane_type == "Airbus")
	{
		if(local_plane.occupied_places.size() == 0)
		{
			cout << "Нет занятых мест";
			return;
		}
		//Печать посадочных мест
		for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
		{
			if (j % 3 == 0 && j != 0)
				cout << "\t";//Проход для пассажиров
			if (j % 6 == 0)
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
				cout << "\t";//Проход для пассажиров
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
	cout << "\nВыберете место: ";
	int num_of_place;
	cin >> num_of_place;

	while (cin.fail() || num_of_place > local_plane.free_places.size() + local_plane.occupied_places.size())
	{
		cout << "\nОшибка ввода места, попробуйте указать существующую позицию";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Попробуйте ещё раз: ";
		cin >> num_of_place;
	}

	if (local_plane.free_places.find(num_of_place) != local_plane.free_places.end())
	{
		cout << "\nЭто место ещё свободно!";
			return;
	}
	passenger tourist = local_plane.list_of_passangers[num_of_place-1];
	cout << "\nИмя: "<< tourist.name;
	cout << "\nФамилия: " << tourist.surname;
	cout << "\nВозраст: " << tourist.age;
}

void del_passenger(vector <plane> &aircraft_base)
{
	planes(aircraft_base);
	if (size_of_park == 0)
	{
		return;
	}
	int NumPlane = 0;
	cout << "\nНомер: ";
	cin >> NumPlane;
	while (cin.fail() || NumPlane > size_of_park || NumPlane <= 0)//Обработка ошибочного ввода позиции
	{
		cout << "Ошибка выбора позиции" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Попробуйте ещё раз: ";
		cin >> NumPlane;
	}

	plane local_plane = aircraft_base[NumPlane - 1];

	int j = 0;
	if (local_plane.plane_type == "Airbus")
	{
		if (local_plane.occupied_places.size() == 0)
		{
			cout << "Нет занятых мест";
			return;
		}
		//Печать посадочных мест
		for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
		{
			if (j % 3 == 0 && j != 0)
				cout << "\t";//Проход для пассажиров
			if (j % 6 == 0)
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
				cout << "\t";//Проход для пассажиров
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
	cout << "\nВыберете место: ";
	int num_of_place;
	cin >> num_of_place;
	while (cin.fail() || num_of_place > local_plane.free_places.size() + local_plane.occupied_places.size())
	{
		cout << "\nОшибка ввода места, попробуйте указать существующую позицию";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Попробуйте ещё раз: ";
		cin >> num_of_place;
	}

	if (local_plane.free_places.find(num_of_place) != local_plane.free_places.end())
	{
		cout << "\nЭто место ещё свободно!";
		return;
	}

	local_plane.list_of_passangers.erase(local_plane.list_of_passangers.begin() + num_of_place - 1);
	local_plane.free_places.insert(num_of_place);//Удаляем свободное место в списке свободных кресел
	local_plane.occupied_places.erase(num_of_place);//Добавление в список занятых кресел место пассажира
	aircraft_base[NumPlane - 1] = local_plane;
}


int console(int i, vector<plane>& aircraft_base)
{
	cout << "\n\tКонсоль сотрудника аэропорта" << endl;
	cout << "\n 1. Добавить самолёт";
	cout << "\n 2. Cамолёты авиакомпании";
	cout << "\n 3. Зарегестрировать человека на рейс";
	cout << "\n 4. Просмотреть занятое место";
	cout << "\n 5. Отменить регистрацию пассажира";
	cout << "\n 0. Выйти";
	//cout << "\n  "
	cout << "\n Введите номер пункта меню: ";
	unsigned n;
	
	cin >> n;
	while (cin.fail() || n>5)
	{
		cout << "\nОшибка выбора позиции";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nПопробуйте ещё раз: ";
		cin >> n;
	}

	//Реализация работы кансоли
	switch (n)
	{

	case 1:
		create_plane(aircraft_base);
		return 1;

	case 2:
		cout << "\nСамолёты в базе";
		planes(aircraft_base);
		return 1;

	case 3:
		add_passanger(aircraft_base);
		return 1;

	case 4:
		find_passanger(aircraft_base);
		return 1;

	case 5:
		del_passenger(aircraft_base);
		return 1;

	case 0:
		return 0;	
	}
	cout << "Такого пункта меню нет, попробуйте ещё раз" << endl;
	return 1;
}

int main()
{
	setlocale(LC_ALL ,"Russian");//Подключаем русский язык

	vector<plane> aircraft_base;//Создаём массив для хранения самолётов

	int i = 1;
	while (i == 1)
	{
		i = console(i,aircraft_base);//Заходим в консоль
	}
	
	return 0;

}