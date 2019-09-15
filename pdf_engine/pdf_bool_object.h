#pragma once

#include "pdf_object.h"

class PdfBoolObject : public PdfObject
{
public:
    PdfBoolObject(bool value);

    operator bool() const { return m_value; }

private:

    bool m_value;

};