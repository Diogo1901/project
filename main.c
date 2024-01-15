/**
 * @file main.c
 * @brief Main program for the Companies360 - Company Management System.
 *
 * This program allows users to interact with the system using either the Administrator or User profiles.
 * Administrators can manage the catalog of companies, business sectors, view reports, and perform other specific operations.
 * Users can search for companies, rate, and comment on them.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 8-12-2024
 * @version 1.0
 *
 *
 * @return 0 on successful execution.
 */

#include "adm.h"
#include "user.h"
#include "utilities.h"
#include "report.h"


int main(int argc, char** argv) {

        int choice;
        int option;
        int suboption;
        int nif;  
        int userChoice;
        int mainOption;
        int subOption1;
        int subOption2;

    BusinessSectorList sectorList;
    Comment *comments;
    int numComments;

        numCompanies = loadCompanyCount();
        loadCommentsFromFile(companies, &numCompanies);
        loadRatingsFromFile(companies, numCompanies);
        loadCompaniesFromFile(companies, &numCompanies);


    do {
            printf("Companies360 - Company Management System\n");
            printf("\nWhich profile do you want to use?");
            printf("\n1-Administrator");
            printf("\n2-User");
            printf("\n3-Exit\n");
            printf("->");
            scanf("%d", &mainOption);

            switch (mainOption) {
                case 1:
                    printf("\nAdministrator Profile");

                    do {
                        printf("\n1-Manage Catalog");
                        printf("\n2-Manage Business Sector");
                        printf("\n3-View Reports");
                        printf("\n4-Back\n");
                        printf("->");
                        scanf("%d", &subOption1);

                        switch (subOption1) {
                            case 1:
                                do {
                                    printf("\n1-Create Company\n");
                                    printf("2-Edit Company\n");
                                    printf("3-Remove Company\n");
                                    printf("4-List Companies\n");
                                    printf("5-Back\n->");
                                    scanf("%d", &subOption2);

                                    switch (subOption2) {
                                        case 1:
                                            createCompany();
                                            break;
                                        case 2:
                                            editCompany();
                                            break;
                                        case 3:
                                            removeCompany(companies, &numCompanies);
                                            break;
                                        case 4:
                                           listCompanies(companies, numCompanies);
                                            break;
                                        default:
                                            printf("Invalid option.\n");
                                    }
                                } while (subOption2 != 5);
                                break;

                            case 2:
                                do {
                                    printf("\n1-Create Business Sector\n");
                                    printf("2-Remove Business Sector\n");
                                    printf("3-Change Business Sector Status\n");
                                    printf("4-List All Business Sectors\n");
                                    printf("5-Back\n->");
                                    scanf("%d", &subOption2);

                                    switch (subOption2) {
                                        case 1:
                                            createBusinessSector(&sectorList);
                                            break;
                                        case 2:
                                            removeBusinessSector();
                                            break;
                                        case 3:
                                            changeBusinessStatus();
                                            break;
                                        case 4:
                                            listAllBusinessSectors();
                                            break;
                                        default:
                                            printf("Invalid option.\n");
                                    }
                                } while (subOption2 != 5);
                                break;

                            case 3:
                                viewReports();
                                break;

                            case 4:
                                printf("Returning to the main page...");
                                break;

                            default:
                                break;
                        }

                    } while (subOption1 != 4);
                    break;

                case 2:
                    printf("\nUser Profile");

                    do {
                        printf("\n1. Search Companies\n");
                        printf("2. Rate Company\n");
                        printf("3. Comment on Company\n");
                        printf("4. Exit\n");
                        printf("-> ");
                        scanf("%d", &userChoice);

                        switch (userChoice) {
                            case 1:
                                searchCompanies(companies, numCompanies);
                                break;
                            case 2:
                                rateCompany(companies, numCompanies);
                                break;
                            case 3:
                                commentCompany(comments, &numComments);
                                break;
                            case 4:
                                printf("Exiting...\n");
                                break;
                            default:
                                printf("Invalid option. Please try again.\n");
                                break;
                        }
                    } while (userChoice != 4);
                    break;

                default:
                    printf("\nInvalid character");
                    break;
            }

        } while (mainOption != 3);

            saveCompaniesToFile(companies, 1);


        return (EXIT_SUCCESS);
    }


