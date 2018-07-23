/*
* AUTOR: BarTOLOme Vich Lozano
* EMAIL: amadews23@hotmail.com 
* FECHA: Julio del 2018
*
* Programa destinado para un alquiler de videojuegos
* 	Usa Glib y Sqlite
*	Es en modo texto
*
* Funcion main
*
*/
#include <stdlib.h>
#include "model.h"
#include "cuestiones.h"
#include <stdio.h>
#include <glib/gprintf.h>
#include <glib.h>

int main() {

	gchar *tecla; //tecla sera un string para evitar que al insertar demasiados caracteres se copie en el siguiente fgets
	gchar *TipoDePersona;
	TipoDePersona = g_malloc(10);
	tecla = g_malloc(3);
  
	if (ConectarBd("rent.db") == FALSE) {
		return -1;
	}
	do {
		//g_printf("\033c");
		g_printf("SELECCIONE UNA OPCION\n");
		g_printf("1-Para Insertar un Cliente\n");
		g_printf("2-Para Insertar un Proveedor\n");
		g_printf("5-Para SALIR\n");

		fgets(tecla, 4, stdin);
		LimpiarTexto(tecla);

		if ((g_strcmp0 (tecla, "1")) == 0) {

			g_stpcpy(TipoDePersona, "CLIENTE");
			CrearPersona(TipoDePersona);
		}
		if ((g_strcmp0 (tecla, "2")) == 0) {

			g_stpcpy(TipoDePersona, "PROVEEDOR");
			CrearPersona(TipoDePersona);
		}

	} while ( g_strcmp0 (tecla, "5") != 0 );
		/*Liberamos variable dinamica*/
		g_free(TipoDePersona);
		g_free(tecla);
		g_printf("Adews...\n");
}

