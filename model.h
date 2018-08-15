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
#define BASEDATOS "rent.db" //Aqui definimos el nombre del archivo de la base de datos

/* tipo_persona .Es un tipo generico para un cliente o proveedor (persona juridica).
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

/*En este vector abierto copiaremos todos las filas de la tabla*/
//typedef tipo_persona tipo_vectorpersonas[];
//typedef struct {
//	gchar *tcnif;
//	gchar *tnombre1;
//	gchar *tnombre2;
//	gchar *tdomicilio;
//	gchar *tcpl; //le anyado una l para que no se parezca el nombre al protocolo tcp, por si acaso!
//	gchar *tciudad;
//	gchar *ttelefono2;
//	gchar *temail;
//	gchar *tobservaciones;
	//gchar *tTipoDePersona; //PROVEEDOR o CLIENTE
//} tipo_camposPersona;

/*Este vector lleva marcado los campos de la tabla que seran marcos en el SELECT de personas (clientes o proveedores)
El orden es: Idproveedor/Idcliente, cnif, nombre1, nombre2, domicilio, cp, ciudad, telefono1, telefono2, email, observaciones*/
typedef gboolean tipo_vectorpersona[11];

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

/*--Procedimiento para mostrar personas--*/
void MostrarPersonas(gchar *TipoDePersona, tipo_vectorpersona vectorpersona);


//
guint CrearCompra(guint fecha, guint Idproveedor);
//int CrearCompra(int fecha, int Idproveedor);
//El IdCompra es obtenido despues de ejecutar CrearCompra(...);
void ComprarArticulo(guint IdVideojuego, guint IdCompra, gfloat preciocoste, guint unidades);
//void ComprarArticulo(int IdArticulo, int IdCompra, float preciocoste, int unidades);


