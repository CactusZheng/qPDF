#pragma once

#include <stdint.h>

/*
 Key concepts:
 The tokens that delimit objects and that describe the structure of a PDF file 
 are all written in the ASCII character set, as are all the reserved words and 
 the names used as keys in standard dictionaries
*/
class PdfFile
{
public:

    bool LoadFileUtf8(const char* file_name);

    bool ReadData(uint64_t offset, uint8_t* buffer, uint32_t buffer_length);

    uint8_t* ReadAllData(uint64_t* length);

private:
    uint8_t* m_all_data;
};