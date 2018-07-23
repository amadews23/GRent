/*
* AUTOR: BarTOLOme Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Julio del 2018
*
* Programa para un alquiler de videojuegos
* 	Usa Glib y Sqlite
*	Es en modo texto
*
* Prototipos y tipos de datos para conectar a la base de datos
* Archivo: model.h
*
*/
#pragma once
#include <glib.h> //incluiremos glib.h para permitir declarar tipos de datos, objetos y estructuras de glib

/*Es un tipo generico (tipo_persona) para un cliente o proveedor (persona juridica).
 Damos por hecho que un proveedor puede ser una sociedad pero un cliente que alquile videojuegos no tiene sentido*/
typedef struct {
	GString *cnif;
	GString *nombre1;
	GString *nombre2;
	GString *domicilio;
	GString *cp;
	GString *ciudad;
	guint telefono1;
	guint telefono2;
	GString *email;
	GString *observaciones;
	gchar *TipoDePersona; //PROVEEDOR o CLIENTE
} tipo_persona;

/*--Revisa si existe el archivo de la Bd en el lugar correspondiente--*/
gboolean ExisteBd(const gchar *bd_nombre);
/*--Comprueba que no hay errores en la consulta--*/
gboolean ConsultaOk(guint resultado_consulta);
/*--Devuelve verdadero si ha podido abrir la base de datos--*/
gboolean ConectarBd(const gchar *bd_nombre);
/*--Procedimiento que solicita los valores a insertar el argumento TipoDePersona puede ser proveedor o cliente--*/
void CrearPersona(gchar *TipoDePersona);
/*--Inserta los valores en la tabla proveedor o en la tabla cliente recogidos previamente --*/
void InsertarPersona(tipo_persona persona);
