#ifndef GEOTIFREADER_H
#define GEOTIFREADER_H

#include <iostream>
#include <vector>
#include<gdal.h>
#include <gdal_priv.h>

union PixelData {
    GByte *byteData;
    GUInt16 *uint16Data;
    GUInt32 *uint32Data;
    GUInt64 *uint64Data;
    GInt16 *int16Data;
    GInt32 *int32Data;
    GInt64 *int64Data;
    float *float32Data;
    double *float64Data;
};


class GeotifReader
{
    public:
        GeotifReader(const char* filename);
        ~GeotifReader();
        float GetValue(int x, int y);
        int GetWidth();
        int GetHeight();
        std::vector<double> GetScale();
        int GetBandNumber();
        float* ReturnFloatDataVector();
        GDALDataType getDataType(int band = 1) const;
        std::vector<double> getImageValues(int band);
        GDALDataType ReturnDataType() const;

    private:
        GDALDataset* dataset;
        GDALRasterBand* band;
        GDALDataType dataType;
        int width;
        int height;
        float* data;
        double geotransform[6];
        double noDataValue;
        std::vector<double> pxScale;

};

#endif // GEOTIFREADER_H
