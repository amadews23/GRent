CREATE TABLE "GENERO" (
    "IdGenero" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "nombre" TEXT
);

CREATE TABLE VIDEOJUEGO(
 IdVideojuego    INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, 
  nombre  TEXT,
  descripcion TEXT,
  IdGenero INTEGER,
  precioalquiler FLOAT,
  FOREIGN KEY (IdGenero) REFERENCES genero(IdGenero) ON UPDATE  CASCADE ON DELETE SET NULL
);
CREATE TABLE "COMPRA" (
    "IdCompra" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "fecha" INTEGER,
    "IdProveedor" TEXT,
      FOREIGN KEY ("IdProveedor") REFERENCES proveedor("IdProveedor") ON UPDATE  CASCADE ON DELETE SET NULL

);
CREATE TABLE "UNIDAD" (
    "IdUnidad" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "IdVideojuego" INTEGER NOT NULL,
    "IdCompra" INTEGER NOT NULL,
    "preciocoste" FLOAT,
      FOREIGN KEY ("IdVideojuego") REFERENCES videojuego("IdVideojuego") ON UPDATE  CASCADE ON DELETE SET NULL,
      FOREIGN KEY ("IdCompra") REFERENCES compra("IdCompra") ON UPDATE  CASCADE ON DELETE SET NULL
);
CREATE TABLE "ALQUILA" (
    "IdAlquiler" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "fecha_salida" INTEGER NOT NULL,
     "fecha_adevolver" INTEGER NOT NULL,
    "fecha_devolucion" INTEGER DEFAULT NULL,
    "importe_pagado" FLOAT, 
    "importe_debido" FLOAT,
    "pagado" INTEGER DEFAULT NULL,
     "IdUnidad" INTEGER NOT NULL,
    "IdCliente" INTEGER NOT NULL,
      FOREIGN KEY ("IdUnidad") REFERENCES unidad("IdUnidad") ON UPDATE  CASCADE ON DELETE SET NULL,
      FOREIGN KEY ("IdCliente") REFERENCES cliente("IdCliente") ON UPDATE  CASCADE ON DELETE SET NULL
);
CREATE TABLE "CLIENTE" (
    "IdCliente" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "cnif" TEXT UNIQUE,
    "nombre1" TEXT,
    "nombre2" TEXT,
    "domicilio" TEXT,
    "cp" TEXT,
    "ciudad" TEXT,
    "telefono1" TEXT,
    "telefono2" TEXT,
    "email" TEXT,
    "observaciones" TEXT
);
;
CREATE TABLE "PROVEEDOR" (
    "IdProveedor" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    "cnif" TEXT UNIQUE,
    "nombre1" TEXT,
    "nombre2" TEXT,
    "domicilio" TEXT,
    "cp" TEXT,
    "ciudad" TEXT,
    "telefono1" TEXT,
    "telefono2" TEXT,
    "email" TEXT,
    "observaciones" TEXT
);
;
