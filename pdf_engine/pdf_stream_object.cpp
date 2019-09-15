#include "pdf_stream_object.h"

#include "pdf_array_object.h"
#include "pdf_integer_object.h"

PdfStreamObject::PdfStreamObject()
{
    // Required common entries to all stream dictionaries
    m_dictionary.SetKeyValue("Length", std::make_shared<PdfIntegerObject>(0));
}