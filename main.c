#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"

int main(int argc, char *argv[]) {
    Wezel *lista = NULL;
    int wybor;

    do {
        wyswietlMenu();
        scanf("%d", &wybor);
        switch (wybor) {
            case 1: dodajMecha(&lista); break;
            case 2: wyswietlWszystkie(lista); break;
            case 0: zwolnijPamiec(&lista); break;
        }
    } while (wybor != 0);
    return 0;
}
