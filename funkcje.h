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

// --- DEKLARACJE FUNKCJI ---

void wyswietlMenu();

void dodajMecha(Wezel **glowa);
void wczytajZPliku(Wezel **glowa, const char *nazwaPliku);
void zapiszDoPliku(Wezel *glowa, const char *nazwaPliku);

void wyswietlWszystkie(Wezel *glowa);
void wyszukajPoModelu(Wezel *glowa);      
void wyszukajPowyzejMocy(Wezel *glowa);   

void usunMecha(Wezel **glowa);           
void usunWszystkieWDemontazu(Wezel **glowa); 
void edytujMecha(Wezel *glowa);

void sortujPoModelu(Wezel *glowa);
void sortujPoMocy(Wezel *glowa);

void zwolnijPamiec(Wezel **glowa);

#endif
