/**
 * @file report.c
 * @brief source file for generating and viewing reports on company evaluations and information.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 11-01-2024
 *

 */

#include "utilities.h"
#include "adm.h"
#include "user.h"
#include "report.h"

    void viewReports() {
        int numCompanies = loadCompanyCount();
        loadCompaniesFromFile(companies, &numCompanies);
        loadCommentsFromFile(companies, &numCompanies);
        loadRatingsFromFile(companies, numCompanies);

        printf("\nList of Companies:\n");

        for (int i = 0; i < numCompanies; i++) {
            printf("%d. %s\n", i + 1, companies[i].name);
        }

        int choice;
        printf("Select a company to view report: ");
        scanf("%d", &choice);

        getchar();

        if (choice >= 1 && choice <= numCompanies) {
            int selectedCompanyId = choice - 1;
            Company selectedCompany = companies[selectedCompanyId];

            char fileName[100];
            sprintf(fileName, "%s_report.txt", selectedCompany.name);

            printf("\nCompany Details:\n");
            printf("Name: %s\n", selectedCompany.name);
            printf("NIF: %d\n", selectedCompany.nif);
            printf("Category: %s\n", selectedCompany.category);
            printf("Business Sector: %s\n", selectedCompany.businessSector);
            printf("Street: %s\n", selectedCompany.street);
            printf("Locality: %s\n", selectedCompany.locality);
            printf("Postal Code: %s\n", selectedCompany.postalCode);
            printf("Status: %s\n", selectedCompany.active ? "Active" : "Inactive");
            printf("Average Rating: %.2f\n", selectedCompany.averageRating);

            printf("\nLast Comment:\n");
            for (int i = 0; i < selectedCompany.numComments; i++) {
                printf("Username: %s\n", selectedCompany.comments[i].username);
                printf("Title: %s\n", selectedCompany.comments[i].title);
                printf("Text: %s\n", selectedCompany.comments[i].text);
                printf("\n");
            }

            printf("\nRatings:\n");
            for (int i = 0; i < selectedCompany.numRatings; i++) {
                printf("%.2f ", selectedCompany.ratings[i]);
            }
            printf("\n");

            FILE *file = fopen(fileName, "w");
            if (file == NULL) {
                printf("Error opening the file for writing.\n");
                return;
            }

            fprintf(file, "\nCompany Details:\n");
            fprintf(file, "Name: %s\n", selectedCompany.name);
            fprintf(file, "NIF: %d\n", selectedCompany.nif);
            fprintf(file, "Category: %s\n", selectedCompany.category);
            fprintf(file, "Business Sector: %s\n", selectedCompany.businessSector);
            fprintf(file, "Street: %s\n", selectedCompany.street);
            fprintf(file, "Locality: %s\n", selectedCompany.locality);
            fprintf(file, "Postal Code: %s\n", selectedCompany.postalCode);
            fprintf(file, "Status: %s\n", selectedCompany.active ? "Active" : "Inactive");
            fprintf(file, "Average Rating: %.2f\n", selectedCompany.averageRating);

            fprintf(file, "\nLast Comment:\n");
            for (int i = 0; i < selectedCompany.numComments; i++) {
                fprintf(file, "Username: %s\n", selectedCompany.comments[i].username);
                fprintf(file, "Title: %s\n", selectedCompany.comments[i].title);
                fprintf(file, "Text: %s\n", selectedCompany.comments[i].text);
                fprintf(file, "\n");
            }

            fprintf(file, "\nRatings:\n");
            for (int i = 0; i < selectedCompany.numRatings; i++) {
                fprintf(file, "%.2f ", selectedCompany.ratings[i]);
            }
            fprintf(file, "\n");

            fclose(file);

            printf("Relatório salvo em %s\n", fileName);
        } else {
            printf("Escolha inválida. Por favor, tente novamente.\n");
        }
    }

