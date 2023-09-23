/** ***************************************************************************
 * @file
 * @brief Contains functions to open and close files,and input/ouput data
 *****************************************************************************/

#include "netPBM.h"

 /** ***************************************************************************
   * @author Aryan Raval
   *
   * @par Description
   * Opens file for input in binary mode
   *
   * @param[in,out]     fin - ifstream file opened for input
   * @param[in]    name - name of the ppm file
   *
   *
   * @par Example
   * @verbatim
     fileopeninput( fin , balloonA.ppm);  // opens balloonA.ppm file for input
     fileopeninput ( fin , booloonB.ppm); // opens balloonb.ppm file for input
     @endverbatim
   *****************************************************************************/

void fileopeninput(ifstream &fin , string name)
{
    fin.open(name,ios :: in | ios :: binary);

    if (!fin.is_open())
    {
        cout << "Unable to open file: " << name << endl;
        exit(0);
    }
}

/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * Opens file for output in binary mode
  *
  * @param[in,out]     fout - ofstream file opened for output
  * @param[in]    name - name of the ppm file
  *
  *
  * @par Example
  * @verbatim
    fileopenoutput( fout , balloonx);  // opens balloonx.ppm file for output
     fileopenoutput ( fout , booloonz); // opens balloonz.ppm file for output
    @endverbatim
  *****************************************************************************/

void fileopenoutput(ofstream &fout , string name)
{
    fout.open(name + ".ppm", ios::out | ios::binary | ios::trunc);

    if (!fout.is_open())
    {
        cout << "Unable to open file: " << name << endl;
        exit(0);
    }
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * Opens file for output in binary mode for grayscale
  *
  * @param[in,out]     fout - ofstream file opened for output
  * @param[in]    name - name of the pgm file
  *
  *
  * @par Example
  * @verbatim
    outputgray( foutgray , balloonx);  // opens balloonx.ppm file for output
    @endverbatim
  *****************************************************************************/


void outputgray (ofstream& fout, string name)
{
    fout.open(name + ".pgm", ios::out | ios::binary | ios::trunc);

    if (!fout.is_open())
    {
        cout << "Unable to open file: " << name << endl;
        exit(0);
    }
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  *  Closes file opened for input
  *
  * @param[in]     file - ifstream file opened for input
  *
  *
  * @par Example
  * @verbatim
    filecloseinput(fin);  // closes fin file
    @endverbatim
  *****************************************************************************/

void filecloseinput(ifstream& file)
{
    file.close();
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * Closes file opened for output
  *
  * @param[in]     file - ofstream file opened for output
  *
  * @par Example
  * @verbatim
    filecloseoutput(fout); // close fout file
    @endverbatim
  *****************************************************************************/


void filecloseoutput(ofstream& file)
{
    file.close();
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * reads data from ifstream file and stores it in structure image.
  *
  * @param[in,out]     fin - file opened for input conataining data for ppm file.
  * @param[in,out]    img - a struture that contains data for ppm image.
  *
  * @returns true if memmory allocation is successful and false otherwise.
  *
  * @par Example
  * @verbatim
    bool ans;
    Image img;
    ifstream fin;
    ans = readimage (fin , img) ; // reads data from fin and stores it in struct img
    @endverbatim
  *****************************************************************************/


bool readImage(ifstream& fin, image& img)
{
    string temp;
    size_t pos;

    int i;
    int j;
    int count = 0;
    int size;

    int* storage = nullptr;
    pixel* storageb = nullptr;

    getline(fin, img.magicNumber);

    if (img.magicNumber != "P3" && img.magicNumber != "P6")
    {
        cout << "Not a valid netpbm image." << endl;
        filecloseinput(fin);
        exit(0);
    }

 
    while (getline(fin, temp) && temp[0] == '#')
    {
        img.comment = img.comment + temp + "\n";
    }

    pos = temp.find(" ");
    img.cols = stoi(temp.substr(0, pos));
    img.rows = stoi(temp.substr(pos + 1, string::npos ) );

    getline(fin, maxpix);

    alloc(img.redGray, img.rows, img.cols);
    alloc(img.green, img.rows, img.cols);
    alloc(img.blue, img.rows, img.cols);

    if (img.redGray == nullptr || img.green == nullptr || img.blue == nullptr)
    {
        return false;
    }

    size = img.rows * img.cols * 3;

    if (img.magicNumber == "P3")
    {
        storage = new(nothrow) int[size];

        if (storage == nullptr)
        {
            cout << "Unable to allocate memory for storage." << endl;
            exit(0);
        }

        while (count < size && fin >> storage[count])
        {
            count++;
        }

        count = 0;

        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                img.redGray[i][j] = pixel(storage[count]);
                count++;
                img.green[i][j] = pixel(storage[count]);
                count++;
                img.blue[i][j] = pixel(storage[count]);
                count++;
            }
        }
        delete[] storage;
    }
    
    else if (img.magicNumber == "P6")
    {
        storageb = new(nothrow)  pixel[size];

        if (storageb == nullptr)
        {
            cout << "Unable to allocate memory for storage." << endl;
            exit(0);
        }

        fin.read((char*) storageb, sizeof(pixel) * size);

        count = 0;

        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                img.redGray[i][j] = (storageb[count]);
                count++;
                img.green[i][j] = (storageb[count]);
                count++;
                img.blue[i][j] = (storageb[count]);
                count++;
            }
        }
        delete[] storageb;
    }

   return true;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * writes output to a file using data from the structure image.
  *
  * @param[in,out]     fout - ofstream file opened for output.
  * @param[in,out]    img - structure conatining data about ppm image.
  *
  *
  * @par Example
  * @verbatim
    ofstream foutl
    Image img;
    ofstream( fout , img); // outputs data in fout file using data from img
    @endverbatim
  *****************************************************************************/


void writeImage(ofstream& fout, image& img)
{
    int i;
    int j;
   
    fout << img.magicNumber << "\n";
    fout << img.comment;

    fout << img.cols;
    fout << " ";
    fout << img.rows << "\n";

    fout << maxpix << "\n";

    if (img.magicNumber == "P3")
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout << int(img.redGray[i][j]);
                fout << " ";
                fout << int(img.green[i][j]);
                fout << " ";
                fout << int(img.blue[i][j]);
                fout << "\n";
            }
        }
    }

    else if (img.magicNumber == "P6")
    {
        for (i = 0; i < img.rows; i++)
        {
            for (j = 0; j < img.cols; j++)
            {
                fout.write((char*) &img.redGray[i][j] , sizeof(pixel));
               
                fout.write((char*) &img.green[i][j], sizeof(pixel));
                
                fout.write((char*) &img.blue[i][j], sizeof(pixel));
            }
        }
    }

    free2d(img.redGray, img.rows);
    free2d(img.green, img.rows);
    free2d(img.blue, img.rows);
}