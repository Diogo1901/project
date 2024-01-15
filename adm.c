/**
 * @file adm.c
 * @brief This file contains function related to administrator actions, such as creating and managing
 * business sectors, editing and removing companies, listing all business sectors and companies, and changing
 * the status of business sectors.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 1-01-2024
 *

 */

#include "utilities.h"
#include "adm.h"

void createBusinessSector() {
        printf("Enter data for the new business sector:\n");

        BusinessSector* businessSectors;
        int numBusinessSectors;

        loadBusinessSectorsFromFile(&businessSectors, &numBusinessSectors);

        businessSectors = realloc(businessSectors, (numBusinessSectors + 1) * sizeof(BusinessSector));

        if (businessSectors == NULL) {
            printf("Memory allocation error.\n");
            return;
        }

        printf("Name of Business Sector: ");
        scanf(" %[^\n]", businessSectors[numBusinessSectors].name);


        businessSectors[numBusinessSectors].isActive = true;

        numBusinessSectors++;

        saveBusinessSectorsToFile(businessSectors, numBusinessSectors);

        free(businessSectors);

        printf("Business sector created successfully!\n");
    }

    void listAllBusinessSectors() {
        int numBusinessSectors;
        BusinessSector* businessSectors;

        loadBusinessSectorsFromFile(&businessSectors, &numBusinessSectors);

        if (numBusinessSectors == 0) {
            printf("No business sectors found.\n");
        } else {
            printf("List of business sectors:\n");

            for (int i = 0; i < numBusinessSectors; ++i) {
                printf("%d. %s - Status: %s\n", i + 1, businessSectors[i].name, businessSectors[i].isActive ? "Active" : "Inactive");
            }
        }

        free(businessSectors);
    }

    int chooseBusinessSector(BusinessSectorList* sectorList) {
        if ((*sectorList).numSectors == 0) {
            printf("\nNo business sectors available.\nPlease create a business sector after and then edit this company.\n\n");
            return -1;
        }

        printf("\nChoose a business sector:\n");

        for (int i = 0; i < (*sectorList).numSectors; i++) {
            printf("%d. %s\n", i + 1, (*sectorList).sectors[i]);
        }

        int choice;
        printf("Enter the number corresponding to your choice: ");
        scanf("%d", &choice);


        int c;
        while ((c = getchar()) != '\n' && c != EOF);


        if (choice < 1 || choice > (*sectorList).numSectors) {
            printf("Invalid choice. Please enter a valid number.\n");
            return -1;
        }

        return choice - 1;
    }

    void removeBusinessSector() {
        int numBusinessSectors;
        BusinessSector* businessSectors;

        loadBusinessSectorsFromFile(&businessSectors, &numBusinessSectors);

        if (numBusinessSectors == 0) {
            printf("No business sectors found.\n");
        } else {
            printf("List of business sectors:\n");

            for (int i = 0; i < numBusinessSectors; ++i) {
                printf("%d. %s - Status: %s\n", i + 1, businessSectors[i].name, businessSectors[i].isActive ? "Active" : "Inactive");
            }

            int sectorIndex;
            printf("Enter the index of the business sector to remove (1 to %d): ", numBusinessSectors);
            scanf("%d", &sectorIndex);

            if (sectorIndex < 1 || sectorIndex > numBusinessSectors) {
                printf("Invalid index.\n");
            } else {
                // Remove the selected business sector
                for (int i = sectorIndex - 1; i < numBusinessSectors - 1; ++i) {
                    businessSectors[i] = businessSectors[i + 1];
                }

                numBusinessSectors--;
                businessSectors = realloc(businessSectors, numBusinessSectors * sizeof(BusinessSector));

                if (businessSectors == NULL && numBusinessSectors > 0) {
                    printf("Memory reallocation error.\n");
                    return;
                }

                saveBusinessSectorsToFile(businessSectors, numBusinessSectors);
                printf("Business sector removed successfully!\n");
            }
        }

        free(businessSectors);
    }

    void changeBusinessStatus() {
        int numBusinessSectors;
        BusinessSector* businessSectors;

        loadBusinessSectorsFromFile(&businessSectors, &numBusinessSectors);

        if (numBusinessSectors == 0) {
            printf("No business sectors found.\n");
        } else {
            printf("List of business sectors:\n");

            for (int i = 0; i < numBusinessSectors; ++i) {
                printf("%d. %s - Status: %s\n", i + 1, businessSectors[i].name, businessSectors[i].isActive ? "Active" : "Inactive");
            }

            int sectorIndex;
            printf("Enter the index of the business sector to change status (1 to %d): ", numBusinessSectors);
            scanf("%d", &sectorIndex);

            if (sectorIndex < 1 || sectorIndex > numBusinessSectors) {
                printf("Invalid index.\n");
            } else {
                // Toggle the status (if active, make inactive; if inactive, make active)
                businessSectors[sectorIndex - 1].isActive = !businessSectors[sectorIndex - 1].isActive;
                saveBusinessSectorsToFile(businessSectors, numBusinessSectors);
                printf("Business sector status changed successfully!\n");
            }
        }
        free(businessSectors);
    }
    
    void createCompany() {
        printf("Enter data for the new company:\n");

        int numBusinessSectors;
        BusinessSector* businessSectors;

        loadBusinessSectorsFromFile(&businessSectors, &numBusinessSectors);

        if (numBusinessSectors == 0) {
            printf("No active business sectors found. Please create an active business sector first.\n");
            free(businessSectors);
            return;
        }

        printf("Active Business Sectors:\n");
        for (int i = 0; i < numBusinessSectors; ++i) {
            if (businessSectors[i].isActive) {
                printf("%d. %s\n", i + 1, businessSectors[i].name);
            }
        }

        int chosenIndex;
        printf("Choose an active Business Sector (1 to %d): ", numBusinessSectors);
        scanf("%d", &chosenIndex);

        // Validate the chosen index
        if (chosenIndex < 1 || chosenIndex > numBusinessSectors || !businessSectors[chosenIndex - 1].isActive) {
            printf("Invalid or inactive Business Sector chosen.\n");
            free(businessSectors);
            return;
        }

        Company* companies = (Company*)malloc(sizeof(Company));

        if (companies == NULL) {
            printf("Memory allocation error.\n");
            free(businessSectors);
            return;
        }

        printf("NIF: ");
        int nifInput;
        while (1) {
            if (scanf("%d", &nifInput) != 1 || (nifInput < 100000000 || nifInput > 999999999)) {
            printf("Invalid NIF. Please enter a 9-digit NIF.\n");
        
            while (getchar() != '\n');
        } else {
        break;
        }
    }
        companies->nif = nifInput;

        printf("Name: ");
        scanf(" %[^\n]", companies->name);

        
        do {
            printf("Category (MICRO, SMALL, MEDIUM, BIG): ");
            scanf(" %[^\n]", companies->category);

            
            if (strcmp(companies->category, "MICRO") == 0 || strcmp(companies->category, "SMALL") == 0 ||
                strcmp(companies->category, "MEDIUM") == 0 || strcmp(companies->category, "BIG") == 0) {
                break;
            } else {
                printf("Invalid category. Please enter MICRO, SMALL, MEDIUM, or BIG.\n");
            }
        } while (1);

        strcpy(companies->businessSector, businessSectors[chosenIndex - 1].name);

        printf("Street: ");
        scanf(" %[^\n]", companies->street);

        printf("Locality: ");
        scanf(" %[^\n]", companies->locality);

        while (1) {
        printf("Postal Code: ");
        char postalCodeInput[15];
        scanf(" %[^\n]", postalCodeInput);

        if (!isValidPostalCode(postalCodeInput)) {

            printf("Invalid Postal Code. Please enter a valid postal code (e.g., 1231-012).\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
      } else {

            strcpy(companies->postalCode, postalCodeInput);
        break;
        }
       }

        // Mark the company as active
        companies->active = 1;
        companies->numRatings = 0;

        saveCompaniesToFile(companies, 1);
        printf("Company created successfully! Restart the program to save the company!!\n");

        free(companies);
        free(businessSectors);
    }

    void editCompany() {
        int nif;

        printf("Enter the NIF of the company you want to edit: ");
        scanf("%d", &nif);
    
            if (nif < 100000000 || nif > 999999999) {
            printf("Invalid NIF. Please enter a 9-digit NIF.\n");
            return;
        }     

        int index = findIndexByNIF(nif);

        if (index != -1 && companies[index].active) {
            int option;

            printf("\nCompany Information:\n");
            printf("1. Name: %s\n", companies[index].name);
            printf("2. Category: %s\n", companies[index].category);
            printf("3. Business Sector: %s\n", companies[index].businessSector);
            printf("4. Street: %s\n", companies[index].street);
            printf("5. Locality: %s\n", companies[index].locality);
            printf("6. Postal Code: %s\n", companies[index].postalCode);

            printf("\nEnter the number corresponding to the information you want to edit: ");
            scanf("%d", &option);

        // Validate the option
            if (option < 1 || option > 6) {
                printf("Invalid option. No changes made.\n");
                return;
            }

         switch (option) {
            case 1:
                printf("Enter the new name: ");
                scanf("%s", companies[index].name);
                break;
            case 2:
                do {
                    printf("Enter the new category (MICRO, SMALL, MEDIUM, BIG): ");
                    scanf(" %[^\n]", companies[index].category);

                    // Validate the category input
                    if (strcmp(companies[index].category, "MICRO") == 0 || strcmp(companies[index].category, "SMALL") == 0 ||
                        strcmp(companies[index].category, "MEDIUM") == 0 || strcmp(companies[index].category, "BIG") == 0) {
                        break;
                    } else {
                        printf("Invalid category. Please enter MICRO, SMALL, MEDIUM, or BIG.\n");
                    }
                } while (1);
                break;
            case 3:
                
                int numBusinessSectors;
                BusinessSector* businessSectors;
                loadBusinessSectorsFromFile(&businessSectors, &numBusinessSectors);
                if (numBusinessSectors == 0) {
                    printf("No active business sectors found. Please create an active business sector first.\n");
                    free(businessSectors);
                    return;
                }
                printf("Active Business Sectors:\n");
                for (int i = 0; i < numBusinessSectors; ++i) {
                    if (businessSectors[i].isActive) {
                        printf("%d. %s\n", i + 1, businessSectors[i].name);
                    }
                }

                int chosenIndex;
                printf("Choose an active Business Sector (1 to %d): ", numBusinessSectors);
                scanf("%d", &chosenIndex);

                // Validate the chosen index
                if (chosenIndex < 1 || chosenIndex > numBusinessSectors || !businessSectors[chosenIndex - 1].isActive) {
                    printf("Invalid or inactive Business Sector chosen.\n");
                    free(businessSectors);
                    return;
                }

                // Assign the chosen Business Sector to the company
                strcpy(companies[index].businessSector, businessSectors[chosenIndex - 1].name);
                free(businessSectors);
                break;
            case 4:
                printf("Enter the new street: ");
                scanf("%s", companies[index].street);
                break;
            case 5:
                printf("Enter the new locality: ");
                scanf("%s", companies[index].locality);
                break;
            case 6:
                while (1) {
                    printf("Enter the new postal code: ");
                    char postalCodeInput[15];
                    scanf(" %[^\n]", postalCodeInput);

                    if (!isValidPostalCode(postalCodeInput)) {
                        printf("Invalid Postal Code. Please enter a valid postal code (e.g., 1231-012).\n");

                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    } else {
                        strcpy(companies[index].postalCode, postalCodeInput);
                        break;
                    }
                }
                break;
            default:
                printf("Invalid option. No changes made.\n");
                return;
        }

        saveNotRemovedCompaniesToFile(numCompanies);
        printf("\nCompany edited successfully!\n");
    } else {
        printf("Company not found or inactive.\n");
    }
}

void removeCompany() {
    int nif;

    printf("Digite o NIF da empresa que deseja remover: ");
    scanf("%d", &nif);

    int index = findIndexByNIF(nif);

    if (index != -1) {
        if (companyHasComments(index)) {

            companies[index].active = 0;
            printf("\nEmpresa marcada como inativa devido à existência de comentários.\n");
        } else {

            for (int i = index; i < 99; i++) {
                companies[i] = companies[i + 1];
            }
            printf("\nEmpresa removida com sucesso!\n");

            saveNotRemovedCompaniesToFile(numCompanies);
        }
        } else {
        printf("Empresa não encontrada ou inativa.\n");
        }
    }

   void listCompanies(Company* companies, int numCompanies) {
        if (numCompanies == 0) {
            printf("No companies available.\n");
            return;
        }

        printf("\nList of Companies:\n");
        int activeCount = 0; // Variable to keep track of active companies


        for (int i = 0; i < numCompanies; ++i) {
            if (companies[i].active) {
                activeCount++;
                printf("\nCompany %d:\n", activeCount);
                printf("NIF: %-5d\n", companies[i].nif);
                printf("Name: %-15s\n", companies[i].name);
                printf("Category: %-15s\n", companies[i].category);
                printf("Business Sector: %-20s\n", companies[i].businessSector);
                printf("Street: %-15s\n", companies[i].street);
                printf("Locality: %-15s\n", companies[i].locality);
                printf("Postal Code: %-10s\n", companies[i].postalCode);
                printf("Active: %-10s\n", companies[i].active ? "Yes" : "No");
            }
        }

        if (activeCount == 0) {
            printf("No active companies found.\n");
        }

        printf("\n");
    }

