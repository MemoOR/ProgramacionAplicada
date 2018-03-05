int Borrar_lista(lista_t *inicio){
 lista_t *temp;
  temp=inicio;
  while(temp!=NULL){
    inicio=temp->sig;
    free(temp);
    temp=inicio;
  }
  return 0;
}
