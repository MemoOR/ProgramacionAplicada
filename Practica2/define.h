
#ifndef UTILITIES_H
    #define UTILITIES_H
        void disable_canonical();
        void enable_canonical();
        void insertar_lista(lista_t **inicio,char simbolo,int prob);
        void imprimir_lista(lista_t *inicio);
        void borrar_simbolo(lista_t **inicio,char sim);
        void Guardar_lista(lista_t *inicio);
        int Borrar_lista(lista_t *inicio);
        void Borrar_arbol(struct nodo_t *p);
        void Leer_lista(lista_t **inicio);
        void codigos_arbol(lista_t **inicio, nodo_t *raiz,char **codes, float *frec);
        void insertar_arbol(nodo_t *padre);
        lista_t *pop(lista_t **inicio);
        nodo_t *crear_nodo(char letra, char code, float prob,
                           nodo_t *izq, nodo_t *der, nodo_t *padre);
        void buscar(nodo_t *raiz, char *buscado,int nivel,char **codes);
        void guardar_codigo();
        void codificar();
        void decodificar();
#endif
