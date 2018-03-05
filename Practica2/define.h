
#ifndef UTILITIES_H
    #define UTILITIES_H
        void disable_canonical();
        void enable_canonical();
        void insertar_lista(lista_t **inicio,char simbolo,int prob);
        void imprimir_lista(lista_t *inicio);
        void borrar_simbolo(lista_t **inicio,char sim);
        void Guardar_lista(lista_t *inicio);
        int salir(lista_t *inicio);
        void Leer_lista(lista_t **inicio);
#endif
