#pragma once

#include <stdint.h>

#include <vector>

// first_object_num object_count
class PdfXRefSubSection
{
public:

    // nnnnnnnnnn ggggg n eol
    // nnnnnnnnnn ggggg f eol
    struct Entry
    {
        uint32_t m_offset; // n - 10-digit byte offset. 
                           // f - 10-digit object number of the next free object.
        uint32_t m_gen;    // 5-digit generation number.
        bool m_in_use;     // n - in use, f - free.
    };

    uint32_t first_object_num();
    
    uint32_t object_count();

private:

    std::vector<Entry> m_entries;

};