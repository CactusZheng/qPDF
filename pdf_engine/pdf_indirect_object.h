#pragma once

#include <stdint.h>

#include <memory>

class PdfObject;

class PdfIndirectObject
{
public:

    // Positive integer, greater than 0.
    uint32_t Num();

    // Non negative integer, including 0 and positive integer.
    uint32_t Gen();

    std::shared_ptr<PdfObject> PdfObject();


};