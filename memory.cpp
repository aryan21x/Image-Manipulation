/** ***************************************************************************
 * @file
 * @brief Contains functions to allocate and free up 2D dynamic memory
 *****************************************************************************/


#include "netPBM.h"

 /** ***************************************************************************
   * @author Aryan Raval
   *
   * @par Description 
   * allocates 2D dynamic array and outputs error message
   * if unable to allocate memory
   *
   *
   * @param[in,out]     storage - a 2D array dynamically alloted
   * @param[in]    rows - number of rows in a ppm image
   * @param[in] cols - number of columns in a ppm image
   *
   *
   * @par Example
   * @verbatim
     alloc ( img.blue , img.rows , img.cols); // allocates 2D array to blue pixels
     alloc (img.green , img.rows , img.cols); // alllocates 2D array to green pixels
     @endverbatim
   *****************************************************************************/


void alloc (pixel **&storage ,int rows, int cols)
{
    int i;
    storage = new(nothrow) pixel* [rows];
    
    if (storage == nullptr)
    {
        cout << "Unable to allocate memory for storage." << endl;
        delete[] storage;
    }

    for (i = 0; i < rows; i++)
    {
        storage[i] = new(nothrow) pixel[cols];

        if (storage[i] == nullptr)
        {
            cout << "Unable to allocate memory for storage." << endl;
            free2d (storage,rows);
        }
    }
}

/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * Frees up dynamically allocated 2D array from memory
  *
  * @param[in,out]     ptr - 2D dynamic array 
  * @param[in]    rows - number of rows in a ppm image
  *
  *
  * @par Example
  * @verbatim
    frre2d (img.gren , img.rows) ; // frees up img.green array
    free2d (img.blue , img.rows) ; // frees up img.blue array
    @endverbatim
  *****************************************************************************/


void free2d (pixel **& ptr, int rows)
{
    int i;
    if (ptr == nullptr)
        return;

    for (i = 0; i < rows; i++)
    {
        delete[] ptr[i];
    }
    delete[] ptr;
}