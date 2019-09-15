#pragma once

#include "pdf_object.h"

class PdfIntegerObject : public PdfObject
{
public:
    PdfIntegerObject(int value);

private:
    int m_value;
};