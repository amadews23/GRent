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
//#include <stdio.h>
#include <sqlite3.h>
#include "model.h"
#include "cuestiones.h"
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h> //para usar g_access

//#include <unistd.h> //para usar la funcion access que comprueba si un archivo existe

//#include <string.h>
sqlite3 *db;


gboolean 
ExisteBd(const gchar *bd_nombre)
{
	if( g_access( bd_nombre, 0 ) == -1 ) {
		//F_OK vale 0 por lo tanto en g_access para no tener que cargar unistd.h pondremos directamente 0
		//if( access( bd_nombre, F_OK ) != -1 ) {
		// file doesn't exist
		//al provocar la salida del programa NO nos creara el archivo de la base de datos vacio
		return TRUE;
	} else {
		return FALSE;
	}
}

gboolean 
ConsultaOk(guint resultado_consulta)
{
	if (resultado_consulta != SQLITE_OK)
  	{
		return FALSE;
  	} else {
      		return TRUE;
  	}
}

gboolean 
ConectarBd(const gchar *bd_nombre)
{
	//puntero a la base de datos
	//?LIBERAR

	//PENDIENTE sqlite3_stmt *res;
	gboolean resultado_consulta ;

	//g_fprintf(stdout,"GRent: ");
	//comprobamos que el archivo con el nombre dado (bd_nombre) existe
	if (ExisteBd(bd_nombre)  == TRUE ) {
		MensageError();
		g_print ("La base de datos %s no existe\n",bd_nombre);
		return FALSE;
	}
	resultado_consulta = sqlite3_open (bd_nombre, &db);
	if (ConsultaOk(resultado_consulta) == TRUE) {
		g_print ("OK %d\n", resultado_consulta);
		return TRUE;
	} else {
		MensageError();
		g_print ("SQL error: %d\n", resultado_consulta);
		return FALSE;	
	}
}

void 
CrearPersona(gchar *TipoDePersona)
{
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
	//g_stpcpy(persona.TipoDePersona, TipoDePersona);

	if (( g_strcmp0 (persona.TipoDePersona, "PROVEEDOR")) == 0) {
		g_stpcpy(tipoDeNombre1, "Nombre comercial");
		g_stpcpy(tipoDeNombre2,"Nombre fiscal");
	} 

	if ((g_strcmp0 (persona.TipoDePersona, "CLIENTE")) == 0){
		g_stpcpy(tipoDeNombre1,"Nombre");
		g_stpcpy(tipoDeNombre2,"Apellidos");
	}
	
	//g_fprintf(stdout,"Introduce:-> ");
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

	/*TODO crear funcion que detecte letras en la entrada del tel y las elimine antes de convertir a int*/
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

	/*<------Aqui Insertar los datos en la BD---->*/
	InsertarPersona(persona);
	/*<------FIN Insertar----------------------->*/

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

void 
InsertarPersona(tipo_persona persona)
{
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

	/*g_printf("%s\n",consulta->str);*/ //Para ver la consulta que realizarA

    gchar *err_msg = 0;  
    gint rc = sqlite3_open(BASEDATOS, &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
     
    }
    rc = sqlite3_exec(db, consulta->str, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
       	MensageError();
		g_printf("(code:%d)\n ", rc);

        if (rc == 19) {
        	g_printf("El NIF o CIF estA duplicado (code:%d)\n ", rc);
        }
        sqlite3_free(err_msg);        
        sqlite3_close(db);
    } 
    sqlite3_close(db);
    /*Liberamos variables dinamicas*/
    g_free(temp);
    g_free(tipoDeConsulta);
    g_string_free(consulta, TRUE);
}

void 
InicializarVectorPersona(tipo_vectorpersona vectorpersona, 
							  gboolean valor) 
{
		for (int a=0; a < 12 ; a++) {
			vectorpersona[a] = valor;
		}
}

void 
InterpretarVectorPersona (GString *consulta, 
						  tipo_vectorpersona vectorpersona, 
						  const gchar *TipoDePersona) 
{

	if (vectorpersona[0] == TRUE ) { 
		if ( g_strcmp0 (TipoDePersona, "CLIENTE") == 0 ) 	{
			g_string_append (consulta, IDCLIENTE);
		}
		if ( g_strcmp0 (TipoDePersona, "PROVEEDOR") == 0 ) 	{
			g_string_append (consulta, IDPROVEEDOR);	
		}
	}
 
 	if (vectorpersona[1] == TRUE) {
 		if (vectorpersona[0] == TRUE) {
 			g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, CNIF);
 	}
		
 	if (vectorpersona[2] == TRUE) {
 		if (vectorpersona[1] == TRUE || vectorpersona[0] == TRUE) {
 			g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, NOMBRE1);
 	}
 	 	if (vectorpersona[3] == TRUE) {
		for (int a= 0; a < 3; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, NOMBRE2);			
	}

 	if (vectorpersona[4] == TRUE) {
		for (int a= 0; a < 4; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, DOMICILIO);
	} 	
 	if (vectorpersona[5] == TRUE) {
		for (int a= 0; a < 5; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, CP);
 	}
 	if (vectorpersona[6] == TRUE) {
		for (int a= 0; a < 6; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, CIUDAD);
 	}
 	if (vectorpersona[7] == TRUE) {
		for (int a= 0; a < 7; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, TELEFONO1);
 	}

 	if (vectorpersona[8] == TRUE) {
		for (int a= 0; a < 8; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, TELEFONO2);
 	}

 	if (vectorpersona[9] == TRUE) {
		for (int a= 0; a < 9; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, EMAIL);
 	}

 	if (vectorpersona[10] == TRUE) {
		for (int a= 0; a < 10; a++) {
			if (vectorpersona[a] == TRUE) {
				g_string_append (consulta, ",");
				break;
			}
		}
 		g_string_append (consulta, OBSERVACIONES);
 	}
	/*
 	if (vectorpersona[3] == TRUE) {
 		if (vectorpersona[2] == TRUE || vectorpersona[1] == TRUE || 
 			vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, NOMBRE2);
 	}

 	if (vectorpersona[4] == TRUE) {
 		if (vectorpersona[3] == TRUE || vectorpersona[2] == TRUE || 
 			vectorpersona[1] == TRUE || vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, DOMICILIO);
 	}

 	if (vectorpersona[5] == TRUE) {
 		if (vectorpersona[4] == TRUE || vectorpersona[3] == TRUE ||
 		 	vectorpersona[2] == TRUE || vectorpersona[1] == TRUE || 
 		 	vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, CP);
 	}

 	if (vectorpersona[6] == TRUE) {
 		if (vectorpersona[5] == TRUE || vectorpersona[4] == TRUE || 
 			vectorpersona[3] == TRUE || vectorpersona[2] == TRUE || 
 			vectorpersona[1] == TRUE || vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, CIUDAD);
 	}

 	if (vectorpersona[7] == TRUE) {
 		if (vectorpersona[6] == TRUE || vectorpersona[5] == TRUE || 
 			vectorpersona[4] == TRUE || vectorpersona[3] == TRUE || 
 			vectorpersona[2] == TRUE || vectorpersona[1] == TRUE || 
 			vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, TELEFONO1);
 	}

 	if (vectorpersona[8] == TRUE) {
 		if (vectorpersona[7] == TRUE || vectorpersona[6] == TRUE || 
 			vectorpersona[5] == TRUE || vectorpersona[4] == TRUE ||
 			vectorpersona[3] == TRUE || vectorpersona[2] == TRUE ||
 			vectorpersona[1] == TRUE || vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, TELEFONO2);
 	}

 	if (vectorpersona[9] == TRUE) {
 		if (vectorpersona[8] == TRUE || 
 			vectorpersona[7] == TRUE || vectorpersona[6] == TRUE || 
 			vectorpersona[5] == TRUE || vectorpersona[4] == TRUE || 
 			vectorpersona[3] == TRUE || vectorpersona[2] == TRUE || 
 			vectorpersona[1] == TRUE || vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, EMAIL);
 	}

 	if (vectorpersona[10] == TRUE) {
 		if (vectorpersona[9] == TRUE || vectorpersona[8] == TRUE || 
 			vectorpersona[7] == TRUE || vectorpersona[6] == TRUE || 
 			vectorpersona[5] == TRUE || vectorpersona[4] == TRUE || 
 			vectorpersona[3] == TRUE || vectorpersona[2] == TRUE || 
 			vectorpersona[1] == TRUE || vectorpersona[0] == TRUE ) {
 				g_string_append (consulta, ",");	
 		} 
 		g_string_append (consulta, OBSERVACIONES);
 	}
	*/

	g_string_append (consulta, " FROM ");
	g_string_append (consulta, TipoDePersona);


	//**
}

void 
ImprimirPersonas(tipo_vectorpersona vectorpersona, 
				sqlite3_stmt *res) 
{

    guint maxcamp = 0; //usada para definir la maxima posicion de los "campos a mostrar"
    guint b = 0; //un indice para la hora de "mostrar los campos"

	/*Comprobamos el numero maximo de campos a mostrar (maxcamp)*/
    for (int a=0; a < 11; a++) {
    	if (vectorpersona[a] == TRUE) {
    		maxcamp++;
    	} 
    }
    while (sqlite3_step (res) == SQLITE_ROW) {
    	for (int a=0 ; a < 11; a++) {
        	if (vectorpersona[a] == TRUE) {
        		b = 0;
        		while(b < maxcamp) {
        			g_printf(" %s ", sqlite3_column_text(res, b));
        			b++;
        		} 
        	break;       		
    		}
    	}	
		g_printf("\n");
	} 
}

void 
ImprimirPersonasV2(tipo_vectorpersona vectorpersona, 
				sqlite3_stmt *res,
				guint maxresultxpag) 
{

    guint maxcamp = 0; //usada para definir la maxima posicion de los "campos a mostrar"
    guint b = 0; //un indice para la hora de "mostrar los campos"
    guint c = 0;
	/*Comprobamos el numero maximo de campos a mostrar (maxcamp)*/
    for (int a=0; a < 11; a++) {
    	if (vectorpersona[a] == TRUE) {
    		maxcamp++;
    	} 
    }
    while ((sqlite3_step (res) == SQLITE_ROW) && (c < maxresultxpag)) {
    	c++;
    	for (int a=0 ; a < 11; a++) {
        	if (vectorpersona[a] == TRUE) {
        		b = 0;
        		while(b < maxcamp) {
        			g_printf(" %s ", sqlite3_column_text(res, b));
        			b++;
        		} 
        	break;       		
    	
    		}

    	}

		g_printf("\n");
	} 
}

void 
MostrarPersonas(gchar *TipoDePersona, 
				tipo_vectorpersona vectorpersona ) 
{
	gchar *tipoDeConsulta;
	//gchar *temp;
	GString *consulta;

	tipoDeConsulta = g_malloc(8);
	//temp = g_malloc(14);
    sqlite3_stmt *res;
    gchar *err_msg = 0;  
    gint rc = sqlite3_open(BASEDATOS, &db);

    /*Copiamos al GString llamado consulta*/
	g_stpcpy(tipoDeConsulta, "SELECT ");
	consulta = g_string_new (tipoDeConsulta);
	/*Llamamos a la funcion que nos crearA el string (consulta->strl) para la consulta a ejecutar*/
	InterpretarVectorPersona (consulta, vectorpersona, TipoDePersona);
	g_string_append (consulta, ";");
	//GString *consulta, tipo_vectorpersona vectorpersona, gchar *TipoDePersona);
	g_printf("%s\n",consulta->str); //Para ver la consulta que se ejecuta

    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
	    //  return 1;
    }

    rc = sqlite3_prepare_v2(db, consulta->str, -1, &res, 0);
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
       	MensageError();
		g_printf("(code:%d)\n ", rc);
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        //  return 1;
    } 
    /*
    ImprimirPersonasV2(vectorpersona, res, 2);
	*/
	ImprimirPersonas(vectorpersona, res);

    sqlite3_finalize(res);
    sqlite3_close(db);
	g_free(tipoDeConsulta);
	g_string_free(consulta, TRUE);
	//cnif, nombre1, nombre2, domicilio, cp, ciudad, telefono1, telefono2, email, observaciones
}

void 
PreguntarBuscarPersonas(gchar *TipoDePersona)
{
	gchar *tipoDeNombre1;
	gchar *tipoDeNombre2;
	gchar *tecla;

	/*Variables usadas para la recogida de valores*/
	gchar *cadenaabuscar ;
	gchar *campobusqueda;
	/**/
	tipo_vectorpersona vectorpersona;
	tipoDeNombre1 = g_malloc(17);
	tipoDeNombre2 = g_malloc(14);
	tecla = g_malloc(3);

	cadenaabuscar = g_malloc(100);
	campobusqueda = g_malloc(100);

	/*TODO--------SE-REPITE--------------------------------*/
	if (( g_strcmp0 (TipoDePersona, "PROVEEDOR")) == 0) {
			g_stpcpy(tipoDeNombre1, "Nombre comercial");
			g_stpcpy(tipoDeNombre2,"Nombre fiscal");
	} 

	if ((g_strcmp0 (TipoDePersona, "CLIENTE")) == 0){
			g_stpcpy(tipoDeNombre1,"Nombre");
			g_stpcpy(tipoDeNombre2,"Apellidos");

	}
	/*----ESTO SE REPITE EN CrearPersona-----*/

	do {
		//g_printf("\033c");
		g_printf("SELECCIONE UNA OPCION\nPara buscar %s\n",TipoDePersona);

		g_printf("1-Por NUmero de %s\n", TipoDePersona);
		g_printf("2-Por CIF o NIF\n");
		g_printf("3-Por %s\n", tipoDeNombre1);
		g_printf("4-Por %s\n", tipoDeNombre2);
		g_printf("5-Por Domicilio\n");
		g_printf("6-Por COdigo Postal\n");
		g_printf("7-Por Ciudad\n");
		g_printf("8-Por TelEfono\n"); //BuscarA tanto el primer como el segundo telefono 
		g_printf("9-Por Correo ElectrOnico\n");
		g_printf("0-Para SALIR\n");


		fgets(tecla, 4, stdin);
		LimpiarTexto(tecla);

		if (atoi(tecla)==1) {
			if (( g_strcmp0 (TipoDePersona, "PROVEEDOR")) == 0) {
				g_stpcpy(campobusqueda,IDPROVEEDOR);
				g_printf("Introduzca %s\n",campobusqueda);
				fgets(cadenaabuscar, 100, stdin);
				LimpiarTexto(cadenaabuscar);
				break;
			}
			if (( g_strcmp0 (TipoDePersona, "CLIENTE")) == 0) {
				g_stpcpy(campobusqueda,IDCLIENTE);
				g_printf("Introduzca %s\n",campobusqueda);
				fgets(cadenaabuscar, 100, stdin);
				LimpiarTexto(cadenaabuscar);
				break;
			}

		}
		if (atoi(tecla)==2) {
			g_stpcpy(campobusqueda,CNIF);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
		if (atoi(tecla)==3) {
			g_stpcpy(campobusqueda,NOMBRE1);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}	
		if (atoi(tecla)==4) {
			g_stpcpy(campobusqueda,NOMBRE2);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
		if (atoi(tecla)==5) {
			g_stpcpy(campobusqueda,DOMICILIO);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
 		if (atoi(tecla)==6) {
			g_stpcpy(campobusqueda,CP);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
 		if (atoi(tecla)==7) {
			g_stpcpy(campobusqueda,CIUDAD);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
		if (atoi(tecla)==8) {
			g_stpcpy(campobusqueda,TELEFONO1);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
		if (atoi(tecla)==9) {
			g_stpcpy(campobusqueda,EMAIL);
			g_printf("Introduzca %s\n",campobusqueda);
			fgets(cadenaabuscar, 100, stdin);
			LimpiarTexto(cadenaabuscar);
			break;
		}
  
	} while ( g_strcmp0 (tecla, "0") != 0 );

	InicializarVectorPersona(vectorpersona, TRUE);
	MostrarBuscarPersonas(TipoDePersona, cadenaabuscar, campobusqueda, vectorpersona);
	/*Liberamos variables dinamicas*/
	g_free(tipoDeNombre1);
	g_free(tipoDeNombre2);
	g_free(tecla);	
	g_free(cadenaabuscar);
	g_free(campobusqueda);	
}

void MostrarBuscarPersonas(gchar *TipoDePersona, 
						   gchar *cadenaabuscar, 
						   gchar *campobusqueda,
			   			   tipo_vectorpersona vectorpersona)
{
	gchar *tipoDeConsulta;
	GString *consulta;
	tipoDeConsulta = g_malloc(8);
    sqlite3_stmt *res;
    gchar *err_msg = 0;  
    gint rc = sqlite3_open(BASEDATOS, &db);

    /*Copiamos al GString llamado consulta*/
	g_stpcpy(tipoDeConsulta, "SELECT ");
	consulta = g_string_new (tipoDeConsulta);
	/*Llamamos a la funcion que nos crearA el string (consulta->strl) para la consulta a ejecutar*/
	InterpretarVectorPersona (consulta, vectorpersona, TipoDePersona);
	//GString *consulta, tipo_vectorpersona vectorpersona, gchar *TipoDePersona);
	g_string_append (consulta, " WHERE ");
    g_string_append (consulta, campobusqueda);
    g_string_append (consulta, " LIKE \"");
	g_string_append (consulta, cadenaabuscar);
	g_string_append (consulta, "\";");
	g_printf("%s\n",consulta->str); //Para ver la consulta que se ejecuta


    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
	    //  return 1;
    }

    rc = sqlite3_prepare_v2(db, consulta->str, -1, &res, 0);
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
       	MensageError();
		g_printf("(code:%d)\n ", rc);
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        //  return 1;
    } 
    /*Imprimimos las personaS*/
    ImprimirPersonas(vectorpersona, res);

    sqlite3_finalize(res);
    sqlite3_close(db);
	g_free(tipoDeConsulta);
	g_string_free(consulta, TRUE);
	//cnif, nombre1, nombre2, domicilio, cp, ciudad, telefono1, telefono2, email, observaciones
}

