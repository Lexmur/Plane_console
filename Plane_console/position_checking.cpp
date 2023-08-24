#include "plane_console_functios.h"


void position_checking(int& Row, int& Colunm, int& realplace, const plane& local_plane)
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