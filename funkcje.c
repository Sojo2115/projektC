#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"

void wyswietlMenu() {
    printf("\n=== SYSTEM MECHOW (v0.1) ===\n");
    printf("1. Dodaj mecha\n");
    printf("2. Wyswietl flote\n");
    printf("0. Wyjscie\n");
    printf("Wybor: ");
}

Wezel* utworzWezel(Mech dane) {
    Wezel *nowy = (Wezel*)malloc(sizeof(Wezel));
    if (!nowy) return NULL;
    nowy->dane = dane;
    nowy->nastepny = NULL;
    return nowy;
}

void dodajMecha(Wezel **glowa) {
    Mech m;
    printf("Model: "); scanf("%s", m.model);
    printf("Klasa: "); scanf("%s", m.klasa);
    printf("Moc: "); scanf("%f", &m.moc);
    printf("Pilot: "); scanf("%s", m.pilot);
    printf("Stan: "); scanf("%s", m.stan);

    Wezel *nowy = utworzWezel(m);
    if (*glowa == NULL) {
        *glowa = nowy;
    } else {
        Wezel *temp = *glowa;
        while (temp->nastepny != NULL) temp = temp->nastepny;
        temp->nastepny = nowy;
    }
    printf("[OK] Dodano.\n");
}

void wyswietlWszystkie(Wezel *glowa) {
    printf("\nMODEL | KLASA | MOC | PILOT\n");
    while (glowa) {
        printf("%s | %s | %.1f | %s\n", glowa->dane.model, glowa->dane.klasa, glowa->dane.moc, glowa->dane.pilot);
        glowa = glowa->nastepny;
    }
}

void zwolnijPamiec(Wezel **glowa) {
    Wezel *obecny = *glowa;
    while (obecny) {
        Wezel *temp = obecny;
        obecny = obecny->nastepny;
        free(temp);
    }
    *glowa = NULL;
}
