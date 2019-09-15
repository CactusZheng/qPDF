#pragma once

#include <memory>

#include "pdf_indirect_object.h"

/*
  num gen R
*/
class PdfIndirectRef : public PdfObject
{
public:
    PdfIndirectRef(std::shared_ptr<PdfIndirectObject> object);

};