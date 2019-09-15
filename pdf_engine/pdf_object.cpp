#include "pdf_object.h"

#include "pdf_document.h"

PdfObject::PdfObject(PdfDocument* doc, pdf_obj* mupdf_obj)
    : m_doc(doc), m_mupdf_obj(mupdf_obj)
{
    assert(m_doc);
    assert(m_mupdf_obj);
}

PdfObject::~PdfObject() {}