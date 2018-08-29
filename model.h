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
#include <sqlite3.h> //para poder usar tipos de sqlite como por ejemplo sqlite3_stmt
#define BASEDATOS "rent.db" //Aqui definimos el nombre del archivo de la base de datos
#define IDCLIENTE "Idcliente"
#define IDPROVEEDOR "Idproveedor"
#define CNIF "cnif"
#define NOMBRE1 "nombre1"
#define NOMBRE2 "nombre2"
#define DOMICILIO "domicilio"
#define CP "cp"
#define CIUDAD "ciudad"
#define TELEFONO1 "telefono1"
#define TELEFONO2 "telefono2"
#define EMAIL "email"
#define OBSERVACIONES "observaciones" 

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

/*Este vector lleva marcado los campos de la tabla que seran campos en el SELECT de personas (clientes o proveedores)
El orden es: Idproveedor/Idcliente, cnif, nombre1, nombre2, domicilio, cp, ciudad, telefono1, telefono2, email, observaciones*/
typedef gboolean tipo_vectorpersona[11];

/*--Revisa si existe el archivo de la Bd en el lugar correspondiente--*/
gboolean 
ExisteBd(const gchar *bd_nombre);

/*--Comprueba que no hay errores en la consulta--*/
gboolean 
ConsultaOk(guint resultado_consulta);

/*--Devuelve verdadero si ha podido abrir la base de datos--*/
gboolean 
ConectarBd(const gchar *bd_nombre);

/*--Procedimiento que solicita los valores a insertar el argumento TipoDePersona puede ser proveedor o cliente--*/
void 
CrearPersona(gchar *TipoDePersona);

/*--Inserta los valores en la tabla proveedor o en la tabla cliente recogidos previamente --*/
void 
InsertarPersona(tipo_persona persona);

/*--Inicializa vectorpersona a todos FALSE o a todos TRUE--*/
void 
InicializarVectorPersona(tipo_vectorpersona vectorpersona, 
							  gboolean valor);

/*--Procedimiento que interpreta el vector persona, lee persona y tipo de consulta --*/
void 
InterpretarVectorPersona (GString *consulta, 
						  tipo_vectorpersona vectorpersona, 
						  const gchar *TipoDePersona);

/*--Procedimiento para mostrar TODAS las personaS--*/
void 
MostrarPersonas(gchar *TipoDePersona, 
			    tipo_vectorpersona vectorpersona);

void 
ImprimirPersonas(tipo_vectorpersona vectorpersona, sqlite3_stmt *res);

/*--Procedimiento que solicita los datos para la persona a buscar --*/
void 
PreguntarBuscarPersonas(gchar *TipoDePersona);

/*--Procedimiento para mostrar persona/s buscada/s , vectorpersona para senyalar campos a buscar--*/
void 
MostrarBuscarPersonas(gchar *TipoDePersona,
                      gchar *cadenaabuscar, 
                      gchar *campobusqueda,
			   		  tipo_vectorpersona vectorpersona);

//PENDIENTES:
//guint CrearCompra(guint fecha, guint Idproveedor);
//int CrearCompra(int fecha, int Idproveedor);
//El IdCompra es obtenido despues de ejecutar CrearCompra(...);
////void ComprarArticulo(int IdArticulo, int IdCompra, float preciocoste, int unidades);


