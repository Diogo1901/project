/**
 * @file user.c
 * @brief source file for user-related functionalities in the Company Management System.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 01-01-2024
 *

 */
#include "utilities.h"
#include "adm.h"
#include "user.h"

void searchCompanies(Company companies[], int numCompanies) {
       char searchTerm[100];
        int criteria;

        printf("Choose the search criterion:\n");
        printf("1. Name\n");
        printf("2. Category\n");
        printf("3. Locality\n");
        printf("Enter the criterion number: ");
        scanf("%d", &criteria);

        printf("Enter the search term: ");
        scanf("%s", searchTerm);

        int resultFound = 0; 


        switch (criteria) {
            case 1:
                // Search by name
                for (int i = 0; i < numCompanies; i++) {
                    if (strstr(companies[i].name, searchTerm) != NULL) {
                        printf("Name: %s\nCategory: %s\nBusiness Sector: %s\nLocality: %s\nPostal Code: %s\n\n",
                                companies[i].name, companies[i].category, companies[i].businessSector,
                                companies[i].locality, companies[i].postalCode);
                        resultFound = 1;
                    }
                }
                break;
            case 2:
                // Search by category
                for (int i = 0; i < numCompanies; i++) {
                    if (strstr(companies[i].category, searchTerm) != NULL) {
                        printf("Name: %s\nCategory: %s\nBusiness Sector: %s\nLocality: %s\nPostal Code: %s\n\n",
                                companies[i].name, companies[i].category, companies[i].businessSector,
                                companies[i].locality, companies[i].postalCode);
                        resultFound = 1;
                    }

                printf("NIF: %-5d\n", companies[i].nif);
                printf("Name: %-15s\n", companies[i].name);
                printf("Category: %-15s\n", companies[i].category);
                printf("Business Sector: %-20s\n", companies[i].businessSector);
                printf("Street: %-15s\n", companies[i].street);
                printf("Locality: %-15s\n", companies[i].locality);
                printf("Postal Code: %-10s\n", companies[i].postalCode);
                printf("Active: %-10s\n", companies[i].active ? "Yes" : "No");
                }
                break;
            case 3:
                // Search by locality
                for (int i = 0; i < numCompanies; i++) {
                    if (strstr(companies[i].locality, searchTerm) != NULL) {
                        printf("Name: %s\nCategory: %s\nBusiness Sector: %s\nLocality: %s\nPostal Code: %s\n\n",
                                companies[i].name, companies[i].category, companies[i].businessSector,
                                companies[i].locality, companies[i].postalCode);
                        resultFound = 1;
                    }
                }
                break;
            default:
                printf("Invalid search criterion.\n");
        }

        if (!resultFound) {
            printf("No results found for the provided search criterion.\n");
        }
    }

    void rateCompany(Company companies[], int numCompanies) {
        printf("Companies available for rating:\n");

        for (int i = 0; i < numCompanies; i++) {
            printf("%d. %s\n", i + 1, companies[i].name);
        }

        int choice;
        printf("Choose the company to rate: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= numCompanies) {
            int index = choice - 1;

            float rating;
            printf("Enter the rating (from 1 to 5) for %s: ", companies[index].name);
            scanf("%f", &rating);

            if (rating >= 1 && rating <= 5) {
                // Add the rating to the ratings array
                companies[index].ratings[companies[index].numRatings++] = rating;

                // Update the average rating
                float sum = 0;
                for (int i = 0; i < companies[index].numRatings; i++) {
                    sum += companies[index].ratings[i];
                }
                companies[index].averageRating = sum / companies[index].numRatings;

                printf("Company %s rated successfully!\n", companies[index].name);

                saveRatingsToFile(companies, numCompanies);
            } else {
                printf("Invalid rating. Please try again.\n");
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

void commentCompany(Comment comments[], int *numComments){

        int numCompanies = loadCompanyCount();
        loadCompaniesFromFile(companies, &numCompanies);
        int choice;
        printf("Companies available for commenting:\n");

        for (int i = 0; i < numCompanies; i++) {
            printf("%d. %s\n", i + 1, companies[i].name);
        }

        printf("Choose the company to comment on: ");
        scanf("%d", &choice);

       if (choice >= 1 && choice <= numCompanies) {
            int index = choice - 1;

            if (companies[index].numComments < MAX_COMMENTS) {

                printf("Enter your name: ");
                scanf("%s", companies[index].comments[companies[index].numComments].username);

                printf("Enter the comment title: ");
                scanf("%s", companies[index].comments[companies[index].numComments].title);

                printf("Enter the comment text: ");
                getchar();
                fgets(companies[index].comments[companies[index].numComments].text,
                      sizeof(companies[index].comments[0].text), stdin);

                companies[index].numComments++;

                printf("Comment added successfully!\n");


                saveCommentsToFile(companies, numCompanies);
            } else {
                printf("Maximum comment limit reached for this company.\n");
            }
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
