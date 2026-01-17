#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcje.h"

void wyswietlMenu() {
    printf("\n=== SYSTEM OBSLUGI FLOTY MECHOW (LISTA) ===\n");
    printf("1. Dodaj mecha\n");
    printf("2. Wyswietl flote\n");
    printf("3. Zapisz do pliku\n");
    printf("4. Wczytaj z pliku\n");
    printf("5. Szukaj (Model)\n");
    printf("6. Szukaj (Moc > X)\n");
    printf("7. Edytuj mecha\n");
    printf("8. Usun mecha (pojedynczo)\n");
    printf("9. Usun wszystkie w 'demontaz' \n");
    printf("10. Sortuj (Model)\n");
    printf("11. Sortuj (Moc)\n");
    printf("0. Wyjscie\n");
    printf("Wybor: ");
}


Wezel* utworzWezel(Mech dane) {
    Wezel *nowy = (Wezel*)malloc(sizeof(Wezel));
    if (!nowy) {
        printf("[BLAD] Brak pamieci RAM!\n");
        return NULL;
    }
    nowy->dane = dane;
    nowy->nastepny = NULL;
    return nowy;
}

void dodajMecha(Wezel **glowa) {
    Mech m;
    printf("Podaj Model (ID): "); scanf("%s", m.model);
    
   
    Wezel *temp = *glowa;
    while(temp != NULL) {
        if(strcmp(temp->dane.model, m.model) == 0) {
            printf("[BLAD] Mech o modelu %s juz istnieje!\n", m.model);
            return;
        }
        temp = temp->nastepny;
    }

    printf("Klasa: "); scanf("%s", m.klasa);
    do {
        printf("Moc reaktora (0-100): ");
        if (scanf("%f", &m.moc) != 1) {
            while(getchar()!='\n'); 
            m.moc = -1;
        }
    } while(m.moc < 0 || m.moc > 100);

    printf("Pilot (lub 'brak'): "); scanf("%s", m.pilot);
    printf("Stan (sprawny/naprawa/demontaz): "); scanf("%s", m.stan);

    Wezel *nowy = utworzWezel(m);
    if (*glowa == NULL) {
        *glowa = nowy;
    } else {
        temp = *glowa;
        while (temp->nastepny != NULL) {
            temp = temp->nastepny;
        }
        temp->nastepny = nowy;
    }
    printf("[OK] Dodano do listy.\n");
}

void wyswietlWszystkie(Wezel *glowa) {
    if (!glowa) { printf("[INFO] Lista pusta.\n"); return; }
    
    printf("\n%-20s | %-15s | %-6s | %-15s | %-15s\n", "MODEL", "KLASA", "MOC", "PILOT", "STAN");
    printf("--------------------------------------------------------------------------------\n");
    
    while (glowa != NULL) {
        printf("%-20s | %-15s | %-6.1f | %-15s | %-15s\n", 
               glowa->dane.model, glowa->dane.klasa, glowa->dane.moc, glowa->dane.pilot, glowa->dane.stan);
        glowa = glowa->nastepny;
    }
}

void zapiszDoPliku(Wezel *glowa, const char *nazwaPliku) {
    FILE *f = fopen(nazwaPliku, "w");
    if (!f) { printf("[BLAD] Nie udalo sie otworzyc pliku do zapisu.\n"); return; }

    while (glowa != NULL) {
        fprintf(f, "%s %s %.2f %s %s\n", 
            glowa->dane.model, glowa->dane.klasa, glowa->dane.moc, glowa->dane.pilot, glowa->dane.stan);
        glowa = glowa->nastepny;
    }
    fclose(f);
    printf("[OK] Zapisano dane.\n");
}

void wczytajZPliku(Wezel **glowa, const char *nazwaPliku) {
    FILE *f = fopen(nazwaPliku, "r");
    if (!f) { printf("[INFO] Brak pliku, zaczynamy z pusta lista.\n"); return; }

    zwolnijPamiec(glowa);

    Mech m;
    while (fscanf(f, "%s %s %f %s %s", m.model, m.klasa, &m.moc, m.pilot, m.stan) == 5) {
        Wezel *nowy = utworzWezel(m);
        if (*glowa == NULL) {
            *glowa = nowy;
        } else {
            Wezel *temp = *glowa;
            while (temp->nastepny != NULL) temp = temp->nastepny;
            temp->nastepny = nowy;
        }
    }
    fclose(f);
    printf("[OK] Wczytano dane z pliku.\n");
}

void wyszukajPoModelu(Wezel *glowa) {
    char s[100]; printf("Podaj szukany model: "); scanf("%s", s);
    int found = 0;
    while(glowa) {
        if (strstr(glowa->dane.model, s) == glowa->dane.model) { 
            printf("ZNALEZIONO: %s (Stan: %s)\n", glowa->dane.model, glowa->dane.stan);
            found = 1;
        }
        glowa = glowa->nastepny;
    }
    if(!found) printf("Brak wynikow.\n");
}

void wyszukajPowyzejMocy(Wezel *glowa) {
    float prog; printf("Pokaz mechy o mocy wiekszej niz: "); scanf("%f", &prog);
    int found = 0;
    while(glowa) {
        if (glowa->dane.moc > prog) {
            printf("SILNY MECH: %s (%.1f MW)\n", glowa->dane.model, glowa->dane.moc);
            found = 1;
        }
        glowa = glowa->nastepny;
    }
    if(!found) printf("Brak tak poteznych mechow.\n");
}

void edytujMecha(Wezel *glowa) {
    char s[100]; printf("Podaj model do edycji: "); scanf("%s", s);
    while(glowa) {
        if (strcmp(glowa->dane.model, s) == 0) {
            printf("Edycja mecha %s. [Model zablokowany]\n", s);
            printf("Nowa klasa: "); scanf("%s", glowa->dane.klasa);
            printf("Nowy pilot: "); scanf("%s", glowa->dane.pilot);
            printf("Nowy stan (sprawny/naprawa/demontaz):"); scanf("%s", glowa->dane.stan);
            do {
                 printf("Nowa moc: "); scanf("%f", &glowa->dane.moc);
            } while(glowa->dane.moc < 0 || glowa->dane.moc > 100);
            return;
        }
        glowa = glowa->nastepny;
    }
    printf("Nie znaleziono.\n");
}

void usunMecha(Wezel **glowa) {
    char s[100]; printf("Podaj model do usuniecia: "); scanf("%s", s);
    
    Wezel *obecny = *glowa;
    Wezel *poprzedni = NULL;

    while (obecny != NULL) {
        if (strcmp(obecny->dane.model, s) == 0) {
            if (strcmp(obecny->dane.stan, "naprawa") != 0 && strcmp(obecny->dane.stan, "demontaz") != 0) {
                printf("[BLAD] Nie mozna usunac! Mech musi byc w naprawie lub demontazu.\n");
                return;
            }

            
            if (poprzedni == NULL) {
                *glowa = obecny->nastepny; 
            } else {
                poprzedni->nastepny = obecny->nastepny; 
            }
            free(obecny);
            printf("[OK] Usunieto element.\n");
            return;
        }
        poprzedni = obecny;
        obecny = obecny->nastepny;
    }
    printf("Nie znaleziono.\n");
}

void usunWszystkieWDemontazu(Wezel **glowa) {
    Wezel *obecny = *glowa;
    Wezel *poprzedni = NULL;
    int licznik = 0;

    while (obecny != NULL) {
        if (strcmp(obecny->dane.stan, "demontaz") == 0) {
            Wezel *doUsuniecia = obecny;
            if (poprzedni == NULL) {
                *glowa = obecny->nastepny;
                obecny = *glowa;
            } else {
                poprzedni->nastepny = obecny->nastepny;
                obecny = poprzedni->nastepny;
            }
            free(doUsuniecia);
            licznik++;
        } else {
            poprzedni = obecny;
            obecny = obecny->nastepny;
        }
    }
    printf("[OK] Wyczyszczono %d mechow przeznaczonych do demontazu.\n", licznik);
}

void sortujPoModelu(Wezel *glowa) {
    if (!glowa) return;
    int zamiana;
    do {
        zamiana = 0;
        Wezel *ptr = glowa;
        while (ptr->nastepny != NULL) {
            if (strcmp(ptr->dane.model, ptr->nastepny->dane.model) > 0) {
                Mech temp = ptr->dane;
                ptr->dane = ptr->nastepny->dane;
                ptr->nastepny->dane = temp;
                zamiana = 1;
            }
            ptr = ptr->nastepny;
        }
    } while (zamiana);
    printf("[OK] Posortowano alfabetycznie.\n");
    wyswietlWszystkie(glowa);
}

void sortujPoMocy(Wezel *glowa) {
    if (!glowa) return;
    int zamiana;
    do {
        zamiana = 0;
        Wezel *ptr = glowa;
        while (ptr->nastepny != NULL) {
            if (ptr->dane.moc < ptr->nastepny->dane.moc) { 
                Mech temp = ptr->dane;
                ptr->dane = ptr->nastepny->dane;
                ptr->nastepny->dane = temp;
                zamiana = 1;
            }
            ptr = ptr->nastepny;
        }
    } while (zamiana);
    printf("[OK] Posortowano wg mocy.\n");
    wyswietlWszystkie(glowa);
}

void zwolnijPamiec(Wezel **glowa) {
    Wezel *obecny = *glowa;
    while (obecny != NULL) {
        Wezel *temp = obecny;
        obecny = obecny->nastepny;
        free(temp);
    }
    *glowa = NULL;
}
