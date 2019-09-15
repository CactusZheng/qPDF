#pragma once

#include <stdint.h>

#include <memory>

#include "pdf_object.h"

/*
  num gen obj
  ...
  endobj
*/
class PdfIndirectObject : public PdfObject
{
public:
    PdfIndirectObject();
    virtual ~PdfIndirectObject();

    // Positive integer, greater than 0.
    uint32_t num() const;

    // Non negative integer, including 0 and positive integer.
    uint32_t gen() const;

protected:

};