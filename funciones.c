#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"




struct Nodo *crear_nodo(int id)
{
    struct Nodo *nodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nodo->id = id;
    nodo->altura = 1;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    return nodo;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;

    // return (a > b) ? a : b;
}

int altura(struct Nodo *nodo)
{
    if (nodo == NULL)
    {
        return 0;
    }
    return nodo->altura;
}

int calcular_altura(struct Nodo *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return raiz->altura;
}




int obtener_balance(struct Nodo *nodo)
{
    if (nodo == NULL)
    {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

struct Nodo *rotar_derecha(struct Nodo *y)
{
    struct Nodo *x = y->izquierda;
    struct Nodo *T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

struct Nodo *rotar_izquierda(struct Nodo *x)
{
    struct Nodo *y = x->derecha;
    struct Nodo *T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

/// @brief /////////////////////
// izq menor , der mallor
struct Nodo* eliminar_nodo(struct Nodo **raiz, int id, struct Nodo **padre) {
    struct Nodo *regreso=NULL;

    if (*raiz == NULL) {
        return regreso;
    }


    

    if (id < (*raiz)->id) {
         regreso=eliminar_nodo(&((*raiz)->izquierda), id, &(*raiz));
    } else if (id > (*raiz)->id) {
         regreso=eliminar_nodo(&((*raiz)->derecha), id, &(*raiz));
    } else {
        struct Nodo *temp = *raiz;

        // Caso 1: Nodo sin hijos o con un solo hijo
        if ((*raiz)->izquierda == NULL) {
            *raiz = (*raiz)->derecha;
            //free(temp);
            regreso=temp;
        } else if ((*raiz)->derecha == NULL) {
            *raiz = (*raiz)->izquierda;
            //free(temp);
            regreso=temp;
        } else {  //



            
            // Caso 2: Nodo con dos hijos
            struct Nodo *Psusesor;
            struct Nodo *aux=NULL;
            struct Nodo *aux2=NULL;
            struct Nodo *eliminar=NULL;
            struct Nodo *hsucesor=NULL;



            struct Nodo *sucesor = encontrar_nodo_minimo((*raiz)->derecha,*raiz,&Psusesor);
            if ((*raiz)->derecha == sucesor)
            {
                aux = (*raiz)->izquierda;
                eliminar=*raiz;
                *raiz = (*raiz)->derecha;
                (*raiz)->izquierda = aux;
                eliminar->izquierda=NULL;
                eliminar->derecha=NULL;
                //printf("id del nodo eliminado%d",eliminar->id);
                regreso=eliminar_nodo(&eliminar,eliminar->id,NULL);    

            }else{
                hsucesor=sucesor->derecha;

                aux=(*raiz)->izquierda;
                aux2=(*raiz)->derecha;


                (*raiz)->izquierda=NULL;
                (*raiz)->derecha=NULL;

                eliminar=*raiz;

                *raiz=sucesor;

                (*raiz)->izquierda=aux;
                (*raiz)->derecha=aux2;

                Psusesor->izquierda=hsucesor;
                
                regreso=eliminar_nodo(&eliminar,eliminar->id,NULL); 
            }   
        }//
    }

    // Actualizar la altura y equilibrar el árbol
    if (*raiz != NULL) {
        (*raiz)->altura = 1 + max(altura((*raiz)->izquierda), altura((*raiz)->derecha));

        int balance = obtener_balance(*raiz);

        if (balance > 1 && obtener_balance((*raiz)->izquierda) >= 0) {
            *raiz = rotar_derecha(*raiz);
            printf("rotacion 1");
        }

        if (balance > 1 && obtener_balance((*raiz)->izquierda) < 0) {
            (*raiz)->izquierda = rotar_izquierda((*raiz)->izquierda);
            *raiz = rotar_derecha(*raiz);
            printf("rotacion 2");

        }

        if (balance < -1 && obtener_balance((*raiz)->derecha) <= 0) {
            *raiz = rotar_izquierda(*raiz);
            printf("rotacion 3");

        }

        if (balance < -1 && obtener_balance((*raiz)->derecha) > 0) {
            (*raiz)->derecha = rotar_derecha((*raiz)->derecha);
            *raiz = rotar_izquierda(*raiz);
            printf("rotacion 4");

        }
    } 
    return regreso;
}


//////////////////////////

struct Nodo *buscar_nodo(struct Nodo *nodo, int id)
{
    if (nodo == NULL || nodo->id == id)
    {
        return nodo;
    }
    if (id < nodo->id)
    {
        return buscar_nodo(nodo->izquierda, id);
    }
    else
    {
        return buscar_nodo(nodo->derecha, id);
    }
}


struct Nodo *encontrar_nodo_minimo(struct Nodo *nodo, struct Nodo *padre, struct Nodo **Psusesor) {
    if (nodo == NULL) {
        padre = NULL;  
        return NULL;
    }

    if (nodo->izquierda == NULL) {
        padre = *Psusesor;  
        return nodo;
    }

    *Psusesor = nodo;  // este es el padre

    return encontrar_nodo_minimo(nodo->izquierda, padre, Psusesor);
}




void insertar_nodo(struct Nodo **raiz, struct Nodo *nodo)
{
    if (*raiz == NULL)
    {
        *raiz = nodo;
        return;
    }

    if (nodo->id < (*raiz)->id)
    {
        insertar_nodo(&((*raiz)->izquierda), nodo);
    }
    else if (nodo->id > (*raiz)->id)
    {
        insertar_nodo(&((*raiz)->derecha), nodo);
    }

    (*raiz)->altura = 1 + max(altura((*raiz)->izquierda), altura((*raiz)->derecha));

    int balance = obtener_balance(*raiz);

    // Caso de desequilibrio a la izquierda-izquierda
    if (balance > 1 && nodo->id < (*raiz)->izquierda->id)
    {
        *raiz = rotar_derecha(*raiz);
    }

    // Caso de desequilibrio a la derecha-derecha
    if (balance < -1 && nodo->id > (*raiz)->derecha->id)
    {
        *raiz = rotar_izquierda(*raiz);
    }

    // Caso de desequilibrio a la izquierda-derecha
    if (balance > 1 && nodo->id > (*raiz)->izquierda->id)
    {
        (*raiz)->izquierda = rotar_izquierda((*raiz)->izquierda);
        *raiz = rotar_derecha(*raiz);
    }

    // Caso de desequilibrio a la derecha-izquierda
    if (balance < -1 && nodo->id < (*raiz)->derecha->id)
    {
        (*raiz)->derecha = rotar_derecha((*raiz)->derecha);
        *raiz = rotar_izquierda(*raiz);
    }
}

void imprimir_arbol(struct Nodo *nodo)
{
    if (nodo == NULL)
    {
        return;
    }
    imprimir_arbol(nodo->izquierda);
    printf("%d ", nodo->id);
    imprimir_arbol(nodo->derecha);
}

void liberar_arbol(struct Nodo *nodo)
{
    if (nodo == NULL)
    {  
        return;
    }
    liberar_arbol(nodo->izquierda);
    liberar_arbol(nodo->derecha);
    free(nodo);
}

void imprimirArbol(struct Nodo *raiz, int nivel)
{
    if (raiz == NULL)
    {
        return;
    }
    imprimirArbol(raiz->derecha, nivel + 5);
    printf("\n");
    Espacios(nivel);
    printf("├─%d\n", raiz->id);
    imprimirArbol(raiz->izquierda, nivel + 5);
}

void Espacios(int espacios)
{
    if (espacios == 0)
    {
        return;
    }
    else
    {
        printf(" ");
        Espacios(espacios - 1);
    }
}

void borrar(struct Nodo *Nodo)
{
    Nodo->izquierda = NULL;
    Nodo->derecha = NULL;
    free(Nodo);
}

void imprimir_inorder(struct Nodo *nodo)
{
    if (nodo != NULL)
    {
        imprimir_inorder(nodo->izquierda);
        printf("%d ", nodo->id);
        imprimir_inorder(nodo->derecha);
    }
}

void imprimir_preorder(struct Nodo *nodo)
{
    if (nodo != NULL)
    {
        printf("%d ", nodo->id);
        imprimir_preorder(nodo->izquierda);
        imprimir_preorder(nodo->derecha);
    }
}

void imprimir_posorder(struct Nodo *nodo)
{
    if (nodo != NULL)
    {
        imprimir_posorder(nodo->izquierda);
        imprimir_posorder(nodo->derecha);
        printf("%d ", nodo->id);
    }
}



void imprimir_parentesis(struct Nodo *nodo)
{
    if (nodo == NULL) {
        return;
    }

    printf("%d", nodo->id);

    if (nodo->izquierda != NULL || nodo->derecha != NULL) {
        printf(" (");

        imprimir_parentesis(nodo->izquierda);

        if (nodo->derecha != NULL) {
            printf(",");
        }

        imprimir_parentesis(nodo->derecha);

        printf(")");
    }
}






void recorrido_anchura(struct Nodo *raiz) {
    if (raiz == NULL) {
        printf("El árbol está vacío.\n");
        return;
    }

    struct nodo *cola = NULL;


    insertar_nodo_cola(&cola, crear_nodo_cola(raiz->id));


    while (cola != NULL) {
      
        struct nodo *nodo_cola = extraer_nodo_cola(&cola);
        struct Nodo *nodo_arbol = buscar_nodo(raiz, nodo_cola->id);
        eliminar_nodo_cola(&nodo_cola);

       
        printf("%d ", nodo_arbol->id);

        if (nodo_arbol->izquierda != NULL) {
            insertar_nodo_cola(&cola, crear_nodo_cola(nodo_arbol->izquierda->id));
        }
        if (nodo_arbol->derecha != NULL) {
            insertar_nodo_cola(&cola, crear_nodo_cola(nodo_arbol->derecha->id));
        }
        //eliminar_nodo_cola(nodo_cola);

    }

    limpia_Cola(&cola);
}


struct nodo * crear_nodo_cola (int id)
{
  struct nodo *nodo= NULL;
  nodo =(struct nodo *) malloc (sizeof (struct nodo));

  if (NULL != nodo)
  {
    nodo-> id= id;
    nodo-> sig= NULL;
  }
  return nodo;
}

void insertar_nodo_cola (struct nodo **cola, struct nodo *nodo )
{
  struct nodo * act= NULL;

  if (*cola==NULL)
    *cola = nodo ;
  else {
    act=*cola;
    //recorrido para encontrar el ultimo elementoi
    while(act -> sig != NULL){
      act = act -> sig;
    }
    act-> sig = nodo;
  
}
}

void eliminar_nodo_cola (struct nodo **nodo){
    free(*nodo);
    *nodo = NULL;
}


struct nodo * extraer_nodo_cola (struct nodo ** cola)
{
    struct nodo * aux = NULL;
    aux = *cola;
    if(aux!=NULL){
    *cola = (*cola) -> sig;
    aux -> sig = NULL;
    }
    return aux;
} 



void limpia_Cola(struct nodo **cola){
struct nodo *aux ;
    while (*cola!=NULL)
    {
        //printf("hay algo en la cola \n");
        aux=extraer_nodo_cola(&(*cola));
        //printf("se saco el nodo %d \n",aux->id);
        eliminar_nodo_cola(&aux);
    }
    //printf("no hay nada en la cola \n");
}



/*
1  agregar *listo
2 quitar   *listo
3 imprimir *listo
4 recoridos falta la cola
5 altura  listo* 
6 buscar  no 
7 vaciar 
8 salir
*/
