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
#include "model.h"
#include "cuestiones.h"
#include <stdio.h>
#include <glib/gprintf.h>
#include <glib.h>

int main() {

	//TODO Hacer usar argp.h y crear las funciones para recoger argumentos (Por Ejemplo cargar otra Bd) y 
	//mostrar --help ... 
	gchar *tecla; //tecla sera un string para evitar que al insertar demasiados caracteres desborde
	gchar *TipoDePersona;

	TipoDePersona = g_malloc(10);

	tipo_vectorpersona vectorpersona;

	for (int a=0; a < 12 ; a++) {
		vectorpersona[a] = FALSE;


	}
	//vectorpersona[0] = TRUE;
	//vectorpersona[1] = TRUE;
	vectorpersona[1] = TRUE;
	//vectorpersona[2] = TRUE;
	vectorpersona[4] = TRUE;
	//vectorpersona[6] = TRUE;


	tecla = g_malloc(3);
	//tmp = g_malloc(3);
	if (ConectarBd(BASEDATOS) == FALSE) {
		return -1;
	}
	do {
		//g_printf("\033c");
		g_printf("SELECCIONE UNA OPCION\n");
		g_printf("1-Para Insertar un Cliente\n");
		g_printf("2-Para Ver Clientes\n");
		//g_printf("3-Para Borrar un Cliente\n");

		g_printf("4-Para Insertar un Proveedor\n");
		g_printf("5-Para Ver Proveedores\n");
		//g_printf("6-Para Borrar un Proveedor\n");

		g_printf("7-Para SALIR\n");

		//fgets (&tecla, 3, stdin);
		fgets(tecla, 4, stdin);
		//fgets(TextoReducido(1, tecla), 3, stdin);
	//	fflush(stdin);

		LimpiarTexto(tecla);

		//g_stpcpy(TipoDePersona, TextoReducido(1, tecla));
		//ReducirTexto0(1, tecla);
		//LimpiarTexto(tecla);
		//g_printf("TECLA:%c",TextoReducido(tecla));
		//g_printf("Es la tecla %s\n",tecla);
//		g_stpcpy (tmp,TextoReducido(tecla));
				//g_stpcpy (tmp,tecla);
		//tmp = TextoReducido(tecla);
		//g_strndup (tecla, 2);
//g_printf("Es la tecla %s\n",tecla);
//g_printf("Es la tecla %s\n",tecla);

//g_printf("el tamanyo del string es %d\n", (guint)strlen(tecla));
		if ((g_strcmp0 (tecla, "1")) == 0) {
		//if (tecla == '1') {
			//g_printf("\033c");
			g_stpcpy(TipoDePersona, "CLIENTE");
			CrearPersona(TipoDePersona);
		}
		if ((g_strcmp0 (tecla, "2")) == 0) {
		//if (tecla == '1') {
			//g_printf("\033c");
			g_stpcpy(TipoDePersona, "CLIENTE");
			MostrarPersonas(TipoDePersona, vectorpersona);
		}
		if ((g_strcmp0 (tecla, "4")) == 0) {
 		//if (tecla == '2') {
 			//g_printf("\033c");
			g_stpcpy(TipoDePersona, "PROVEEDOR");
			CrearPersona(TipoDePersona);
		}
		if ((g_strcmp0 (tecla, "5")) == 0) {
		//if (tecla == '1') {
			//g_printf("\033c");
			g_stpcpy(TipoDePersona, "PROVEEDOR");
			MostrarPersonas(TipoDePersona, vectorpersona);
		}

	} while ( g_strcmp0 (tecla, "7") != 0 );
		/*Liberamos variables dinamicas*/
		g_free(TipoDePersona);
		g_free(tecla);
		g_printf("Adeus...\n");
}
