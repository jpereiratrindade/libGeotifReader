#include "GeotifReader.h"
//!Start GeotifReader Class with the image data file name read only
GeotifReader::GeotifReader(const char* filename)
{
    int hasNoData = 0;
    GDALAllRegister();

    this->dataset = (GDALDataset*)GDALOpen(filename, GA_ReadOnly);
    if (dataset == NULL)
    {
        // Error handling
        std::cerr << "\n[ERROR]\tFailed to open dataset:\t" << filename << std::endl;
        std::cerr << "[ERROR]\tError message:\t" << CPLGetLastErrorMsg() << std::endl;
    }

    this->width = this->dataset->GetRasterXSize();
    this->height = this->dataset->GetRasterYSize();

    this->band = this->dataset->GetRasterBand(1);

    this->noDataValue = this->band->GetNoDataValue(&hasNoData);
    this->dataType = band->GetRasterDataType();

    this->dataset->GetGeoTransform(this->geotransform);

    this->data = new float[this->width * this->height];
    CPLErr err = this->band->RasterIO(GF_Read, 0, 0, this->width, this->height, this->data, this->width, this->height, GDT_Float32, 0, 0);
    if (err != CE_None)
    {
        // Error handling
        std::cerr << "\t[ERROR]\tFailed to read raster data from band." << std::endl;
        std::cerr << "[ERROR]\tError message:\t" << CPLGetLastErrorMsg() << std::endl;
        delete[] data; // Free the memory allocated for the raster data
        GDALClose(dataset); // Close the dataset and release resources
    }
}
//****************************************************************************
//!Empty float* data array and close dataset
GeotifReader::~GeotifReader()
{
    delete[] this->data;
    GDALClose(this->dataset);
}
//****************************************************************************
//!Return data value into x, y position
float GeotifReader::ReturnXYValue(int x, int y)
{
    return this->data[y * this->width + x];
}
//****************************************************************************
//!Return image width (number of collumns)
int GeotifReader::ReturnWidth()
{
    return this->width;
}
//****************************************************************************
//!Return image height (number of rows)
int GeotifReader::ReturnHeight()
{
    return this->height;
}
//****************************************************************************
//!Return Image Scale into a std::vector<double> pxScale with two registers
std::vector<double> GeotifReader::ReturnScale()
{
    pxScale.push_back(this->geotransform[1]);
    pxScale.push_back(this->geotransform[5]);
    return this->pxScale;
}
//****************************************************************************
//!Return image band number
int GeotifReader::GetBandNumber()
{
    return dataset->GetRasterCount();
}
//****************************************************************************
//!Return the image data set into a float* array
float* GeotifReader::ReturnFloatDataVector()
{
    return this->data;
}
//****************************************************************************
//!Get and return all image data values for all data types
std::vector<double> GeotifReader::getImageValues(int band)
{
    std::vector<double> imageValues(this->width * this->height);
    PixelData pixelData;

    switch (this->dataType) {
        case GDT_Byte:
            pixelData.byteData = new GByte[this->width * this->height];
            break;
        case GDT_UInt16:
            pixelData.uint16Data = new GUInt16[this->width * this->height];
            break;
        case GDT_UInt32:
            pixelData.uint32Data = new GUInt32[this->width * this->height];
            break;
        case GDT_UInt64:
            pixelData.uint64Data = new GUInt64[this->width * this->height];
            break;
        case GDT_Int16:
            pixelData.int16Data = new GInt16[this->width * this->height];
            break;
        case GDT_Int32:
            pixelData.int32Data = new GInt32[this->width * this->height];
            break;
        case GDT_Int64:
            pixelData.int64Data = new GInt64[this->width * this->height];
            break;
        case GDT_Float32:
            pixelData.float32Data = new float[this->width * this->height];
            break;
        case GDT_Float64:
            pixelData.float64Data = new double[this->width * this->height];
            break;
        // Ignore the complex data types (GDT_CInt16, GDT_CInt32, GDT_CFloat32, GDT_CFloat64)
    }

    GDALRasterBand *poBand;
    poBand = dataset->GetRasterBand(band);
    CPLErr err = poBand->RasterIO(GF_Read, 0, 0, this->width, this->height, pixelData.byteData, this->width, this->height, dataType, 0, 0);
    if (err != CE_None) {
        std::cerr << "\n[ERROR]\t" << CE_None << std::endl;
        std::cerr << "\t[ERROR]\tFailed to read raster data from band." << std::endl;
        std::cerr << "[ERROR]\tError message:\t" << CPLGetLastErrorMsg() << std::endl;
        delete[] pixelData.byteData; // Free the memory allocated
        GDALClose(dataset); // Close the dataset and release resources

    }

    // Fill the imageValues vector with the pixel values from the PixelData union
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            switch (dataType) {
                case GDT_Byte:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.byteData[i * this->width + j]);
                    break;
                case GDT_UInt16:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.uint16Data[i * this->width + j]);
                    break;
                case GDT_UInt32:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.uint32Data[i * this->width + j]);
                    break;
                case GDT_UInt64:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.uint64Data[i * this->width + j]);
                    break;
                case GDT_Int16:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.int16Data[i * this->width + j]);
                    break;
                case GDT_Int32:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.int32Data[i * this->width + j]);
                    break;
                case GDT_Int64:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.int64Data[i * this->width + j]);
                    break;
                case GDT_Float32:
                    imageValues[i * this->width + j] = static_cast<double>(pixelData.float32Data[i * this->width + j]);
                    break;
                case GDT_Float64:
                    imageValues[i * this->width + j] = pixelData.float64Data[i * this->width + j];
                    break;
            }
        }
    }

    // Deallocate memory
    switch (dataType) {
        case GDT_Byte:
            delete[] pixelData.byteData;
            break;
        case GDT_UInt16:
            delete[] pixelData.uint16Data;
            break;
        case GDT_UInt32:
            delete[] pixelData.uint32Data;
            break;
        case GDT_UInt64:
            delete[] pixelData.uint64Data;
            break;
        case GDT_Int16:
            delete[] pixelData.int16Data;
            break;
        case GDT_Int32:
            delete[] pixelData.int32Data;
            break;
        case GDT_Int64:
            delete[] pixelData.int64Data;
            break;
        case GDT_Float32:
            delete[] pixelData.float32Data;
            break;
        case GDT_Float64:
            delete[] pixelData.float64Data;
            break;
    }

    return imageValues;
}
//******************************************************************************
//!Retur image data type
GDALDataType GeotifReader::ReturnDataType() const
{
    return this->dataType;
}
//******************************************************************************
//!Return band 1 no data value
double GeotifReader::ReturnNoDataValue() const
{
    return this->noDataValue;
}
//******************************************************************************
//!Return the image number of pixels without consider no data values
int GeotifReader::ReturnNumPixels()
{
    int counter = 0;
    for(size_t i=0;i<(this->width*this->height);i++){
        if(data[i]!= this->noDataValue){
            counter++;
        }
    }
    return numPxWithoutNoDataValue = (this->width * this->height) - counter;
}
