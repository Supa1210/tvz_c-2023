/*
  Potrebno je iz baze vozača izvući one koji žive u danom gradu, poredano po registraciji abecedno.
  Jedan zapis u datoteci car-data.dat izgleda ovako:
    char grad[100];
    char reg[9]; - registracija
    char name[100]; - ime vozača
    char surname[100]; - prezime vozača
    char street[200]; - ulica vozača
    int month; - mjesec izdavanja vozačke dozvole
    int day; - dan izdavanja vozačke dozvole
    int year; - godina izdavanja vozačke dozvole
    char category[3]; - kategorija (slovo i znamenka)
  Izlazna datoteka: rezultat.out
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_STR 100

typedef struct {
	char grad[100];
	char reg[9];
	char name[100];
	char surname[100];
	char street[200];
	int month;
	int day;
	int year;
	char category[3];
} osoba;

void sortirajOsobe(osoba *niz, int n) {
	for(int i = 0; i < n - 1; i++) {
		for(int j = i + 1; j < n; j++) {
			for(int c = 0; c < strlen(niz[i].reg) && c < strlen(niz[j].reg); c++) {
				if(niz[i].reg[c] < niz[j].reg[c]) break;
				if(niz[i].reg[c] > niz[j].reg[c]) {
					osoba tmp = niz[i];
					niz[i] = niz[j];
					niz[j] = tmp;
					break;
				}
			}
		}
	}
}

int main(void) {
	FILE *fin;
	fin = fopen("./car-data.dat", "rb");
	fseek(fin, 0L, SEEK_END);
	int file_size = ftell(fin);
	fseek(fin, 0L, SEEK_SET);
	
	int num_osoba = file_size / sizeof(osoba);
	osoba db[num_osoba];
	fread(db, sizeof(osoba), num_osoba, fin);
	fclose(fin);
	
	char grad[MAX_STR];
	fgets(grad, MAX_STR, stdin);
	// Izbriši new line
	grad[strlen(grad) - 1] = 0;
	
	// Radi memorijske optimizacije, prvo odredi broj elemenata završnog niza
	int cnt = 0;
	for(int i = 0; i < num_osoba; i++) {
		if(strcmp(db[i].grad, grad) == 0) cnt++;
	}
	
	osoba trazeni[cnt];
	cnt = 0;
	for(int i = 0; i < num_osoba; i++) {
		if(strcmp(db[i].grad, grad) == 0) {
			trazeni[cnt] = db[i];
			cnt++;
		}
	}
	
	// Nije određeno da li je output file binary ili ne
	// Zbog jednostavnosti, pretpostavimo da je plain text
	FILE *fout;
	fout = fopen("./rezultat.out", "w");
	
	if(cnt == 0) {
		fprintf(fout, "Nepoznati grad!\n");
		return 0;
	}
	
	sortirajOsobe(trazeni, cnt);
	
	for(int i = 0; i < cnt; i++) {
		//printf("%s %s %s\n", trazeni[i].reg, trazeni[i].name, trazeni[i].surname);
		// Zbog pretpostavke da je out file plain text
		fprintf(fout, "%s %s %s\n", trazeni[i].reg, trazeni[i].name, trazeni[i].surname);
	}
	
	fclose(fout);
	
	return 0; // - Supa@FER
}
