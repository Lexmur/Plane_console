#include "plane_console_functios.h"

int main()
{
	setlocale(LC_ALL ,"Russian");//���������� ������� ����
	int size_of_park = 0; //������ ������� ����� ��������
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
		//����������� �� ������� ������� ����
		if (ActiveMenuItem < 3) ActiveMenuItem = 3;
		if (ActiveMenuItem > 8) ActiveMenuItem = 8;
	}
	return 0;
}