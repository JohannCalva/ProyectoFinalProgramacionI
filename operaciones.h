#ifndef OPERACIONES_H_INCLUDED
#define OPERACIONES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//el struct que contiene la informacion de los productos
struct Producto {
    int id;
    char nombre[20];
    float precio;
    int cantidad;
};
//funcion para verificiar que un ingreso sea positivo
bool positivo(int a){
  if (a>0){
    return true;
  }
  printf("Por favor ingrese un numero positivo.\n");
  return false;
} 
//funcion para registrar un producto
void registrarProductos(struct Producto productos[], int *contador) {
    char input[10];
    char input2[10];
    int np;
    printf("Cuantos productos desea ingresar: ");
  //se verifica que el ingreso sea un numero positivo
    do {
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &np);
    } while (positivo(np) == false);
  //se usa un for para registrar la informacion del producto (o productos)
    for (int i = 0; i < np; i++) {
        printf("\nRegistre el nombre producto %d: ", (*contador) + 1);
      //se registra el id del producto 
        productos[*contador].id = (*contador) + 1;
      //se usa scanf para registrar el nombre del producto
        scanf("%s", productos[*contador].nombre);
        printf("Ingrese el precio de %s: $", productos[*contador].nombre);
      //getchar para limpiar el buffer
        getchar();
        do {
          //se usa fgets para registrar el precio del producto en un string, el cual sera convertido a float y se guarda en el struct con sscanf
            fgets(input2, sizeof(input2), stdin);
            sscanf(input2, "%f", &productos[*contador].precio);
        } while (positivo(productos[*contador].precio) == false);
        do {
            printf("Ingrese las Unidades de %s: ", productos[*contador].nombre);
          //se usa fgets para registrar la cantidad de unidades del producto en un string, el cual sera convertido a int y se guarda en el struct con sscanf
            fgets(input2, sizeof(input2), stdin);
            sscanf(input2, "%d", &(productos[*contador].cantidad));
          //se usa un doble verificador para asegurarse que el ingreso sea valido
        } while (sscanf(input2, "%d", &(productos[*contador].cantidad)) != 1 || positivo(productos[*contador].cantidad) == false);
      //se aumenta el contador para registrar el siguiente producto
        (*contador)++;
    }
}
//funcion para visualizar el inventario
void listaProdu(struct Producto productos[], int numproducto) {
  //cabecera del inventario (no es parte del archivo)
    printf("\n-----------LISTA DE PRODUCTOS----------\n");
    printf("\n\tPRODUCTOS|\tPRECIO\t|\tCANTIDAD\n");
  //se usa un for para imprimir los elementos de los productos
    for (int i = 0; i < numproducto; i++) {
        if (strlen(productos[i].nombre) > 0 && productos[i].cantidad > 0) {
            printf("%d) %s\t\t\t\t$%.2f\t\t\t%d\n",(i+1), productos[i].nombre, productos[i].precio, productos[i].cantidad);
        }
    }
}
//funcion para editar un producto ingresado
void editarProdu(struct Producto productos[], int numProductos) {
    char input[10];
    int nProducto;
//se pide que el usuario ingrese el id del producto que desea editar
    do {
      //se usa fgets para registrar el id del producto en un string, el cual sera convertido a int y se guarda en la variable nProducto
        printf("\nIngrese el número de producto que desea editar: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &nProducto);
      //tambien se usa el doble verificador para asegurarse que el ingreso sea valido
    } while (nProducto < 1 || nProducto > numProductos);
    int opcionEdicion;
  //se muestra el menu de opciones para editar el producto
    printf("\nSeleccione la opción de edición:\n");
    printf("1. Editar nombre del producto\n");
    printf("2. Editar precio del producto\n");
    printf("3. Editar cantidad del producto\n");
    printf("4. Editar todo\n");
    printf("Seleccione: ");
    do {
      //mismo metodo de ingreso y verificacion
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &opcionEdicion);
      if (opcionEdicion < 1 || opcionEdicion > 4){
        printf("Por favor ingrese un numero valido.\n");
      }
    } while (opcionEdicion < 1 || opcionEdicion > 4);
    //switch para las opciones del menu
    switch (opcionEdicion) {
      //edicion de solo el nombre del producto
        case 1:
            printf("Ingrese el nuevo nombre del producto: ");
            scanf("%s", productos[nProducto - 1].nombre);
            getchar();
            break;
      //edicion de solo el precio del producto
        case 2:
            do {
                printf("Ingrese el nuevo precio del producto: $");
                fgets(input, sizeof(input), stdin);
                sscanf(input, "%f", &productos[nProducto - 1].precio);
            } while (sscanf(input, "%f", &productos[nProducto - 1].precio) != 1 || positivo(productos[nProducto - 1].precio) == false);
            break;
      //edicion de solo la cantidad del producto
        case 3:
            do {
                printf("Ingrese la nueva cantidad del producto: ");
                fgets(input, sizeof(input), stdin);
                sscanf(input, "%d", &productos[nProducto - 1].cantidad);
            } while (sscanf(input, "%d", &productos[nProducto - 1].cantidad) != 1 || positivo(productos[nProducto - 1].cantidad) == false);
            break;
      //edicion de todos los elementos del producto
        case 4:
            printf("Ingrese el nuevo nombre del producto: ");
            scanf("%s", productos[nProducto - 1].nombre);
            getchar();
            do {
                printf("Ingrese el nuevo precio del producto: $");
                fgets(input, sizeof(input), stdin);
                sscanf(input, "%f", &productos[nProducto - 1].precio);
            } while (sscanf(input, "%f", &productos[nProducto - 1].precio) != 1 || positivo(productos[nProducto - 1].precio) == false);

            
            do {
                printf("Ingrese la nueva cantidad del producto: ");
                fgets(input, sizeof(input), stdin);
                sscanf(input, "%d", &productos[nProducto - 1].cantidad);
            } while (sscanf(input, "%d", &productos[nProducto - 1].cantidad) != 1 || positivo(productos[nProducto - 1].cantidad) == false);
            break;
        default:
            printf("Intente nuevamente:\n");
    }
}
//funcion para eliminar un producto
void eliminarProdu(struct Producto productos[], int *np, struct Producto eliminados[], int *cont_elim) {
    int nProducto;
    printf("\nIngrese el número de producto que desea eliminar: ");
    scanf("%d", &nProducto);
  //se verifica que el ingreso sea valido
    if (nProducto >= 1 && nProducto <= *np) {
        (*cont_elim)++;
        eliminados[*cont_elim - 1] = productos[nProducto - 1];
  //se usa un for para mover los elementos del arreglo
        for (int i = nProducto - 1; i < *np - 1; i++) {
            productos[i] = productos[i + 1];
        }
        (*np)--;
      //mensaje si el ingreso no es valido
    } else {
        printf("El número de producto no es válido. Intente nuevamente.\n");
    }
}
//misma funcion que visualizar pero para los productos eliminados
void imprimirEliminados(struct Producto eliminados[], int np) {
    printf("Productos eliminados:\n");
    printf("\n\tPRODUCTOS|\tPRECIO\t|\tCANTIDAD\n");

    for (int i = 0; i < np; i++) {
        printf("%s\t\t\t\t$%.2f\t\t\t%d\n", eliminados[i].nombre, eliminados[i].precio, eliminados[i].cantidad);
    }
}

//funcion para guardar los productos en un archivo
void guardarInventario(struct Producto productos[], int np) {
  //se abre el archivo en modo write
    FILE *archivo = fopen("inventario.txt", "w");
  //mensaje por si no se pudo abrir el archivo
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de inventario.\n");
        return;
    }
  //se usa un for para escribir los productos y sus elementos en el archivo
    for (int i = 0; i < np; i++) {
        fprintf(archivo, "%d) %s\t\t\t\t$%.2f\t\t\t%d\n", (i+1), productos[i].nombre, productos[i].precio, productos[i].cantidad);
    }
    fclose(archivo);
}
//misma funcion que la anterior pero para los eliminados
void guardarEliminados(struct Producto eliminados[], int ne) {
    FILE *archivo = fopen("eliminados.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de productos eliminados.\n");
        return;
    }

    for (int i = 0; i < ne; i++) {
        fprintf(archivo, "%d) %s\t\t\t\t$%.2f\t\t\t%d\n", (i+1), eliminados[i].nombre, eliminados[i].precio, eliminados[i].cantidad);
    }

    fclose(archivo);
}
//funcion para cargar los productos desde un archivo (se usa esto para poder correr el programa sin tener que ingresar los productos anteriores)
void cargarProductos(struct Producto productos[], int *np) {
    FILE *archivo = fopen("inventario.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de inventario.\n");
        return;
    }
    int i = 0;
  //se usa un while para leer los productos y sus elementos del archivo
    while (fscanf(archivo, "%d) %s $%f %d", &productos[i].id, productos[i].nombre, &productos[i].precio, &productos[i].cantidad) == 4) {
        i++;
    }
    *np = i;
    fclose(archivo);
}
//misma funcion que la anterior pero para los eliminados
void cargarEliminados(struct Producto eliminados[], int *ne) {
    FILE *archivo = fopen("eliminados.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de productos eliminados.\n");
        return;
    }

    int i = 0;
    while (fscanf(archivo, "%d) %s\t$%f\t%d", &eliminados[i].id, eliminados[i].nombre, &eliminados[i].precio, &eliminados[i].cantidad) == 4) {
      i++;
  }


    *ne = i;
    fclose(archivo);
}
//funcion para mostrar el menu principal y sus opciones
void menu(){
  printf("\n");
  printf("\n---INVENTARIO TIENDA DE MASCOTAS---\n");
  printf("1.Registrar productos nuevos\n");
  printf("2.Ver inventario\n");
  printf("3.Editar productos\n");
  printf("4.Eliminar productos\n");
  printf("5.Ver productos eliminados\n");
  printf("6.Salir del programa\n");
}
#endif