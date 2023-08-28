#include "plane_console_functios.h"


void planes(vector<plane>& aircraft_base, int flag, int size_of_park)
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
		cout << "\n" << i + 1 << ". Самолёт: " << local_plane.name_of_plane << ", количество cвободных мест - " << local_plane.free_places.size() << ", количество занятых мест - " << local_plane.occupied_places.size();
	}
}