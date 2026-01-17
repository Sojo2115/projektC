#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uzycie: %s baza.txt\n", argv[0]);
        return 1;
    }

    Wezel *lista = NULL; 
    int wybor;

    wczytajZPliku(&lista, argv[1]);

    do {
        wyswietlMenu();
        if (scanf("%d", &wybor) != 1) {
            while(getchar() != '\n');
            wybor = -1;
        }

        switch (wybor) {
            case 1: dodajMecha(&lista); break;
            case 2: wyswietlWszystkie(lista); break;
            case 3: zapiszDoPliku(lista, argv[1]); break;
            case 4: wczytajZPliku(&lista, argv[1]); break;
            case 5: wyszukajPoModelu(lista); break;
            case 6: wyszukajPowyzejMocy(lista); break;
            case 7: edytujMecha(lista); break;
            case 8: usunMecha(&lista); break;
            case 9: usunWszystkieWDemontazu(&lista); break;
            case 10: sortujPoModelu(lista); break;
            case 11: sortujPoMocy(lista); break;
            case 0: 
                zapiszDoPliku(lista, argv[1]);
                zwolnijPamiec(&lista);
                printf("Koniec.\n");
                break;
            default: printf("Nieznana opcja.\n");
        }
    } while (wybor != 0);

    return 0;
}
