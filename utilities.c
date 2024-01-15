/**
 * @file utilities.c
 * @brief file containing utility functions and data structures for the Company Management System.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 05-01-2024
 *

 */
#include "utilities.h"
/**
 * @brief A structure representing a list of business sectors.
 */
BusinessSectorList sectorList;

/**
 * @brief The initial number of companies in the system.
 */
int numCompanies = 0;

/**
 * @brief The initial number of comments made on companies.
 */
int numComments = 0;

/**
 * @brief An array representing the companies in the system.
 */
Company companies[MAX_COMPANIES];

    const char* getCategoryName(Categoria category) {
        static const char* categoryNames[] = {
            [MICRO] = "MICRO",
            [SMALL] = "SMALL",
            [MEDIUM] = "MEDIUM",
            [BIG] = "BIG",
        };

        if (category >= MICRO && category <= BIG) {
            return categoryNames[category];
        } else {
            return "UNKNOWN";
        }
    }

    void saveBusinessSectorsToFile(BusinessSector* businessSectors, int numBusinessSectors) {
        FILE* file = fopen("business_sectors.txt", "w");

        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < numBusinessSectors; ++i) {
            fprintf(file, "%s|%d\n", businessSectors[i].name, businessSectors[i].isActive);
        }

        fclose(file);
    }

    void loadBusinessSectorsFromFile(BusinessSector** businessSectors, int* numBusinessSectors) {

            FILE *file = fopen("business_sectors.txt", "r");
        if (file == NULL) {
            file = fopen("business_sectors.txt", "w");
            *numBusinessSectors = 0;
            fclose(file);
            return;
        }

        int maxBusinessSectors = 100;
        *businessSectors = (BusinessSector*)malloc(maxBusinessSectors * sizeof(BusinessSector));

        if (*businessSectors == NULL) {
            printf("Memory allocation error.\n");
            *numBusinessSectors = 0;
            fclose(file);
            return;
        }

        *numBusinessSectors = 0;

        while (*numBusinessSectors < maxBusinessSectors && fscanf(file, " %99[^|]|%d", (*businessSectors)[*numBusinessSectors].name, &(*businessSectors)[*numBusinessSectors].isActive) == 2) {
            (*numBusinessSectors)++;
        }

        fclose(file);
    }

    int isBusinessSectorInUse(const Company* companies, int numCompanies, const char* businessSector) {
        for (int i = 0; i < numCompanies; i++) {
            if (strcmp(companies[i].businessSector, businessSector) == 0) {
                return 1; 
            }
        }
        return 0; 
    }

    void freeBusinessSectorList(BusinessSectorList* sectorList) {
        for (int i = 0; i < sectorList->numSectors; i++) {
            free(sectorList->sectors[i]);
        }
        free(sectorList->sectors);
    }

    void shiftArray(Company* arr, size_t size, size_t index) {
        if (index < size - 1) {
            memmove(&arr[index], &arr[index + 1], (size - index - 1) * sizeof(Company));
        }
    }

    float calculateAverageRating(float ratings[], int numRatings) {
        if (numRatings == 0) {
            return 0.0;
        }

        float sum = 0;
        for (int i = 0; i < numRatings; i++) {
            sum += ratings[i];
        }

        return sum / numRatings;
    }

    void saveCompaniesToFile(Company companies[], int numCompanies) {
        FILE *file;
        file = fopen("companies.txt", "a");

        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < numCompanies; i++) {
            fprintf(file, "Company %d:\n", i + 1);
            fprintf(file, "NIF: %d\n", companies[i].nif);
            fprintf(file, "Name: %s\n", companies[i].name);
            fprintf(file, "Category: %s\n", companies[i].category);
            fprintf(file, "Business Sector: %s\n", companies[i].businessSector);
            fprintf(file, "Street: %s\n", companies[i].street);
            fprintf(file, "Locality: %s\n", companies[i].locality);
            fprintf(file, "Postal Code: %s\n", companies[i].postalCode);
            fprintf(file, "Active: %d\n", companies[i].active);

            fprintf(file, "\n");
        }

        fclose(file);

    }

    void loadCompaniesFromFile(Company companies[], int *numCompanies) {
        FILE *file = fopen("companies.txt", "r");
        if (file == NULL) {

            file = fopen("companies.bin", "wb");
            fclose(file);
            return;
        }

        while (fscanf(file, "Company %*d:\n") != EOF) {
            int index = (*numCompanies)++;
            fscanf(file, "NIF: %d\n", &companies[index].nif);
            fscanf(file, "Name: %s\n", companies[index].name);
            fscanf(file, "Category: %s\n", companies[index].category);
            fscanf(file, "Business Sector: %s\n", companies[index].businessSector);
            fscanf(file, "Street: %s\n", companies[index].street);
            fscanf(file, "Locality: %s\n", companies[index].locality);
            fscanf(file, "Postal Code: %s\n", companies[index].postalCode);
            fscanf(file, "Active: %d\n", &companies[index].active);


            for (int i = 0; i < MAX_COMMENTS; i++) {
                fscanf(file, "Username: %s\n", companies[index].comments[i].username);
                fscanf(file, "Title: %s\n", companies[index].comments[i].title);
                fscanf(file, "Text: %s\n", companies[index].comments[i].text);
            }

            fscanf(file, "Ratings: ");
            for (int i = 0; i < MAX_RATINGS; i++) {
                fscanf(file, "%f ", &companies[index].ratings[i]);
            }
            fscanf(file, "\n\n");

        }

        fclose(file);

    }
    
    int loadCompanyCount() {
        FILE *file;
        file = fopen("company_count.bin", "rb");

        if (file == NULL) {
            printf("");
            return 0;
        }

        int numCompanies;
        fscanf(file, "%d", &numCompanies);

        fclose(file);
        return numCompanies;
    }

    void saveCompanyCount(int numCompanies) {
        FILE *file = fopen("company_count.bin", "wb");
        if (file == NULL) {
            perror("Error opening file for writing");
            exit(EXIT_FAILURE);
        }

        fprintf(file, "%d\n", numCompanies);

        fclose(file);
    }
    
    int isValidPostalCode(const char *postalCode) {
        int length = strlen(postalCode);


        return (length == 8 && isdigit(postalCode[0]) && isdigit(postalCode[1]) &&
            isdigit(postalCode[2]) && isdigit(postalCode[3]) && postalCode[4] == '-' &&
            isdigit(postalCode[5]) && isdigit(postalCode[6]) && isdigit(postalCode[7]));
    }

   
    
    void saveNotRemovedCompaniesToFile(int numCompanies) {
        FILE *file = fopen("companies.txt", "w");

        if (file != NULL) {
            for (int i = 0; i < numCompanies; i++) {
                if (companies[i].active == 1) {
                    fprintf(file, "Company %d:\n", i + 1);
                    fprintf(file, "NIF: %d\n", companies[i].nif);
                    fprintf(file, "Name: %s\n", companies[i].name);
                    fprintf(file, "Category: %s\n", companies[i].category);
                    fprintf(file, "Business Sector: %s\n", companies[i].businessSector);
                    fprintf(file, "Street: %s\n", companies[i].street);
                    fprintf(file, "Locality: %s\n", companies[i].locality);
                    fprintf(file, "Postal Code: %s\n", companies[i].postalCode);
                    fprintf(file, "Active: %d\n", companies[i].active);
                }
            }

            fclose(file);
        } else {
            printf("Erro ao abrir o arquivo para salvar.\n");
        }
    }
    
    
    int findIndexByNIF(int nif) {
        for (int i = 0; i < MAX_COMPANIES; i++) {
            if (companies[i].nif == nif && companies[i].active == 1) {
                return i;
            }
        }
        return -1;
    }

    int companyHasComments(int index) {
        return companies[index].numComments > 0;
    }

 void saveRatingsToFile(Company companies[], int numCompanies) {
        FILE *file = fopen("ratings.txt", "w");

        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < numCompanies; i++) {
            fprintf(file, "%s %f %d", companies[i].name, companies[i].averageRating, companies[i].numRatings);

            for (int j = 0; j < companies[i].numRatings; j++) {
                fprintf(file, " %f", companies[i].ratings[j]);
            }

            fprintf(file, "\n");
        }

        fclose(file);
    }

    void loadRatingsFromFile(Company companies[], int numCompanies) {
        FILE *file = fopen("ratings.txt", "r");

        if (file == NULL) {
            printf("");
            return;
        }

        for (int i = 0; i < numCompanies; i++) {
            int numRatings;
            fscanf(file, "%s %f %d", companies[i].name, &companies[i].averageRating, &numRatings);
            companies[i].numRatings = numRatings;

            for (int j = 0; j < numRatings; j++) {
                fscanf(file, " %f", &companies[i].ratings[j]);
            }
        }

        fclose(file);
    }


    void saveCommentsToFile(Company companies[], int numCompanies) {
        FILE *file = fopen("comments.txt", "a");

        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < numCompanies; i++) {
            for (int j = 0; j < companies[i].numComments; j++) {
                fprintf(file, "Company: %s\n", companies[i].name);
                fprintf(file, "Username: %s\n", companies[i].comments[j].username);
                fprintf(file, "Title: %s\n", companies[i].comments[j].title);
                fprintf(file, "Text: %s\n", companies[i].comments[j].text);
                fprintf(file, "------------------------------\n");
            }
        }

        fclose(file);
        printf("Comments saved to file successfully!\n");
    }


    void loadCommentsFromFile(Company companies[], int *numCompanies) {
        FILE *file = fopen("comments.txt", "r");

        if (file == NULL) {
            printf("");
            return;
        }

        int i = -1;

        while (!feof(file)) {
            char buffer[1000]; 
            if (fgets(buffer, sizeof(buffer), file) != NULL) {
                if (strncmp(buffer, "Company:", 8) == 0) {

                    i++;
                    sscanf(buffer, "Company: %s", companies[i].name);
                    companies[i].numComments = 0;
                } else if (strncmp(buffer, "Username:", 9) == 0) {

                    int currentCommentIndex = companies[i].numComments;
                    sscanf(buffer, "Username: %s", companies[i].comments[currentCommentIndex].username);

                    fgets(buffer, sizeof(buffer), file);
                    sscanf(buffer, "Title: %s", companies[i].comments[currentCommentIndex].title);

                    fgets(buffer, sizeof(buffer), file);
                    sscanf(buffer, "Text: %[^\n]", companies[i].comments[currentCommentIndex].text);

                    fgets(buffer, sizeof(buffer), file); 

                    companies[i].numComments++; 
                    
                }
            }
        }

        fclose(file);
        *numCompanies = i + 1;
        printf("Comments loaded from file successfully!\n");
    }
