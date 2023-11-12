#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#undef max//Решает конфликт пространства имён
#include <conio.h>

using namespace std;

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

void position_checking(int& Row, int& Colunm, int& realplace, const plane& local_plane);

void gotoxy(int x, int y);//Функция манипуляции курсором

void create_plane(vector<plane>& aircraft_base, int& size_of_park);//Функция добавления самолёта в парк авиакомпании

void planes(vector<plane>& aircraft_base, int flag, int size_of_park);//Функция просмотра авиапарка

void add_passanger(vector<plane>& aircraft_base, int size_of_park);//Функция регистрации пассажира

void find_passanger(vector<plane>& aircraft_base, int size_of_park);//Функция просмотра данных о пассажире

void del_passenger(vector <plane>& aircraft_base, int size_of_park);//Функция удаления пассажира


