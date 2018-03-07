
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
        void codigos(lista_t *inicio);
        void insertar_arbol(nodo_t *hojas_1,nodo_t *hojas_2);
        void generar_codigo();
        void guardar_codigo();
        void codificar();
        void decodificar();
#endif
