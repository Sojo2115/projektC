#ifndef FUNKCJE_H
#define FUNKCJE_H

typedef struct {
    char model[100];
    char klasa[50];
    float moc;
    char pilot[100];
    char stan[50];
} Mech;

typedef struct Wezel {
    Mech dane;
    struct Wezel *nastepny;
} Wezel;

void wyswietlMenu();
void dodajMecha(Wezel **glowa);
void wyswietlWszystkie(Wezel *glowa);
void zwolnijPamiec(Wezel **glowa);

#endif
