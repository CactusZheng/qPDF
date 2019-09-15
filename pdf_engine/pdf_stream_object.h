#pragma once

#include <stdint.h>

#include "pdf_dictionary_object.h"
#include "pdf_indirect_object.h"

/*
 << >>
 stream
 ...
 endstream
*/
class PdfStreamObject : public PdfIndirectObject
{
public:
    PdfStreamObject();

private:
    PdfDictionaryObject m_dictionary;
    uint8_t* m_data;
};