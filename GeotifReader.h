/************************************************************************
 * Copyright (c) 2023 José Pedro Trindade
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ************************************************************************
 *
 * This file includes software from the GDAL library. GDAL is licensed under
 * the X/MIT license, which can be found at https://gdal.org/license.html
 ************************************************************************/

#ifndef GEOTIFREADER_H
#define GEOTIFREADER_H

#include <iostream>
#include <vector>
#include<gdal.h>
#include <gdal_priv.h>

//!Union of all data types into PixelData
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

//!Process geotiff image to access pixel data and all data row using GDAL library
class GeotifReader
{
    public:
        GeotifReader(const char* filename);

        ~GeotifReader();

        float ReturnXYValue(int x, int y);
        int ReturnWidth();
        int ReturnHeight();
        std::vector<double> ReturnScale();
        int GetBandNumber();
        float* ReturnFloatDataVector();
        GDALDataType getDataType(int band = 1) const;
        std::vector<double> getImageValues(int band);
        GDALDataType ReturnDataType() const;
        double ReturnNoDataValue() const;
        int ReturnNumPixels();

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
        int numPxWithoutNoDataValue;

};

#endif // GEOTIFREADER_H
