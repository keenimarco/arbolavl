 #ifndef _libreria_H_
#define _libreria_H_

//balanceado

struct Nodo {
    int id;
    int altura;
    struct Nodo* izquierda;
    struct Nodo* derecha;
};

struct nodo
{
	int id;
	//...
	struct nodo *sig;
};




struct Nodo* crear_nodo(int id);
int max(int a, int b);

int altura(struct Nodo* nodo);
int calcular_altura(struct Nodo *raiz);

int obtener_balance(struct Nodo* nodo) ;
struct Nodo* rotar_derecha(struct Nodo* y);
struct Nodo* rotar_izquierda(struct Nodo* x);
void insertar_nodo(struct Nodo**, struct Nodo *);
struct Nodo* buscar_nodo(struct Nodo* nodo, int id);
struct Nodo* encontrar_nodo_minimo(struct Nodo* nodo, struct Nodo *,struct Nodo **);

struct Nodo* eliminar_nodo(struct Nodo**, int,struct Nodo**);

void imprimir_arbol(struct Nodo* nodo) ;
void liberar_arbol(struct Nodo* nodo) ;
void imprimirArbol(struct Nodo *raiz, int nivel) ;
void Espacios(int espacios);
void borrar (struct Nodo *Nodo);


void imprimir_inorder(struct Nodo* nodo);
void imprimir_preorder(struct Nodo* nodo);
void imprimir_posorder(struct Nodo* nodo);
void imprimir_parentesis(struct Nodo *nodo);


void recorrido_anchura(struct Nodo *raiz);




struct nodo *crear_nodo_cola (int);
void insertar_nodo_cola  (struct nodo **, struct nodo *);
struct nodo *extraer_nodo_cola  (struct nodo **);
void eliminar_nodo_cola (struct nodo **);
void limpia_Cola(struct nodo **cola);







#endif
