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

//#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
//#include <glib.h>
#include <glib/gprintf.h>
//#include <glib/gstdio.h> //para usar g_access
//#include <unistd.h> //para usar la funcion access que comprueba si un archivo existe
#include "cuestiones.h"

void LimpiarTexto(gchar *cadena) {
	gchar *p;
	p = strchr (cadena, '\n');
	if (p) {
		*p = '\0';
	}
}
void MensageError(void) {
		g_fprintf(stdout,"GRent Error: ");
}

/* char TextoReducido al primer miembro del string {*/
 char TextoReducido0(gchar *cadena) {
	//LimpiarTexto(cadena);
	//g_printf("Esta es la cadena: %c\n", cadena[0]);
	return cadena[0];
}


void ReducirTexto(guint n, gchar *cadena) {
	for (int i = 0 ; i < strlen(cadena); i++) {
		g_printf("Estos son los caracteres %c\n", cadena[i]);
	}
}

