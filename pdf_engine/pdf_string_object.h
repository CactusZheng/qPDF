#pragma once

#include <stdint.h>

#include "pdf_object.h"

/*
 * As a sequence of literal characters enclosed in parentheses ( ).
 * As hexadecimal data enclosed in angle brackets < >.
*/
class PdfStringObject : public PdfObject
{
public:


private:
    uint8_t* m_bytes;
};