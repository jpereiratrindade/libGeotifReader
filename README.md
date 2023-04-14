# GeotifReader Class Manual

## Overview

`GeotifReader` is a C++ class designed to facilitate reading and handling GeoTIFF files using the GDAL library. The class provides methods to read and retrieve essential information about the GeoTIFF file, such as the raster data, dimensions, geotransform values, and data types.

## Class Structure

### Public Methods

- `GeotifReader(const char* filename)`: Constructor that initializes the `GeotifReader` object by reading a GeoTIFF file specified by `filename`.
- `~GeotifReader()`: Destructor that deallocates memory and closes the GDAL dataset.
- `float GetValue(int x, int y)`: Returns the value at the specified pixel location (x, y).
- `int GetWidth()`: Returns the width of the raster image in pixels.
- `int GetHeight()`: Returns the height of the raster image in pixels.
- `std::vector<double> GetScale()`: Returns the pixel scale in the x and y dimensions as a vector of two doubles.
- `int GetBandNumber()`: Returns the number of bands in the dataset.
- `float* ReturnFloatDataVector()`: Returns a pointer to the float array holding the raster data.
- `GDALDataType getDataType(int band = 1) const`: Returns the data type of the specified band. Defaults to the first band if not specified.
- `std::vector<double> getImageValues(int band)`: Returns a vector containing the image values for the specified band.
- `GDALDataType ReturnDataType() const`: Returns the data type of the currently loaded raster band.

### Private Members

- `GDALDataset* dataset`: Pointer to the GDAL dataset object.
- `GDALRasterBand* band`: Pointer to the GDAL raster band object.
- `GDALDataType dataType`: The data type of the currently loaded raster band.
- `int width`: The width of the raster image in pixels.
- `int height`: The height of the raster image in pixels.
- `float* data`: Pointer to the float array holding the raster data.
- `double geotransform[6]`: Array containing the geotransform coefficients.
- `double noDataValue`: The value indicating no data for the raster band.
- `std::vector<double> pxScale`: A vector containing the pixel scale in x and y dimensions.

## Usage

1. Include the "GeotifReader.h" header file in your code.
2. Create a `GeotifReader` object by providing the path to the GeoTIFF file as an argument.
3. Use the various public methods to retrieve information about the GeoTIFF file and its raster data.

## Dependencies
1. GDAL library (https://gdal.org/)

### Example

```cpp
#include "GeotifReader.h"

int main() {
    const char* filename = "path/to/your/geotiff/file.tif";
    GeotifReader geotif(filename);

    int width = geotif.GetWidth();
    int height = geotif.GetHeight();
    std::vector<double> scale = geotif.GetScale();
    int bandCount = geotif.GetBandNumber();
    GDALDataType dataType = geotif.ReturnDataType();

    float value = geotif.GetValue(10, 20); // Get value at pixel location (10, 20)

    return 0;
}
