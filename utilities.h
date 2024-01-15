/* 
 * @file:   utilities.h
 * 
 * @author: Vitor and Diogo (Group 16)
 * @date 5-1-2024
 *
 * @brief Header file containing utility functions and data structures for the Company Management System.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * @brief Maximum number of companies in the system.
     */
    #define MAX_COMPANIES 100

    /**
     * @brief Maximum number of comments for a company.
     */
    #define MAX_COMMENTS 100

    /**
     * @brief Maximum number of ratings for a company.
     */
    #define MAX_RATINGS 100

    /**
     * @brief Minimum rating value.
     */
    #define MIN_RATING 1

    /**
     * @brief Maximum rating value.
     */
    #define MAX_RATING 5

    /**
     * @brief Initial buffer size for dynamic memory allocation.
     */
    #define INITIAL_BUFFER_SIZE 50

    /**
     * @brief Incremental size for buffer resizing.
     */
    #define BUFFER_INCREMENT 10

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <ctype.h>

    /**
     * @brief Structure representing a comment made by a user.
     */
    typedef struct {
        char username[50];
        char title[100];
        char text[500];
    } Comment;

    /**
     * @brief Enumeration representing different company categories.
     */
    typedef enum {
        MICRO = 1,
        SMALL,
        MEDIUM,
        BIG
    } Categoria;

    /**
     * @brief Structure representing a company's information.
     */
    typedef struct {
        int nif;
        char name[100];
        char category[50];
        char businessSector[50];
        char street[50];
        char locality[50];
        char postalCode[10];
        int active;  // 1 for active, 0 for inactive
        Comment comments[50];
        int numComments;
        char activity[100];
        float averageRating;
        float ratings[MAX_RATINGS];
        int numRatings;
    } Company;

    /**
     * @brief Structure representing a list of business sectors.
     */
    typedef struct {
        char** sectors;
        int* activeStatus;
        int numSectors;
    } BusinessSectorList;

    /**
     * @brief Enumeration representing different search criteria.
     */
    typedef enum {
        SEARCH_NAME = 1,
        SEARCH_CATEGORY,
        SEARCH_LOCALITY
    } SearchCriterion;

    /**
     * @brief Structure representing a business sector.
     */
    typedef struct {
        char name[100];
        bool isActive; 
    } BusinessSector;

    /**
     * @brief Gets the name associated with a company category.
     *
     * @param category The company category.
     * @return The name associated with the category.
     */
    const char* getCategoryName(Categoria category);

    /**
     * @brief Saves business sectors to a file.
     *
     * @param businessSectors An array of business sectors.
     * @param numBusinessSectors The number of business sectors.
     * @return void - This function does not return a value.
     */
    void saveBusinessSectorsToFile(BusinessSector* businessSectors, int numBusinessSectors);

    /**
     * @brief Loads business sectors from a file.
     *
     * @param businessSectors A pointer to the array of business sectors.
     * @param numBusinessSectors A pointer to the number of business sectors.
     * @return void - This function does not return a value.
     */
    void loadBusinessSectorsFromFile(BusinessSector** businessSectors, int* numBusinessSectors);

    /**
     * @brief Checks if a business sector is in use by any company.
     *
     * @param companies An array of companies.
     * @param numCompanies The number of companies in the array.
     * @param businessSector The name of the business sector.
     * @return 1 if the business sector is in use, 0 otherwise.
     */
    int isBusinessSectorInUse(const Company* companies, int numCompanies, const char* businessSector);

    /**
     * @brief Frees the memory allocated for a business sector list.
     *
     * @param sectorList A pointer to the BusinessSectorList structure.
     * @return void - This function does not return a value.
     */
    void freeBusinessSectorList(BusinessSectorList* sectorList);

    /**
     * @brief Shifts elements in an array to the left starting from a specified index.
     *
     * @param arr The array to be shifted.
     * @param size The size of the array.
     * @param index The index from which to start shifting.
     * @return void - This function does not return a value.
     */
    void shiftArray(Company* arr, size_t size, size_t index);

    /**
     * @brief Calculates the average rating from an array of ratings.
     *
     * @param ratings An array of ratings.
     * @param numRatings The number of ratings in the array.
     * @return The calculated average rating.
     */
    float calculateAverageRating(float ratings[], int numRatings);

    /**
     * @brief Checks if a postal code is valid.
     *
     * @param postalCode The postal code to be checked.
     * @return 1 if the postal code is valid, 0 otherwise.
     */
    int isValidPostalCode(const char *postalCode);

    /**
     * @brief Saves company information to a file.
     *
     * @param companies An array of companies.
     * @param numCompanies The number of companies in the array.
     * @return void - This function does not return a value.
     */
    void saveCompaniesToFile(Company companies[], int numCompanies);

    /**
     * @brief Loads company information from a file.
     *
     * @param companies An array of companies.
     * @param numCompanies A pointer to the number of companies.
     * @return void - This function does not return a value.
     */
    void loadCompaniesFromFile(Company companies[], int *numCompanies);

    /**
     * @brief Loads the count of companies from a file.
     *
     * @return The count of companies.
     */
    int loadCompanyCount();

    /**
     * @brief Saves the count of companies to a file.
     *
     * @param numCompanies The count of companies.
     * @return void - This function does not return a value.
     */
    void saveCompanyCount(int numCompanies);

    /**
     * @brief Saves company information for non-removed companies to a file.
     *
     * @param numCompanies The number of companies in the array.
     * @return void - This function does not return a value.
     */
    void saveNotRemovedCompaniesToFile(int numCompanies);

    /**
     * @brief Finds the index of a company by its NIF.
     *
     * @param nif The NIF of the company.
     * @return The index of the company in the array.
     */
    int findIndexByNIF(int nif);

    /**
     * @brief Checks if a company has comments.
     *
     * @param index The index of the company.
     * @return 1 if the company has comments, 0 otherwise.
     */
    int companyHasComments(int index);

    /**
     * @brief Saves company ratings to a file.
     *
     * @param companies An array of companies.
     * @param numCompanies The number of companies in the array.
     * @return void - This function does not return a value.
     */
    void saveRatingsToFile(Company companies[], int numCompanies);

    /**
     * @brief Loads company ratings from a file.
     *
     * @param companies An array of companies.
     * @param numCompanies The number of companies in the array.
     * @return void - This function does not return a value.
     */
    void loadRatingsFromFile(Company companies[], int numCompanies);

    /**
     * @brief Saves company comments to a file.
     *
     * @param companies An array of companies.
     * @param numCompanies The number of companies in the array.
     * @return void - This function does not return a value.
     */
    void saveCommentsToFile(Company companies[], int numCompanies);

    /**
     * @brief Loads company comments from a file.
     *
     * @param companies An array of companies.
     * @param numCompanies A pointer to the number of companies.
     * @return void - This function does not return a value.
     */
    void loadCommentsFromFile(Company companies[], int *numCompanies);

    /**
     * @brief External declarations for the number of companies and comments.
     */
    extern int numCompanies;
    extern int numComments;

    /**
     * @brief External declaration for the array of companies.
     */
    extern Company companies[MAX_COMPANIES];

#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */
