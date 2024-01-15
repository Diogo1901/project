/**
 * @file user.h
 * @brief Header file for user-related functionalities in the Company Management System.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 1st January 2024
 */

#ifndef USER_H
#define USER_H

#include "utilities.h"

#ifdef __cplusplus
extern "C" {
#endif
 /**
 * @brief Searches and displays information about companies based on various criteria.
 *
 * This function allows users to search for companies using different criteria such as name,
 * category, location. The search results are displayed to the user.
 *
 * @param companies An array of companies.
 * @param numCompanies The number of companies in the array.
 * @return void - This function does not return a value.
 */      
void searchCompanies(Company companies[], int numCompanies);

/**
 * @brief Allows users to rate a company.
 *
 * This function enables users to provide a rating (0 to 5) for a specific company. The rating
 * contributes to the company's overall evaluation.
 *
 * @param companies An array of companies.
 * @param numCompanies The number of companies in the array.
 * @return void - This function does not return a value.
 */
void rateCompany(Company companies[], int numCompanies);

/**
 * @brief Allows users to comment on a company.
 *
 * This function enables users to add comments to a specific company. User information such as
 * name is collected along with the comment.
 *
 * @param comments An array of comments.
 * @param numComments A pointer to the variable storing the number of comments.
 * @return void - This function does not return a value.
 */
void commentCompany(Comment comments[], int *numComments);


#ifdef __cplusplus
}
#endif

#endif /* USER_H */

