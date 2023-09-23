/** ***************************************************************************
 * @file
 * @brief Includes the function main and execution of the Program
 *****************************************************************************/

#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "netPBM.h"

 /**
 * @brief RUNCATCH is a function that decides whether to run testcases or not 
 */

const bool RUNCATCH = false;

/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * Function main that is responsible for the execution of the program 
 * by calling various function to accomplish different tasks.
 *
 * @param[in]     argc - number of command line arguements passed in.
 * @param[out]    argv - contains values of commandline arguements passed in.
 *
 * @return returns 0 on successful execution and non zero otherwise
 * 
 *****************************************************************************/

int main(int argc, char** argv)
{
    Catch::Session session;
    int result;

    ifstream fin;
    ofstream fout;

    ofstream foutgray;

    image img;
    bool ans;

    if (RUNCATCH)
    {
        result = session.run(argc, argv);
        if (result != 0)
        {
            cout << "Test cases didn't pass." << endl;
            return result;
        }
    }

    if (argc < 4 || argc > 5)
    {
        cout << "thpe11.exe [option] --outputtype basename image.ppm" << endl;
        cout << endl;
        cout << "Output Type      Output Description" << endl;
        cout << "    --ascii      integer text numbers will be written for the data" << endl;
        cout << "    --binary     integer numbers will be written in binary form" << endl;
        cout << endl;
        cout << "Option Code      Option Description" << endl;
        cout << "    --flipX      Flip the image on the X axis" << endl;
        cout << "    --flipY      Flip the image on the Y axis" << endl;
        cout << "    --rotateCW   Rotate the image clockwise" << endl;
        cout << "    --rotateCCW  Rotate the image counter clockwise" << endl;
        cout << "    --grayscale  Convert image to grayscale" << endl;
        cout << "    --sepia      Antique a color image" << endl;
        exit(0);
    }

    if (argc == 4)
    {
        if (strcmp(argv[1], "--outputtype") != 0 && strcmp(argv[1], "--ascii") != 0
            && strcmp(argv[1], "--binary") != 0)
        {
            cout << "Invalid output type specified" << endl;

            cout << "thpe11.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type      Output Description" << endl;
            cout << "    --ascii      integer text numbers will be written for the data" << endl;
            cout << "    --binary     integer numbers will be written in binary form" << endl;
            cout << endl;
            cout << "Option Code      Option Description" << endl;
            cout << "    --flipX      Flip the image on the X axis" << endl;
            cout << "    --flipY      Flip the image on the Y axis" << endl;
            cout << "    --rotateCW   Rotate the image clockwise" << endl;
            cout << "    --rotateCCW  Rotate the image counter clockwise" << endl;
            cout << "    --grayscale  Convert image to grayscale" << endl;
            cout << "    --sepia      Antique a color image" << endl;
            exit(0);
        }
    }

    if (argc == 5)
    {
        if (strcmp(argv[1], "--flipX") != 0 && strcmp(argv[1], "--flipY") != 0
            && strcmp(argv[1], "--rotateCW") != 0 && strcmp(argv[1], "--rotateCCW") != 0
            && strcmp(argv[1], "--grayscale") != 0 && strcmp(argv[1], "--sepia") != 0)
        {
            cout << "Invalid option given" << endl;

            cout << "thpe11.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type      Output Description" << endl;
            cout << "    --ascii      integer text numbers will be written for the data" << endl;
            cout << "    --binary     integer numbers will be written in binary form" << endl;
            cout << endl;
            cout << "Option Code      Option Description" << endl;
            cout << "    --flipX      Flip the image on the X axis" << endl;
            cout << "    --flipY      Flip the image on the Y axis" << endl;
            cout << "    --rotateCW   Rotate the image clockwise" << endl;
            cout << "    --rotateCCW  Rotate the image counter clockwise" << endl;
            cout << "    --grayscale  Convert image to grayscale" << endl;
            cout << "    --sepia      Antique a color image" << endl;
            exit(0);
        }

        if (strcmp(argv[2], "--outputtype") != 0 && strcmp(argv[2], "--ascii") != 0
           && strcmp(argv[2], "--binary") != 0)
        {
            cout << "Invalid output type specified" << endl;

            cout << "thpe11.exe [option] --outputtype basename image.ppm" << endl;
            cout << endl;
            cout << "Output Type      Output Description" << endl;
            cout << "    --ascii      integer text numbers will be written for the data" << endl;
            cout << "    --binary     integer numbers will be written in binary form" << endl;
            cout << endl;
            cout << "Option Code      Option Description" << endl;
            cout << "    --flipX      Flip the image on the X axis" << endl;
            cout << "    --flipY      Flip the image on the Y axis" << endl;
            cout << "    --rotateCW   Rotate the image clockwise" << endl;
            cout << "    --rotateCCW  Rotate the image counter clockwise" << endl;
            cout << "    --grayscale  Convert image to grayscale" << endl;
            cout << "    --sepia      Antique a color image" << endl;
            exit(0);
        }
    }

    fileopeninput(fin, argv[argc - 1]);

    if (strcmp(argv[1], "--grayscale") != 0)
    {
        fileopenoutput(fout, argv[argc - 2]);
    }
   
    ans = readImage(fin, img);

    if (ans == false)
    {
        exit(1);
    }

    if (argc == 4)
    {
        if (strcmp(argv[1], "--outputtype") == 0)
        {
            writeImage(fout, img);
        }

        if (strcmp(argv[1], "--ascii") == 0)
        {
            img.magicNumber = "P3";
            writeImage(fout, img);
        }

        if (strcmp(argv[1], "--binary") == 0)
        {
            img.magicNumber = "P6";
            writeImage(fout, img);
        }
    }

    else if (argc == 5)
    {
        
        if (strcmp(argv[1], "--grayscale") == 0)
        {
            outputgray(foutgray, argv[argc-2]);
            grayScale(foutgray, img, argv[2]);
            filecloseoutput(foutgray);
        }
        
        if (strcmp(argv[1], "--flipX") == 0)
        {
            flipX(img, argv[2]);
            writeImage(fout, img);
        }

        if (strcmp(argv[1], "--flipY") == 0)
        {
            flipY(img, argv[2]);
            writeImage(fout, img);
        }

        if (strcmp(argv[1], "--rotateCW") == 0)
        {
            rotateCW(img, argv[2]);
            writeImage(fout, img);
        }

        if (strcmp(argv[1], "--rotateCCW") == 0)
        {
            rotateCCW(img, argv[2]);
            writeImage(fout, img);
        }

        if (strcmp(argv[1], "--sepia") == 0)
        {
            sepia(img, argv[2]);
            writeImage(fout, img);
        }

    }
    filecloseinput(fin);
    filecloseoutput(fout);
}
