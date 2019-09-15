#pragma once

#include <string>

#include "pdf_object.h"

/*
 /...
*/
class PdfNameObject : public PdfObject
{
public:
    PdfNameObject(const char* name);
    PdfNameObject(std::string name);

private:
    std::string m_name; // utf-8?

};