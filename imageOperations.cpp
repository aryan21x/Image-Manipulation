/** ***************************************************************************
 * @file
 * @brief Contains functions to manipulate the image
 *****************************************************************************/


#include "netPBM.h"


 /** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * applies grayscale filter to a ppm image and outputs the data
  *
  * @param[in,out]     fout - ofstream file opened for output
  * @param[in,out]    img - structure containing data of a ppm image
  * @param[in]  outputType - aschii or binary format type
  *
  *
  * @par Example
  * @verbatim
    iimage img;
    ofstream fout;
    grayScale(fout,img,"ascii"); // will output an grayscale image in ascii 
                                 // format to fout file
    @endverbatim
  *****************************************************************************/

void grayScale(ofstream &fout, image& img, string outputType)
{
    int i;
    int j;

    int count = 0;

    int r, g, b;

    if (outputType == "--ascii")
    {
        img.magicNumber = "P2";
    }

    if (outputType == "--binary")
    {
        img.magicNumber = "P5";
    }

    fout << img.magicNumber << "\n";
    fout << img.comment;

    fout << img.cols;
    fout << " ";
    fout << img.rows << "\n";

    fout << maxpix << "\n";

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            r = (img.redGray[i][j]);
            g = (img.green[i][j]);
            b = (img.blue[i][j]);

            img.redGray[i][j] = pixel(round(0.3 * r + 0.6 * g + 0.1 * b));
        }
    }

    if (img.magicNumber == "P2" )
    {
        for (i = 0; i < img.rows; i++)
        {
            for (i = 0; i < img.rows; i++)
            {
                for (i = 0; i < img.rows; i++)
                {
                    for (j = 0; j < img.cols; j++)
                    {
                        fout << int(img.redGray[i][j]);
                        fout << " ";
                        count++;

                        if (count == 3)
                        {
                            count = 0;
                            fout << "\n";
                        }
                    }
                }

            }

        }
    }
    
    else if (img.magicNumber == "P5")
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout.write((char*)&img.redGray[i][j], sizeof(pixel));
            }
        }
    }
   
}

/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * manipulates data so the the ppm image flips on x axis.
 * 
 *
 * @param[in,out]     img - structure containing data of a ppm image.
 * @param[in]     outputType - aschii or binary format type.
 *
 *
 * @par Example
 * @verbatim
   struct img;
   flipX(img, "ascii"); // will produce a flipped on x axis ascii image
   flipX(img, "binary"); // will produce a flipped on x axis binary imgae
   @endverbatim
 *****************************************************************************/


void flipX(image& img,string outputType)
{
    int i;
    int j;

    for (j = 0; j < img.cols; j++)
    {
        for (i = 0; i < img.rows/2; i++)
        { 
            swap (img.redGray[i][j] , img.redGray[img.rows - i - 1][j]);
            swap (img.blue[i][j] , img.blue[img.rows - i - 1 ][j]);
            swap (img.green[i][j] ,img.green[img.rows - i - 1][j]);
        }
    }

    if (outputType == "--ascii")
    {
        img.magicNumber = "P3";
    }

    else if (outputType == "--binary")
    {
        img.magicNumber = "P6";
    }
}

/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * manipulates data so that the ppm image can flip on y axis
 *
 * @param[in]     img - structure containing data of a ppm image
 * @param[out]    outputType - aschii or binary format type.
 *
 * @par Example
 * @verbatim
   image img;
   flipY(img,"ascii"); // will produce an flipped on y axis ascii image
   flipY(img,"binary"); // will produce an flipped on y axis binary image
   @endverbatim
 *****************************************************************************/


void flipY(image& img, string outputType)
{
    int i;
    int j;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols/2; j++)
        {
            swap(img.redGray[i][j], img.redGray[i][img.cols - j -1]);
            swap(img.blue[i][j], img.blue[i][img.cols - j - 1]);
            swap(img.green[i][j], img.green[i][img.cols - j -1]);
        }
    }

    if (outputType == "--ascii")
    {
        img.magicNumber = "P3";
    }

    else if (outputType == "--binary")
    {
        img.magicNumber = "P6";
    }
}

/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * manipulates data to rotate a ppm image in clockwise direction.
 *
 * @param[in,out]     img - structure containing data of a ppm image.
 * @param[in]     outputType - aschii or binary format type.
 * 
 * @par Example
 * @verbatim
   image img;
   rotateCW (img, "ascii") ; // will produce on closwise roated ascii image
   rotateCw (img,"binary") ; // will produce an clockwise roates binary image
   @endverbatim
 *****************************************************************************/

void rotateCW(image& img, string outputType)
{
    int i;
    int j;

    pixel** tempRed;
    pixel** tempBlue;
    pixel** tempGreen;


    alloc(tempRed, img.cols, img.rows); 
    alloc(tempBlue, img.cols, img.rows);
    alloc(tempGreen, img.cols, img.rows);

    if (tempRed == nullptr || tempBlue == nullptr || tempGreen == nullptr)
    {
        cout << "Unable to allocate memory for storage." << endl;
        exit(1);
    }

    for (j = 0; j < img.cols; j++)   //   700 
    {
        for (i = 0; i < img.rows; i++)   //  400
        {
            (tempRed[j][i] = img.redGray[img.rows - i - 1][j]);
            (tempBlue[j][i] =  img.blue[img.rows - i - 1][j]);
            (tempGreen[j][i] = img.green[img.rows - i -1][j]);
        }
    }

    free2d(img.redGray, img.rows);
    free2d(img.green, img.rows);
    free2d(img.blue, img.rows);

    alloc(img.redGray, img.cols, img.rows);
    alloc(img.blue, img.cols, img.rows);
    alloc(img.green, img.cols, img.rows);

    swap(img.cols, img.rows);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redGray[i][j] = tempRed[i][j];
            img.blue[i][j] = tempBlue[i][j];
            img.green[i][j] = tempGreen[i][j];
        }
    }

    free2d(tempRed, img.rows);
    free2d(tempBlue, img.rows);
    free2d(tempGreen, img.rows);

    if (outputType == "--ascii")
    {
        img.magicNumber = "P3";
    }

    else if (outputType == "--binary")
    {
        img.magicNumber = "P6";
    }
}


/** ***************************************************************************
 * @author Your Name
 *
 * @par Description
 * manipulates data to rotate a ppm image in ounter clockwise direction.
 *
 * @param[in,out]     img - structure containing data of a ppm image.
 * @param[in]     outputType - aschii or binary format type.
 * 
 *
 * @par Example
 * @verbatim
   mage img;
   rotateCCW (img, "ascii") ; // will produce on counter closwise roated ascii image
   rotateCCw (img,"binary") ; // will produce an counter clockwise roates binary image
   @endverbatim
 *****************************************************************************/


void rotateCCW(image& img, string outputType)
{
    int i;
    int j;

    pixel** tempRed;
    pixel** tempBlue;
    pixel** tempGreen;


    alloc(tempRed, img.cols, img.rows);
    alloc(tempBlue, img.cols, img.rows);
    alloc(tempGreen, img.cols, img.rows);

    if (tempRed == nullptr || tempBlue == nullptr || tempGreen == nullptr)
    {
        cout << "Unable to allocate memory for storage." << endl;
        exit(1);
    }

    for (j = 0; j < img.cols; j++)   //   700 
    {
        for (i = 0; i < img.rows; i++)   //  400
        {
            (tempRed[img.cols - j - 1][img.rows - i -1] = img.redGray[img.rows - i - 1][j]);
            (tempBlue[img.cols - j - 1][img.rows - i -1] = img.blue[img.rows - i - 1][j]);
            (tempGreen[img.cols - j - 1][img.rows - i -1] = img.green[img.rows - i - 1][j]);
        }
    }


    free2d(img.redGray, img.rows);
    free2d(img.green, img.rows);
    free2d(img.blue, img.rows);

    alloc(img.redGray, img.cols, img.rows);
    alloc(img.blue, img.cols, img.rows);
    alloc(img.green, img.cols, img.rows);

    swap(img.cols, img.rows);

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            img.redGray[i][j] = tempRed[i][j];
            img.blue[i][j] = tempBlue[i][j];
            img.green[i][j] = tempGreen[i][j];
        }
    }

    free2d(tempRed, img.rows);
    free2d(tempBlue, img.rows);
    free2d(tempGreen, img.rows);

    if (outputType == "--ascii")
    {
        img.magicNumber = "P3";
    }

    else if (outputType == "--binary")
    {
        img.magicNumber = "P6";
    }
}


/** ***************************************************************************
 * @author Your Name
 *
 * @par Description
 * apllies the sepia filter to a ppm iaage.
 *
 * @param[in,out]     img - structure containing data of a ppm image.
 * @param[in]     outputType - aschii or binary format type.
 * 
 *
 * @par Example
 * @verbatim
   image img;
   sepia(img ,"ascii) ; // will produce an sepia image in ascii format
   sepia(img, "binary") ; //  will produce an sepia image in binary format
   @endverbatim
 *****************************************************************************/


void sepia(image& img, string outputType)
{

    int i;
    int j;
    
    pixel red;
    pixel green;
    pixel blue;

    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            red = pixel(crop(round(0.393 * (img.redGray[i][j])
                + 0.769 * (img.green[i][j]) + 0.189 * (img.blue[i][j]))));

            green = pixel(crop(round(0.349 * (img.redGray[i][j])
                + 0.686 * (img.green[i][j]) + 0.168 * (img.blue[i][j]))));

            blue = pixel(crop(round(0.272 * (img.redGray[i][j])
                + 0.534 * (img.green[i][j]) + 0.131 * (img.blue[i][j]))));

            img.redGray[i][j] = red;
            img.blue[i][j] = blue;
            img.green[i][j] = green;

        }
    }

    if (outputType == "--ascii")
    {
        img.magicNumber = "P3";
    }

    else if (outputType == "--binary")
    {
        img.magicNumber = "P6";
    }
    
}


/** ***************************************************************************
 * @author Your Name
 *
 * @par Description
 *  Used for cropping pixel value while creating sepia image, makes
 * sure the pixel doesn't exceed 255
 * 
 * @param[in]     value - pixel value for either red , green or blue
 * 
 * @return 255 if value > 255 or return the value itself otherwise.
 *
 * @par Example
 * @verbatim
   double ans;
   ans = crop(284) ; // ans is 255
   ans = crop(89) ; // ans is 89
   @endverbatim
 *****************************************************************************/


double crop(double value)
{
    if (value > 255 )
    {
        return 255;
    }
    else return value;
}