//se incluye la libreria
#include "operaciones.h"
//comienzo del main
int main(void) {
  //se declaran las variables y los struc
    struct Producto productos[20];
    struct Producto eliminados[20];
  //el char que se usara para los ingresos
    char input[10];
  //contador de productos
    int contador=0;
  //contador de eliminados
    int contador_eliminados=0;
  //variable que lee cuantos productos ingresara el usuario
    int np=0;
  //variable para el menu
    int op;
  //se carga los productos ingresados y eliminados previamente y se guardan en sus respectivos structs
    cargarProductos(productos, &np);
    cargarEliminados(eliminados, &contador_eliminados);
  //el contador es igual al numero de productos ingresados 
    contador=np;
  //comienzo del primer do
    do {
      //se imprime el menu
        menu();
        do {
          //se lee la opcion ingresada por el usuario y se verifica si es valida
            printf("\nSeleccione:");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &op);
        } while (sscanf(input, "%d", &op) != 1 || positivo(op) == false);
        //switch basado en la opcion ingresada
        switch (op) {
          //caso 1 registra productos
            case 1:
                registrarProductos(productos, &contador);
              //el contador ahora es igual a la cantidad de productos ingresados
                np=contador;
                break;
          //caso 2 visualiza los productos ingresados
            case 2:
              //verifica si hay productos ingresados
              if(contador<1){
                printf("No hay productos registrados.\n");
                  }else{
                //corre la funcion listaProdu
                listaProdu(productos, contador);
                  }
                break;
            case 3:
              //verificacion
              if(contador<1){
                printf("No hay productos registrados.\n");
                  }else{
                //primero se despliega la lista de productos
                listaProdu(productos, contador);
                //despues sigue con la funcion editar
                editarProdu(productos, contador);
                  }
                break;
          //caso 4 elimina productos
            case 4:
              //verificacion
              if (contador<1){
                printf("No hay productos registrados.\n");
                  }else{
                //se despliega la lista de productos
                listaProdu(productos, contador);
                //sigue con la funcion eliminar
                eliminarProdu(productos, &contador, eliminados, &contador_eliminados);
                //se limpia el buffer
                getchar();
                  }
                break;
          //caso 5 visualizacion de eliminados
            case 5:
              //verificacion
              if(contador_eliminados<1){
                printf("No ha eliminado productos.\n");
                  }else{
                //se despliega la lista de productos eliminados
                imprimirEliminados(eliminados, contador_eliminados);
                  }
                break;
          //caso 6 salir del programa
            case 6:
              //se guardan los productos ingresados y eliminados en los archivos
              guardarInventario(productos, np);
              guardarEliminados(eliminados, contador_eliminados);
                break;
          //default en caso de que no se ingrese una opcion valida
            default:
              printf("Intente nuevamente.\n");
        }
      //el primer loop termina cuando el usuario ingrese 6
    } while (op != 6);

    return 0;
}
