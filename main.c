#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    Wezel *lista = NULL;
    int wybor;
    wczytajZPliku(&lista, argv[1]);

    do {
        wyswietlMenu();
        scanf("%d", &wybor);
        switch (wybor) {
            case 1: dodajMecha(&lista); break;
            case 2: wyswietlWszystkie(lista); break;
            case 3: zapiszDoPliku(lista, argv[1]); break;
            case 4: wczytajZPliku(&lista, argv[1]); break;
            case 5: wyszukajPoModelu(lista); break;
            case 8: usunMecha(&lista); break;
            case 0: zapiszDoPliku(lista, argv[1]); zwolnijPamiec(&lista); break;
        }
    } while (wybor != 0);
    return 0;
}
