#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>



struct Student {

	int Numar_matricol;
	char nume[20];
	int an;
	int grupa;
	char serie;
	float note[10];
};

void creare_binara() {
	Student s;
	char continua = 'y';
	FILE* f = fopen("Studenti", "wb+");
	if (!f) {
		printf("nu s-a deschis");
		return;
	}
	else {
		while (continua == 'y') {
			printf("Numar matricol: ");
			scanf_s("%d", &s.Numar_matricol);
			printf("nume");
			scanf_s("%s", s.nume, 20);
			printf("an ,grupa ,serie: ");
			scanf_s("%d", &s.an);
			scanf_s("%d", &s.grupa);

			while (getchar() != '\n');
			scanf_s("%c", &s.serie, 1);

			printf("note (10 in total): ");
			for (int i = 0; i < 10; i++) {
				scanf_s("%f", &s.note[i]);
			}

			fseek(f, s.Numar_matricol * sizeof(Student), SEEK_SET); //Mutăm indicatorul de scriere la poziția corespunzătoare numărului matricol pentru a permite accesul aleatoriu și a evita duplicarea datelor.
			fwrite(&s, sizeof Student, 1, f);

			while (getchar() != '\n');
			printf("continuati? ");
			scanf_s("%c", &continua,1);
		}
		
	}
	fclose(f);
}

/* blocul " creare_binara " calculează media notelor și scrie într-un fișier text studenții performanți apoi
  citește din fișierul binar "Studenti" și scrie în "Medii_mari.txt".*/

void listare_medii8() {
	Student s;
	FILE* g = fopen("Medii_mari.txt", "w");
	FILE* f = fopen("Studenti", "rb");
	if (!f || !g) {
		printf("nu s-au deschis la etapa 2 ");
		return;
	}
	fprintf(g, "Matricol | Nume                     | Medie\n ");
	fprintf(g, "---------------------------------------------\n");

	while (fread(&s, sizeof(Student), 1, f) == 1) {
		if (s.Numar_matricol > 0) {
			float medie = 0.00f;
			float S = 0.00f;

			for (int i = 0; i < 10; i++) {
				S = s.note[i] + S;
			}
			medie = S / 10.0f;
			if (medie > 8.0f) {
				fprintf(g, "%8d | ", s.Numar_matricol);
				fprintf(g, "%-20s | ", s.nume);
				fprintf(g, "%.2f\n", medie);
			}
		}
	}
	fclose(g);
	fclose(f);

	printf("Raportul tabelar a fost generat in 'Medii_mari.txt'!\n");
}

int main() {
	creare_binara();
	listare_medii8();

	return 0;
}
