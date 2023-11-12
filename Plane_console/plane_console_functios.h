#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#undef max//������ �������� ������������ ���
#include <conio.h>

using namespace std;

struct passenger//����� ��������
{
	unsigned place = 0;
	string name;
	string surname;
	unsigned age = 0;
};

struct plane
{
	//�������� ��������������
	string name_of_plane;
	unsigned place_in_row = 0; //���-�� ���� � ����� ����
	set <int> free_places; // ���-�� ��������� ����
	set <int> occupied_places; //���-�� ������� ����
	int all_places = 0;

	//���������������
	vector <passenger> list_of_passangers; // C����� ����������
	string plane_type; //��� ������� 
};

void position_checking(int& Row, int& Colunm, int& realplace, const plane& local_plane);

void gotoxy(int x, int y);//������� ����������� ��������

void create_plane(vector<plane>& aircraft_base, int& size_of_park);//������� ���������� ������� � ���� ������������

void planes(vector<plane>& aircraft_base, int flag, int size_of_park);//������� ��������� ���������

void add_passanger(vector<plane>& aircraft_base, int size_of_park);//������� ����������� ���������

void find_passanger(vector<plane>& aircraft_base, int size_of_park);//������� ��������� ������ � ���������

void del_passenger(vector <plane>& aircraft_base, int size_of_park);//������� �������� ���������


