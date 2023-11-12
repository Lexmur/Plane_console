#include "plane_console_functios.h"

void create_plane(vector<plane>& aircraft_base, int& size_of_park)//������� ���������� ������� � ���� ������������
{
	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;
	while (exit != 0)
	{
		system("cls");
		cout << "�������� ��� �������:";
		cout << "\n1. Airbus A320";
		cout << "\n2. Superjet 100";
		cout << "\n�����";

		gotoxy(0, ActiveMenuItem);

		ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
		}

		switch (ch)
		{
		case 72: ActiveMenuItem--; break;//������� �����

		case 80: ActiveMenuItem++; break;//������� ����

		case 13://������� enter
			if (ActiveMenuItem == 1)
			{
				system("cls");
				plane Airbus;
				size_of_park += 1;
				cout << "\t�������� �������: Airbus_" << size_of_park;
				Airbus.name_of_plane = "Airbus" + to_string(size_of_park);
				cout << "\n������� ���-�� ����, �� �� ����� 180: ";
				unsigned seats;
				cin >> seats;
				while (cin.fail() || seats > 180 || seats == 0)//��������� ���������� ����� �������
				{
					cout << "\n������ ����� ���-�� ����" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "���������� ��� ���: ";
					cin >> seats;
				}
				Airbus.all_places = seats;
				//������ ���������� �����
				for (int i = 0; i < seats; i++)
				{
					Airbus.free_places.insert(i + 1);
				}
				Airbus.place_in_row = 6;
				Airbus.plane_type = "Airbus";
				Airbus.list_of_passangers.resize(seats);
				aircraft_base.push_back(Airbus);//��������� ������ � ���� ������
				cout << "\n������ ������� ��������!" << endl;
				exit = 0;

			}
			if (ActiveMenuItem == 2)
			{
				system("cls");
				plane SuperJet;
				size_of_park += 1;
				cout << "\t�������� �������: SuperJet_" << size_of_park;
				SuperJet.name_of_plane = "SuperJet" + to_string(size_of_park);
				cout << "\n������� ���-�� ����, �� �� ����� 100: ";
				int seats;
				cin >> seats;
				while (cin.fail() || seats > 100 || seats <= 0)//��������� ���������� ����� �������
				{
					cout << "������ ����� ���-�� ����" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "���������� ��� ���: ";
					cin >> seats;
				}
				//������ ���������� �����
				for (int i = 0; i < seats; i++)
				{
					SuperJet.free_places.insert(i + 1);
				}
				SuperJet.place_in_row = 5;
				SuperJet.plane_type = "SuperJet";
				SuperJet.all_places = seats;
				SuperJet.list_of_passangers.resize(seats);
				aircraft_base.push_back(SuperJet);//��������� ������ � ���� ������
				cout << "\n������ ������� ��������!" << endl;
				exit = 0;
			}
			if (ActiveMenuItem == 3)
			{
				exit = 0;
			}
			break;
		}//switch
		//��������� ����� �� ������� ����
		if (ActiveMenuItem < 1) ActiveMenuItem = 1;
		if (ActiveMenuItem > 3) ActiveMenuItem = 3;
	}//while
}