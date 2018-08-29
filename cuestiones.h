/*
* AUTOR: BarTOLOme Vich Lozano
* EMAIL: amadews23@hotmail.com
* FECHA: Julio del 2018
*
* Programa que destinado para un alquiler de videojuegos
* 	Usa Glib y Sqlite
*	Es en modo texto
*
* Prototipos y tipos de datos para el manejo de cadenas
* Archivo: cuestiones.h
*
*/
#pragma once
#include <glib.h>

//Eliminamos los /n del fgets
void LimpiarTexto(gchar *cadena);

void MensageError(void);

char TextoReducido0( gchar *cadena);

//TODO ¿? o
//void EliminarLetras(gchar *cadena);
// o
//void EliminarLetras(GString cadena);
// char TextoReducido(guint n, gchar *cadena);


