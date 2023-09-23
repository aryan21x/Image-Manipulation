/** ***************************************************************************
 * @file
 * @brief Header file containining function prototypes
 *****************************************************************************/

 /** **************************************************************************
  * @mainpage Take home programming Exam 1 - Image Manipulation
  *
  * @section course_section Course Information
  *
  * @author Aryan Raval
  *
  * @par Professor:
  *         Roger Schrader
  *
  * @par Course:
  *         CSC 215 - Programming Techniques
  *
  * @par Location:
  *         McLaury - 306
  *
  * @date Due March 3, 2023
  *
  * @section program_section Program Information
  *
  * @details
  * 
  * The program takes only coloured ppm images as input either in ascii format or binary format.
  * The input is read into a structure called image using readImage function and dynamic allocation 
  * of memory for the 3 pixels red , green and blue is used which is later outputted using writeImage. The file
  * is always opened in Binary mode and can output the data in both ascii or binary format.
  * 
  * The image can be manipulated to different forms depending such as Flip on x axis, Flip on Y axis, 
  * rotate Clockwise , rotate Counter Clockwise , Grayscale and Sepia depending on user's input. There are 
  * multiple files for conductiong different operation such memory allocation , image manipulation , opening 
  * and closing of file and reading and writing the data , header file containg function prototypes.
  *
  * A c++ program that manipulates a coloured ppm image into different forms and outputs it in either binary or
  * ascii format depending on user's input.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
        c:\> thpe11.exe [option] --outputtype basename image.ppm

    Output Type      Output Description
        --ascii      integer text numbers will be written for the data
        --binary     integer numbers will be written in binary form

    Option Code      Option Description
        --flipX      Flip the image on the X axis
        --flipY      Flip the image on the Y axis
        --rotateCW   Rotate the image clockwise
        --rotateCCW  Rotate the image counter clockwise
        --grayscale  Convert image to grayscale
        --sepia      Antique a color image
    @endverbatim
  *
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  * @bug NO BUGS 
  *
  * @todo Everything works
  *
  * @par Modifications and Development Timeline:
  * https://gitlab.cse.sdsmt.edu/101125506/csc215s23programs/-/commits/main?ref_type=heads
  *
  *****************************************************************************/


#include <iostream>
#include <string>
#include <fstream>


using namespace std;

#ifndef __NETPBM__H__
#define __NETPBM__H__

/**
 * @brief tydefed unsigned char to "pixel" 
 */

typedef unsigned char pixel;

/**
 * @brief holds the data of a ppm file
 */

struct image
{
    string magicNumber;  /**< a number that decides the ascii or binary format  */
    string comment;   /**<  contains comments made by author */
    int rows;     /**< contains the number of rows in a ppm image*/
    int cols;    /**< contains the number of cols in a ppm image */
    pixel** redGray;    /**<  contains 2D array of red or gray pixels  */
    pixel** green;    /**< contains 2D array of green pixels   */
    pixel** blue;    /**<  contains 2D array of blue  */
};

/**
 * @brief a string that contains constant maxpixel value
 */

static string maxpix = "255";

void fileopeninput(ifstream& fin, string name);

void fileopenoutput(ofstream& fout, string name);

void filecloseinput(ifstream& file);

void filecloseoutput(ofstream& file);

bool readImage(ifstream& fin, image& img);

void writeImage(ofstream& fout, image& img);

void alloc (pixel **& storage, int rows, int cols);

void free2d (pixel **& ptr, int rows);

void grayScale(ofstream& fout, image& img, string outputType);

void flipX(image& img, string outputType);

void flipY(image& img, string outputType);

void rotateCW(image& img, string outputType);

void rotateCCW(image& img, string outputType);

void sepia(image& img, string outputType);

double crop(double value);

void outputgray(ofstream& fout, string name);


#endif