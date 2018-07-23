/*
* AUTOR: BarTOLOme Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Julio del 2018
*
* Programa destinado para un alquiler de videojuegos
* 	Usa Glib y Sqlite
*	Es en modo texto
*
* Implementacion de los prototipos
* Archivo: model.c
*
*/
#include <sqlite3.h>
#include "model.h"
#include "cuestiones.h"
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h> //para usar g_access

gboolean ExisteBd(const gchar *bd_nombre) {
	if( g_access( bd_nombre, 0 ) == -1 ) {
		//F_OK vale 0 por lo tanto en g_access para no tener que cargar unistd.h pondremos directamente 0
		return TRUE;
	} else {
		return FALSE;
	}
}

gboolean ConsultaOk(guint resultado_consulta) {
	if (resultado_consulta != SQLITE_OK)
  	{
		return FALSE;
  	} else {
      		return TRUE;
  	}
}

gboolean ConectarBd(const gchar *bd_nombre) {
	//puntero a la base de datos
	sqlite3 *db;
	gboolean resultado_consulta ;

	g_fprintf(stdout,"GRent: ");
	//comprobamos que el archivo con el nombre dado (bd_nombre) existe
	if (ExisteBd(bd_nombre)  == TRUE ) {
		g_print ("La base de datos %s no existe\n",bd_nombre);
		return FALSE;
	}
	resultado_consulta = sqlite3_open (bd_nombre, &db);
	if (ConsultaOk(resultado_consulta) == TRUE) {
		g_print ("OK %d\n", resultado_consulta);
		return TRUE;
	} else {
		g_print ("SQL error: %d\n", resultado_consulta);
		return FALSE;	
	}
}

void CrearPersona(gchar *TipoDePersona) {
	/*Definen si el primer nombre es el nombre comercial de la empresa o nombre cliente
	,nombre fiscal de empresa o apellidos del cliente*/
	gchar *tipoDeNombre1;
	gchar *tipoDeNombre2;

	/*Variables usadas para la recogida de valores*/
	gchar *temp ;
	guint tempn ;
	guint limite ;

	tipo_persona persona;
	
	tipoDeNombre1 = g_malloc(17);
	tipoDeNombre2 = g_malloc(14);
	temp = g_malloc(100);	

	limite = 50;

	/*TipoDePersona es un CLIENTE o un PROVEEDOR*/
	persona.TipoDePersona = TipoDePersona;

	if (( g_strcmp0 (persona.TipoDePersona, "PROVEEDOR")) == 0) {
		g_stpcpy(tipoDeNombre1, "Nombre comercial");
		g_stpcpy(tipoDeNombre2,"Nombre fiscal");
	} 

	if ((g_strcmp0 (persona.TipoDePersona, "CLIENTE")) == 0){
		g_stpcpy(tipoDeNombre1,"Nombre");
		g_stpcpy(tipoDeNombre2,"Apellidos");
	}
	
	g_print ("Introduce los datos para un nuevo %s\n", persona.TipoDePersona);

	do {
		g_print ("%s:\n", tipoDeNombre1);
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.nombre1 = g_string_new (temp);

	do {
		g_print ("%s:\n", tipoDeNombre2);
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.nombre2 = g_string_new (temp);

	do {
		g_printf ("Cif o Nif\n");
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.cnif = g_string_new (temp);

	do {
		g_printf ("Domicilio\n");
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.domicilio = g_string_new (temp);

	do {
		g_printf ("Codigo postal\n");
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.cp = g_string_new (temp);

	do {
		g_printf ("Ciudad\n");
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.ciudad = g_string_new (temp);

	/*Aunque telefono se guarde como TEXT en la BD 
	hasta la hora de insertar sera usado como integer*/
	do {
		g_printf ("Telefono: \n");
		fgets (temp, 12, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	tempn = atoi(temp);
	persona.telefono1 = tempn;

	do {
		g_printf ("Segundo telefono: \n");
		fgets (temp, 12, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	tempn = atoi(temp);
	persona.telefono2 = tempn;

	do {
		g_printf ("Correo electronico\n");
		fgets (temp, 100, stdin);
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.email = g_string_new (temp);

	do {
		g_printf ("Observaciones\n");
		fgets (temp, 100, stdin); 
	} while (strlen(temp) > limite);
	LimpiarTexto(temp);
	persona.observaciones = g_string_new (temp);

	//g_printf("\033c"); //Comentado por ahora
	/*Muestra los resultados antes de realizar el Insert*/
	g_printf ("Datos introducidos para un %s\n", persona.TipoDePersona);
	g_printf ("%s :%s\n", tipoDeNombre1, persona.nombre1->str);
	g_printf ("%s :%s\n", tipoDeNombre2, persona.nombre2->str);
	g_printf ("CIF o NIF: %s\n", persona.cnif->str);
	g_printf ("Domicilio: %s\n", persona.domicilio->str);
	g_printf ("Codigo Postal: %s\n", persona.cp->str);
	g_printf ("Ciudad: %s\n", persona.ciudad->str);
	g_printf ("Telefono: %d\n", persona.telefono1);
	g_printf ("Segundo telefono: %d\n", persona.telefono2);
	g_printf ("Email: %s\n", persona.email->str);
	g_printf ("Observaciones: %s\n", persona.observaciones->str);
	
	g_printf ("Pulse ENTER para continuar");
	fgets (temp, 100, stdin);
	//g_printf("\033c"); //Comentado por ahora

	/*<------Aqui inserta los datos en la BD---->*/
	InsertarPersona(persona);
	/*<------fin insestar----------------------->*/

	/*Liberamos las variables dinamicas*/
	g_free(temp);
	g_free(tipoDeNombre1);
	g_free(tipoDeNombre2);
	g_string_free (persona.nombre1, TRUE);
    g_string_free (persona.nombre2, TRUE);
	g_string_free (persona.cnif, TRUE);
	g_string_free (persona.domicilio, TRUE);
	g_string_free (persona.cp, TRUE);
	g_string_free (persona.ciudad, TRUE);
	g_string_free (persona.email, TRUE);
	g_string_free (persona.observaciones, TRUE);
}

void InsertarPersona(tipo_persona persona) {
	gchar *tipoDeConsulta;
	gchar *temp;
	GString *consulta;
   
	tipoDeConsulta = g_malloc(14);
	temp = g_malloc(14);

	g_stpcpy(tipoDeConsulta, "INSERT INTO ");
	consulta = g_string_new (tipoDeConsulta);
	g_string_append (consulta, persona.TipoDePersona);
	g_string_append (consulta, " (cnif, nombre1, nombre2, domicilio, cp, ciudad, telefono1, telefono2, email, observaciones) ");
	g_string_append (consulta, " VALUES ('");

	g_string_append (consulta, persona.cnif->str);
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.nombre1->str);
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.nombre2->str);
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.domicilio->str);
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.cp->str);
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.ciudad->str);
	g_string_append (consulta, "', '");

	g_sprintf(temp,"%d', '%d",persona.telefono1, persona.telefono2);
	g_string_append (consulta, temp);
	
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.email->str);
	g_string_append (consulta, "', '");
	g_string_append (consulta, persona.observaciones->str);
	g_string_append (consulta, "') ;");

	g_printf("%s\n",consulta->str);

    sqlite3 *db;
    gchar *err_msg = 0;  
    gint rc = sqlite3_open("rent.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    rc = sqlite3_exec(db, consulta->str, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);

    } 
    
    sqlite3_close(db);
    //Liberamos variables dinamicas
    g_free(temp);
    g_free(tipoDeConsulta);
    g_string_free(consulta, TRUE);

}
