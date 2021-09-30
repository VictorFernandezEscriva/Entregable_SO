#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char nombre[10];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi\uffc3\uffb3n: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi\uffc3\uffb3n: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	printf ("Dame el nombre de la persona que quieres buscar\n");
	scanf ("%s", nombre);
	strcpy (consulta,"SELECT COUNT(Participacion.Posicion) FROM Jugador,Participacion WHERE Jugador.Nombre = '");
	strcat (consulta, nombre);
	strcat (consulta,"'AND Jugador.Id = Participacion.Id_J AND Participacion.Posicion = 1");
	
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf ("Nombre victorias: %s\n", row[0] );
	mysql_close (conn);
	exit(0);
	
}
