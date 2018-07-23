/*
* AUTOR: BarTOLOme Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Julio del 2018
*
* Programa para un alquiler de videojuegos
* 	Usa Glib y Sqlite
*	Es en modo texto
*
* Implementacion de los prototipos para el manejo de cadenas
* Archivo: cuestiones.c
*
*/
#include <string.h>
#include "cuestiones.h"

void LimpiarTexto(gchar *cadena) {
	gchar *p;
	p = strchr (cadena, '\n');
	if (p) {
		*p = '\0';
	}
}
