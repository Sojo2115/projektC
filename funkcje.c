#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"

void wyswietlMenu() {
    printf("\n=== SYSTEM MECHOW (v0.5) ===\n");
    printf("1. Dodaj mecha\n");
    printf("2. Wyswietl flote\n");
    printf("3. Zapisz\n");
    printf("4. Wczytaj\n");
    printf("5. Szukaj (Model)\n");
    printf("8. Usun mecha\n");
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
}

void wyswietlWszystkie(Wezel *glowa) {
    printf("\nMODEL | KLASA | MOC | PILOT | STAN\n");
    while (glowa) {
        printf("%s | %s | %.1f | %s | %s\n", glowa->dane.model, glowa->dane.klasa, glowa->dane.moc, glowa->dane.pilot, glowa->dane.stan);
        glowa = glowa->nastepny;
    }
}

void zapiszDoPliku(Wezel *glowa, const char *nazwaPliku) {
    FILE *f = fopen(nazwaPliku, "w");
    if (!f) return;
    while (glowa) {
        fprintf(f, "%s %s %.2f %s %s\n", glowa->dane.model, glowa->dane.klasa, glowa->dane.moc, glowa->dane.pilot, glowa->dane.stan);
        glowa = glowa->nastepny;
    }
    fclose(f);
    printf("Zapisano.\n");
}

void wczytajZPliku(Wezel **glowa, const char *nazwaPliku) {
    FILE *f = fopen(nazwaPliku, "r");
    if (!f) return;
    zwolnijPamiec(glowa);
    Mech m;
    while (fscanf(f, "%s %s %f %s %s", m.model, m.klasa, &m.moc, m.pilot, m.stan) == 5) {
        Wezel *nowy = utworzWezel(m);
        if (*glowa == NULL) *glowa = nowy;
        else {
            Wezel *t = *glowa;
            while(t->nastepny) t=t->nastepny;
            t->nastepny = nowy;
        }
    }
    fclose(f);
}

void wyszukajPoModelu(Wezel *glowa) {
    char s[100]; printf("Model: "); scanf("%s", s);
    while(glowa) {
        if(strstr(glowa->dane.model, s)) printf("ZNALEZIONO: %s\n", glowa->dane.model);
        glowa = glowa->nastepny;
    }
}

void usunMecha(Wezel **glowa) {
    char s[100]; printf("Model do usuniecia: "); scanf("%s", s);
    Wezel *curr = *glowa, *prev = NULL;
    while(curr) {
        if(strcmp(curr->dane.model, s)==0) {
            if(prev) prev->nastepny = curr->nastepny;
            else *glowa = curr->nastepny;
            free(curr);
            printf("Usunieto.\n");
            return;
        }
        prev = curr;
        curr = curr->nastepny;
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
