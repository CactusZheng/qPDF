#pragma once

#include <memory>
#include <unordered_map>

#include "pdf_object.h"
#include "pdf_name_object.h"

/*
 << ... >>
*/

class PdfDictionaryObject : public PdfObject
{
public:
    PdfDictionaryObject();
    ~PdfDictionaryObject();

    void SetKeyValue(PdfNameObject key, std::shared_ptr<PdfObject> value);
    void DeleteKey(PdfNameObject key);
    bool HasKey(PdfNameObject key);

private:
    std::unordered_map<PdfNameObject, std::shared_ptr<PdfObject>> m_dict;

};