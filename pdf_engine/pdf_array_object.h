#pragma once

#include <memory>
#include <vector>

#include "pdf_object.h"

/*
 [ ... ]
*/

class PdfArrayObject : public PdfObject
{
public:
    PdfArrayObject();
    virtual ~PdfArrayObject();

private:
    std::vector<std::shared_ptr<PdfObject>> m_array;
};