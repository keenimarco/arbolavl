#include<stdio.h>
#include "arbol.h"
#include<stdlib.h>
#include <time.h>




// balanceado arbol


int menu (void)
{
	int opcion;

	printf ("MENU.\n");
	printf ("--------\n");
	printf ("1. Agregar (crear + insertar).\n");
	printf ("2. Quitar  (extraer + eliminar).\n");
	printf ("3. Imprimir arbol.\n");
	printf ("4. Imprimir recoridos .\n");
	printf ("5. altura.\n");// y cuantos ciclos se usaron
	printf ("6. vaciar.\n");
	printf ("7. Salir.\n");
	printf ("--------\n");
	printf ("Opcion: ");
	scanf ("%d", &opcion);

	return opcion;
}

int main (int argc, char *argv[])
{
	int opcion, id;
	struct Nodo *arbol = NULL, *nodo = NULL;
	//struct nodo *cola = NULL;
		
	
    if (argc > 1) {
        // Si se proporcionan argumentos de línea de comandos, agregar nodos automáticamente
        for (int i = 1; i < argc; i++) {

			id = atoi(argv[i]);
			if (!(buscar_nodo(arbol,id)!=NULL))
			{
				nodo = crear_nodo(id);
				insertar_nodo(&arbol, nodo);
			}else{
			printf("\nnodo insertado con anterioridad\n");
			}
        }
    }
	do
	{
		opcion = menu ();
		switch (opcion)
		{
			case 1:
				printf ("Id del nodo: ");
				scanf ("%d", &id);	
				if (!(buscar_nodo(arbol,id)!=NULL))
				{
					nodo = crear_nodo(id);
					insertar_nodo(&arbol, nodo);
					}else{
					printf("\nnodo insertado con anterioridad\n");
				}
				break;

			case 2:

				if(arbol == NULL ) // protege de que la cola no este vacia 
					printf("la arbol  vacio ");
				else
				{
					printf("id a eliminar ");
					scanf ("%d", &id);

					nodo=eliminar_nodo(&arbol,id,NULL);
					if(nodo!=NULL){
					printf("se elimino el nodo %d ", nodo->id);
					borrar(nodo);
					}
				}
				break;

			case 3:
				 imprimirArbol(arbol,0);
				break;
			case 4:
			//aqui se imprimen todos 
				imprimir_parentesis(arbol);

				printf("\ninorden \n");
				imprimir_inorder(arbol);
				printf("\nposorden \n");
				imprimir_posorder(arbol);
				printf("\npreorden \n");
				imprimir_preorder(arbol);


       			printf("\nRecorrido en anchura: ");
        		recorrido_anchura(arbol);
        		printf("\n");
        break;
				break;
			case 5:
			    printf("Altura del árbol: %d\n", calcular_altura(arbol));
				break;
			case 6:
			liberar_arbol(arbol);
			arbol=NULL;
				break;
			case 7:
			liberar_arbol(arbol);
				break;

			default:
				printf ("Opción inválida !!!\n");

		}
		printf ("\n");
	} while (opcion != 7); 

	return 0;
} 
