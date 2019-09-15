#pragma once

#include "pdf_object.h"

class PdfRealObject : public PdfObject
{
public:
    PdfRealObject(float value);

    operator float() const { return m_value; }

private:

    float m_value;
};