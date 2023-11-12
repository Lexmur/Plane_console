#include "plane_console_functios.h"


void add_passanger(vector<plane>& aircraft_base, int size_of_park)
{
	system("cls");
	if (size_of_park == 0)
	{
		cout << "� ����� ���� ��� �������� ��� ����������� ����������" << endl;
		system("pause");
		return;
	}
	passenger tourist;

	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;

	while (exit != 0)
	{
		system("cls");
		int flag = 1;
		planes(aircraft_base, flag, size_of_park);//����� ��������� ��������
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
			if (ActiveMenuItem == size_of_park + 1)
			{
				exit = 0;
				break;
			}
			plane local_plane = aircraft_base[ActiveMenuItem - 1];

			if (local_plane.all_places == local_plane.occupied_places.size())
			{
				system("cls");
				cout << "��� ��������� ����" << endl;
				system("pause");
				break;
			}

			//����������� ���������
			system("cls");
			cout << "��� ���������: ";
			cin >> tourist.name;//���������� ����� ���������
			cout << "\n������� ���������: ";
			cin >> tourist.surname;//��������� ������� ���������
			cout << "\n������� ���������: ";
			cin >> tourist.age;//���������� �������� ���������
			while (cin.fail() || tourist.age < 0)
			{
				cout << "\n������������ ���� ��������";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\n���������� ��� ���: ";
				cin >> tourist.age;

			}
			system("cls");
			int j = 0;
			if (local_plane.plane_type == "Airbus")
			{
				//������ ���������� ����
				for (int i = 1; i <= local_plane.all_places; i++)
				{
					if (j % 3 == 0 && j != 0)
						cout << "\t";//������ ��� ����������
					if (j % 6 == 0 && j != 0)
						cout << endl;
					if (local_plane.occupied_places.find(i) != local_plane.occupied_places.end())
					{
						cout.width(4);
						cout << "x";//���� ����� ������ 
						j++;
						continue;
					}
					cout.width(4);//������ ���� ������ ����������� ����� ����� 
					cout << i;
					j++;
				}
			}
			else//if type == SuperJet
			{
				int spec_2 = 2;//���� ��� ������ ������� ����� 2 ������� �����
				int spec_5 = 5;//���� ��� �������� ����
				//������ ���������� ����
				for (int i = 1; i <= local_plane.free_places.size() + local_plane.occupied_places.size(); i++)
				{

					if (j == spec_2)
					{
						cout << "    ";//������ ��� ����������
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
						cout << "x";//���� ����� ������ 
						j++;
						continue;
					}
					cout.width(4);//������ ���� ������ ����������� ����� ����� 
					cout << i;
					j++;
				}
			}
			tourist.place = 0;
			int Colunm = 3;
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
				case 72: Row--; realplace -= local_plane.place_in_row; break;//������� �����

				case 80: Row++; realplace += local_plane.place_in_row; break;//������� ����

				case 75://������� ����� 
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

				case 77://������� ������
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
					cout << "�� ������� �����: " << tourist.place;
					cout << "\n���: " << tourist.name;
					cout << "\n�������: " << tourist.surname;
					cout << "\n�������: " << tourist.age << endl;
					local_plane.list_of_passangers[tourist.place - 1] = tourist;
					local_plane.free_places.erase(tourist.place);//������� ��������� ����� � ������ ��������� ������
					local_plane.occupied_places.insert(tourist.place);//���������� � ������ ������� ������ ����� ���������
					aircraft_base[ActiveMenuItem - 1] = local_plane;
					system("pause");
					break;

				}
				position_checking(Row, Colunm, realplace, local_plane);
			}
			//��������� ����� �� ������� ����

		}
		if (ActiveMenuItem < 1) ActiveMenuItem = 1;
		if (ActiveMenuItem > size_of_park + 1) ActiveMenuItem = size_of_park + 1;
	}//while

}