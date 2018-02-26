
// Esta función deshabilita el modo canónico en la terminal,
// con el fin de evitar que se tenga que presionar enter
// en la pantalla principal.
struct termios original_f, modified_f;
void disable_canonical() {
    setbuf(stdout, NULL);
    tcgetattr(STDIN_FILENO, &original_f);

    modified_f = original_f;
    modified_f.c_lflag &= ~(ICANON|ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &modified_f);
}

// Esta función habilita el modo canónico en la terminal
void enable_canonical() {
    tcgetattr(STDIN_FILENO, &original_f);

    original_f.c_lflag |= (ICANON|ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &original_f);
}

//funcion para los creditos del programa
void creditos() { 
    CLS;

    printf("Universidad Iberoamericana\n");
    printf("Programación Aplicada\n\n");

    printf("Este programa fue desarrollado por:\n");
    printf("\tGuillermo Ortega\n");
    printf("\tSerio Sarabia\n");

    printf("\n\nPresiona enter para entrar al sistema...");

    disable_canonical();
    getchar();
    enable_canonical();

    CLS;
}
