/**
 * @file adm.h
 * @brief Header file for Administrator functionalities.
 *
 * This file contains function declarations related to administrator actions, such as creating and managing
 * business sectors, editing and removing companies, listing all business sectors and companies, and changing
 * the status of business sectors.
 *
 * @author Vitor and Diogo (Group 16)
 * @date 1st January 2024
 */


#ifndef ADM_H
#define ADM_H

#include "utilities.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates a new business sector.
 *
 * This function allows the administrator to create a new business sector, specifying its name and status.
 * The user is prompted to enter the name of the new business sector, and the status is set to "Active" by default.
 * The newly created business sector is then added to the list of business sectors.
 *
 * @return This function does not return a value. It populates the string parameter with the user's input.
 */
void createBusinessSector();

/**
 * @brief Lists all active business sectors.
 *
 * This function retrieves and displays a list of all active business sectors,
 * including their names and statuses. The information is presented to the administrator.
 * If there are no active business sectors, a corresponding message is displayed.
 *
 * @return void - This function does not return a value.
 */
void listAllBusinessSectors();

/**
 * @brief Allows the administrator to choose a business sector.
 *
 * This function displays a menu of available business sectors, allowing the administrator
 * to choose one. The selected business sector's index is returned.
 *
 * @param sectorList Pointer to the list of business sectors.
 * @return int - The index of the chosen business sector. Returns -1 if no valid choice is made.
 */
int chooseBusinessSector(BusinessSectorList* sectorList);

/**
 * @brief Removes a business sector.
 *
 * This function allows the administrator to remove a business sector. If there are associated
 * companies in the chosen sector, the sector is marked as "Inactive." If there are no associated
 * companies, the sector is permanently eliminated. The user is prompted to choose a business sector
 * to remove.
 *
 * @return void - This function does not return a value.
 */
void removeBusinessSector();

/**
 * @brief Changes the status of a business sector.
 *
 * This function allows the administrator to change the status (Active or Inactive) of a specific business sector.
 * The user is prompted to choose a business sector, and the function toggles its status accordingly. If the sector
 * is currently Active, it will be changed to Inactive, and vice versa.
 *
 * @return void - This function does not return a value.
 */
void changeBusinessStatus();

/**
 * @brief Creates a new company.
 *
 * This function enables the administrator to create a new company by prompting for necessary details
 * such as NIF, name, category, activity sector, address, and status. The new company is added to the
 * list of companies.
 *
 * @return void - This function does not return a value.
 */
void createCompany();

/**
 * @brief Edits the details of a company.
 *
 * This function allows the administrator to edit the details of a specific company, including its
 * name, NIF, category, activity sector, address, and status. The administrator is prompted to choose
 * a company to edit, and then modify the desired information.
 *
 * @return void - This function does not return a value.
 */
void editCompany();

/**
 * @brief Removes a company.
 *
 * This function allows the administrator to remove a company. If there are no comments from users
 * associated with the company, the removal is permanent. Otherwise, the company is marked as "Inactive,"
 * and its details are hidden from users. The administrator is prompted to choose a company to remove.
 *
 * @return void - This function does not return a value.
 */
void removeCompany();

/**
 * @brief Lists all companies.
 *
 * This function displays a list of all companies, including their details such as NIF, name, category,
 * activity sector, address, and status. The information is presented to the administrator. If there are
 * no companies to display, a corresponding message is shown.
 *
 * @param companies An array of companies.
 * @param numCompanies The number of companies in the array.
 * @return void - This function does not return a value.
 */
void listCompanies(Company* companies, int numCompanies);

    
#ifdef __cplusplus
}
#endif

#endif /* ADM_H */

