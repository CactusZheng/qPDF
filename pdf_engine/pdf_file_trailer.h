#pragma once

#include "pdf_dictionary_object.h"
#include "pdf_document.h"

/*
 trailer
 << key1 value1
    key2 value2
    бн
    keyn valuen
 >>
 startxref
 Byte_offset_of_last_cross-reference_section
 %%EOF
*/
class PdfTrailer : public PdfDictionaryObject
{
public:

    int size();

    int prev();

    std::shared_ptr<PdfDocument> root();



    int64_t offset_of_last_x_ref_section();

    std::string eof_marker();

};