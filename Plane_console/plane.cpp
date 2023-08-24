#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <windows.h>
#undef max//������ �������� ������������ ���
#include <conio.h>

using namespace std;


int size_of_park = 0; //������ ��������� ��������

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

void gotoxy(int x, int y)//������� ����������� ��������
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void create_plane(vector<plane>& aircraft_base)//������� ���������� ������� � ���� ������������
{
	int exit = 1;
	int ActiveMenuItem = 1;
	int ch = 0;
	while(exit != 0)
	{
		system("cls");
		cout << "�������� ��� �������:";
		cout << "\n1. Airbus A320";
		cout << "\n2. Superjet 100";
		cout << "\n3. �����";

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
			if(ActiveMenuItem == 1)
			{
				system("cls");
				plane Airbus;
				size_of_park += 1;
				cout << "\t�������� �������: Airbus_" << size_of_park;
				Airbus.name_of_plane = "Airbus" + to_string(size_of_park);
				cout << "\n������� ���-�� ����, �� �� ����� 180: ";
				int seats;
				cin >> seats;
				while (cin.fail() || seats > 180 || seats <= 0)//��������� ���������� ����� �������
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

void planes(vector<plane>& aircraft_base,int flag)
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
		cout << "\n" << i+1 << ". ������: " << local_plane.name_of_plane << ", ���������� c�������� ���� - " << local_plane.free_places.size() << ", ���������� ������� ���� - " << local_plane.occupied_places.size();
	}
	
}

void add_passanger(vector<plane>& aircraft_base)
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

	while(exit!= 0)
	{
		system("cls");
		int flag = 1;
		planes(aircraft_base, flag);//����� ��������� ��������
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
				cout << "��� ��������� ����"<<endl;
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
				for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
				{
					if (j % 3 == 0 && j != 0)
						cout << "\t";//������ ��� ����������
					if (j % 6 ==  0 && j != 0)
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
		if (ActiveMenuItem > size_of_park+1) ActiveMenuItem = size_of_park+1;
	}//while
	
}

void find_passanger(vector<plane>& aircraft_base)
{
	system("cls");
	if (size_of_park == 0)
	{
		cout << "� ����� ��� �������� ��������"<<endl;
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
		planes(aircraft_base, flag);//����� ��������� ��������
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

			system("cls");
			
			int j = 0;
			if (local_plane.plane_type == "Airbus")
			{
				if (local_plane.occupied_places.size() == 0)
				{
					cout << "��� ������� ����";
					system("pause");
					return;
				}
				//������ ���������� ����
				for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
				{
					if (j % 3 == 0 && j != 0)
						cout << "\t";//������ ��� ����������
					if (j % 6 == 0 && j != 0)
						cout << endl;
					if (local_plane.free_places.find(i) != local_plane.free_places.end())
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
				if (local_plane.occupied_places.size() == 0)
				{
					cout << "��� ������� ����";
					return;
				}
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
					if (local_plane.free_places.find(i) != local_plane.free_places.end())
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

				case 13://Enter
					if (local_plane.free_places.find(realplace) != local_plane.free_places.end())
					{
						num_of_place = 0;
						break;
					}
					else
					{
						passenger tourist = local_plane.list_of_passangers[realplace - 1];
						cout << "\n���: " << tourist.name;
						cout << "\n�������: " << tourist.surname;
						cout << "\n�������: " << tourist.age;
						num_of_place = 1;
						system("pause");
					}

				}
				position_checking(Row, Colunm, realplace, local_plane);

			}
			//��������� ����� �� ������� ����

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
		cout << "� ����� ��� �������� ��������" << endl;
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
		planes(aircraft_base, flag);//����� ��������� ��������
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

			system("cls");

			int j = 0;
			if (local_plane.plane_type == "Airbus")
			{
				if (local_plane.occupied_places.size() == 0)
				{
					cout << "��� ������� ����"<<endl;
					system("pause");
					return;
				}
				//������ ���������� ����
				for (int i = 1; i <= (local_plane.free_places.size() + local_plane.occupied_places.size()); i++)
				{
					if (j % 3 == 0 && j != 0)
						cout << "\t";//������ ��� ����������
					if (j % 6 == 0 && j != 0)
						cout << endl;
					if (local_plane.free_places.find(i) != local_plane.free_places.end())
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
				if (local_plane.occupied_places.size() == 0)
				{
					cout << "��� ������� ����";
					return;
				}
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
					if (local_plane.free_places.find(i) != local_plane.free_places.end())
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

				case 13://Enter
					if (local_plane.free_places.find(realplace) != local_plane.free_places.end())
					{
						num_of_place = 0;
						break;
					}
					else
					{
						local_plane.list_of_passangers.erase(local_plane.list_of_passangers.begin() + realplace - 1);
						local_plane.free_places.insert(realplace);//��������� ��������� ����� � ������ ��������� ������
						local_plane.occupied_places.erase(realplace);//������� ������� ����� �� ������ �������
						aircraft_base[ActiveMenuItem - 1] = local_plane;
						num_of_place = 1;
						break;
					}

				}
				position_checking(Row, Colunm, realplace, local_plane);

			}
			//��������� ����� �� ������� ����

		}
		if (ActiveMenuItem < 1) ActiveMenuItem = 1;
		if (ActiveMenuItem > size_of_park + 1) ActiveMenuItem = size_of_park + 1;
	}//while
}

int main()
{
	setlocale(LC_ALL ,"Russian");//���������� ������� ����

	vector<plane> aircraft_base;//������ ������ ��� �������� ��������
	//��������������� ����������
	int exit = 1;
	int ActiveMenuItem = 3;
	int ch = 0;

	//���������� �������
	while(exit != 0)
	{
		system("cls");
		cout << "\n\t������� ���������� ���������" << endl;
		cout << "\n 1. �������� ������";
		cout << "\n 2. C������ ������������";
		cout << "\n 3. ���������������� �������� �� ����";
		cout << "\n 4. ����������� ������� �����";
		cout << "\n 5. �������� ����������� ���������";
		cout << "\n 0. �����" << endl;
		//cout << "\n  "
		cout << "\n ������� ����� ������ ����, ��������� ��������� ����������. ��� �������� �� ������ ������� Enter";

		

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
		//����������� �� ������� ������� ����
		if (ActiveMenuItem < 3) ActiveMenuItem = 3;
		if (ActiveMenuItem > 8) ActiveMenuItem = 8;
	}

	return 0;

}