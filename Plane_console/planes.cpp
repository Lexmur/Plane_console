#include "plane_console_functios.h"


void planes(vector<plane>& aircraft_base, int flag, int size_of_park)
{
	system("cls");
	if (size_of_park == 0)
	{
		cout << "\n\t�������� �������� � ���� ���� ���." << endl;
		return;
	}
	if (flag == 1)
	{
		cout << "�������� ������";
	}
	else if (flag == 0)
	{
		cout << "\n������� � ����";
	}
	for (int i = 0; i < size_of_park; i++)
	{
		plane local_plane = aircraft_base[i];
		cout << "\n" << i + 1 << ". ������: " << local_plane.name_of_plane << ", ���������� c�������� ���� - " << local_plane.free_places.size() << ", ���������� ������� ���� - " << local_plane.occupied_places.size();
	}
}