#include <stdio.h>

void print_annuary() {
    FILE *file;
    char buffer[256];

    file = fopen("annuaire.txt", "r");

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s\n", buffer);
    }
}

void write_annuary() {
    FILE *file;
    char name[50];
    char nickname[50];

    printf("Quel est votre prénom : ");
    scanf("%s", &name);

    printf("Quel est votre nom : ");
    scanf("%s", &nickname);

    file = fopen("annuaire.txt", "a");

    fprintf(file, "%s %s\n", nickname, name);
        
    fclose(file);
}

void annuary() {
    int choice;
        while (choice != 3) {
        printf("=== Menu de l'annuaire ===\n"
            "1. Voir l'annuaire\n"
            "2. AJouter une nom & prénom\n"
            "3. Quitter\n"
            "Veuillez entrer votre choix : ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            print_annuary();
        } else if (choice == 2) {
            write_annuary();
        } else if (choice == 3) {
            printf("Arrête de l'annuaire");
        } else {
            printf("Veuillez entrer un numéro valide !");
        }
    }

}

int main() {
    annuary();
}