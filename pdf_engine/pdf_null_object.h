#pragma once

#include "pdf_object.h"

class PdfNullObject : public PdfObject
{
public:
    static PdfNullObject* GetInstance() { return &m_null; }

private:
    PdfNullObject() = default;
    ~PdfNullObject() = default;

    static PdfNullObject m_null;
};