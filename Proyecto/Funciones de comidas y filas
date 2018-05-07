void ComeFichas(jugador, tablero)
{
	int x, int y; //variables del tablero
	var jugador=j; //j será el jugador en turno

	//valida a la derecha
	if(x<=17)
	{	
		if(casilla!="vacio" && casilla==j){
			x++;
			if(casilla!="vacio" && casilla!=j)
			{
				x++;
				if(casilla!="vacio" && casilla!=j)
				{
					x++;
					if(casilla!="vacio" && casilla==j)
					{
						j.comidas+2;
						x--;
						casilla=vacio;
						x--;
						casilla=vacio;
					}
				}
			}
		}
	}

	//valida diagonal abajo derecha
	if(x<=17 && y<=17)
	{
		if(casilla!="vacio" && casilla==j)
		{
			x++; 
			y++;
			if(casilla!="vacio" && casilla!=j)
			{
				x++;
				y++;
				if(casilla!="vacio" && casilla!=j)
				{
					x++;
					y++;
					if(casilla!="vacio" && casilla==j)
					{
						j.comidas+2;
						x--;
						casilla=vacia;
						x--;
						casilla=vacia;
					}
				}
			}
		}
	}

	//valida abajo
	if(y<=17)
	{
		if(casilla!="vacio" && casilla==j)
		{
			y++;
			if(casilla!="vacio" && casilla!=j)
			{
				y++;
				if(casilla!="vacio" && casilla==j)
				{
					y++;
					if(casilla!="vacio" && casilla!=j)
					{
						j.comidas+2;
						y--;
						casilla=vacia;
						y--;
						casilla=vacia;
					}
				}
			}
		}
	}

	//valida diagonal abajo izquierda
	if(x<=3 && y<=17)
	{
		if(casilla!="vacio" && casilla==j)
		{
			x--; 
			y++;
			if(casilla!="vacio" && casilla!=j)
			{
				x--;
				y++;
				if(casilla!="vacio" && casilla!=j)
				{
					x--;
					y++;
					if(casilla!="vacio" && casilla==j)
					{
						j.comidas+2;
						x--;
						casilla=vacia;
						x--;
						casilla=vacia;
					}
				}
			}
		}
	}
}


void FilasDe4(jugador, tablero)
{
	int x, y, i; //variables del tablero
	var jugador=j; //j será el jugador en turno

	//valida derecha
	if(x<=17)
	{
		while(casilla!="vacio" && casilla==j && i<=3)
		{
			i++;
			x++;
		}
		if(i==3)
		{
			j.filas=j.filas++;
		}
	}

	//valida diagonal derecha
	if(x<=17 && y<=17)
	{
		while(casilla!="vacio" && casilla==j && i<=3)
		{
			i++;
			x++;
			y++;
		}
		if(i==3)
		{
			j.filas=j.filas++;
		}
	}

	//valida abajo
	if(y<=17)
	{
		while(casilla!="vacio" && casilla==j && i<=3)
		{
			i++;
			y++;
		}
		if(i==3)
		{
			j.filas=j.filas++;
		}
	}

	//valida diagonal derecha abajo
	if(x>3 && y<=17)
	{
		while(casilla!="vacio" && casilla==j && i<=3)
		{
			i++;
			x--;
			y++;
		}
		if(i==3)
		{
			j.filas=j.filas++;
		}
	}
}
