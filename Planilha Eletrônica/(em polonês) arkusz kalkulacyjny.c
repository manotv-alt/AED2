#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAKS_ALUMNÓW 10
#define MAKS_FORMUŁA 100
#define MAKS_STOS 100

// Struktura do przechowywania informacji o studentach
typedef struct {
    float egzamin1;
    float egzamin2;
    float frekwencja;
} Student;

// Stos używany do konwersji i oceny
typedef struct {
    char elementy[MAKS_STOS];
    int szczyt;
} StosChar;

typedef struct {
    float elementy[MAKS_STOS];
    int szczyt;
} StosFloat;

// Funkcje stosu dla typu char
void inicjalizujStosChar(StosChar *s) {
    s->szczyt = -1;
}

int stosPustyChar(StosChar *s) {
    return s->szczyt == -1;
}

void wlozChar(StosChar *s, char wartosc) {
    if (s->szczyt < MAKS_STOS - 1) {
        s->elementy[++(s->szczyt)] = wartosc;
    }
}

char wyjmijChar(StosChar *s) {
    if (!stosPustyChar(s)) {
        return s->elementy[(s->szczyt)--];
    }
    return '\0'; // Błąd: stos pusty
}

char szczytChar(StosChar *s) {
    if (!stosPustyChar(s)) {
        return s->elementy[s->szczyt];
    }
    return '\0'; // Błąd: stos pusty
}

// Funkcje stosu dla typu float
void inicjalizujStosFloat(StosFloat *s) {
    s->szczyt = -1;
}

int stosPustyFloat(StosFloat *s) {
    return s->szczyt == -1;
}

void wlozFloat(StosFloat *s, float wartosc) {
    if (s->szczyt < MAKS_STOS - 1) {
        s->elementy[++(s->szczyt)] = wartosc;
    }
}

float wyjmijFloat(StosFloat *s) {
    if (!stosPustyFloat(s)) {
        return s->elementy[(s->szczyt)--];
    }
    return 0; // Błąd: stos pusty
}

// Funkcja do określenia precedencji operatorów
int precedencja(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
    }
    return -1; // Nieprawidłowy operator
}

// Funkcja konwertująca wyrażenie infiksowe na postfiksowe (notacja odwrotna polska)
void infiksNaPostfiks(char* infiks, char* postfiks) {
    StosChar stos;
    inicjalizujStosChar(&stos);
    int j = 0;

    for (int i = 0; infiks[i] != '\0'; i++) {
        char c = infiks[i];

        // Jeśli to operand (E1, E2, F), dodaj do wyjścia
        if (isalnum(c)) {
            postfiks[j++] = c;
        }
        // Jeśli to nawias otwierający, włóż na stos
        else if (c == '(') {
            wlozChar(&stos, c);
        }
        // Jeśli to nawias zamykający, wyjmuj aż do nawiasu otwierającego
        else if (c == ')') {
            while (!stosPustyChar(&stos) && szczytChar(&stos) != '(') {
                postfiks[j++] = wyjmijChar(&stos);
            }
            wyjmijChar(&stos); // Usuń '(' ze stosu
        }
        // Jeśli to operator, wyjmuj operatory o wyższej lub równej precedencji i włóż bieżący operator
        else if (strchr("+-*/", c)) {
            while (!stosPustyChar(&stos) && precedencja(szczytChar(&stos)) >= precedencja(c)) {
                postfiks[j++] = wyjmijChar(&stos);
            }
            wlozChar(&stos, c);
        }
    }

    // Wyjmij to, co zostało na stosie
    while (!stosPustyChar(&stos)) {
        postfiks[j++] = wyjmijChar(&stos);
    }

    postfiks[j] = '\0'; // Zakończenie ciągu znaków
}

// Funkcja do oceny wyrażenia postfiksowego
float ocenPostfiks(char* postfiks, Student student) {
    StosFloat stos;
    inicjalizujStosFloat(&stos);
    
    for (int i = 0; postfiks[i] != '\0'; i++) {
        char c = postfiks[i];

        // Jeśli to operand, włóż odpowiednią wartość
        if (c == 'E') {
            i++; // Przejdź do numeru egzaminu
            if (postfiks[i] == '1') {
                wlozFloat(&stos, student.egzamin1);
            } else if (postfiks[i] == '2') {
                wlozFloat(&stos, student.egzamin2);
            }
        } else if (c == 'F') {
            wlozFloat(&stos, student.frekwencja);
        }
        // Jeśli to operator, wyjmij dwa operandy, wykonaj operację i włóż wynik
        else if (strchr("+-*/", c)) {
            float operand2 = wyjmijFloat(&stos);
            float operand1 = wyjmijFloat(&stos);

            switch (c) {
                case '+':
                    wlozFloat(&stos, operand1 + operand2);
                    break;
                case '-':
                    wlozFloat(&stos, operand1 - operand2);
                    break;
                case '*':
                    wlozFloat(&stos, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        wlozFloat(&stos, operand1 / operand2);
                    } else {
                        printf("Błąd: Dzielenie przez zero.\n");
                        return 0;
                    }
                    break;
            }
        }
    }

    return wyjmijFloat(&stos); // Ostateczny wynik będzie jedyną pozostałą wartością na stosie
}

int main() {
    int liczbaStudentów;
    Student studenci[MAKS_ALUMNÓW];
    char formuła[MAKS_FORMUŁA], postfiks[MAKS_FORMUŁA];

    // Pytanie o liczbę studentów
    printf("Podaj liczbę studentów (maksymalnie %d): ", MAKS_ALUMNÓW);
    scanf("%d", &liczbaStudentów);

    // Wprowadzanie danych dla każdego studenta
    for (int i = 0; i < liczbaStudentów; i++) {
        printf("\nStudent %d:\n", i + 1);

        printf("Wynik Egzaminu 1: ");
        scanf("%f", &studenci[i].egzamin1);

        printf("Wynik Egzaminu 2: ");
        scanf("%f", &studenci[i].egzamin2);

        printf("Frekwencja (w %%): ");
        scanf("%f", &studenci[i].frekwencja);
    }

    // Odczyt formuły do obliczania średniej
    printf("\nPodaj formułę do obliczania średniej (użyj E1, E2, F): ");
    scanf("%s", formuła);

    // Konwersja formuły infiksowej na postfiksową
    infiksNaPostfiks(formuła, postfiks);
    printf("Formuła w notacji postfiksowej: %s\n", postfiks);

    // Obliczanie średniej dla każdego studenta za pomocą formuły postfiksowej
    for (int i = 0; i < liczbaStudentów; i++) {
        float średnia = ocenPostfiks(postfiks, studenci[i]);
        printf("Średnia końcowa studenta %d: %.2f\n", i + 1, średnia);
    }

    return 0;
}
