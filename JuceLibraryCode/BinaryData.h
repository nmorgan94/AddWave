/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_16525805_INCLUDED
#define BINARYDATA_H_16525805_INCLUDED

namespace BinaryData
{
    extern const char*   DancingKeys_xml;
    const int            DancingKeys_xmlSize = 4747;

    extern const char*   DelayedDuck_xml;
    const int            DelayedDuck_xmlSize = 5023;

    extern const char*   DubstepMidBass_xml;
    const int            DubstepMidBass_xmlSize = 5009;

    extern const char*   GlassKeys_xml;
    const int            GlassKeys_xmlSize = 4707;

    extern const char*   Reset_xml;
    const int            Reset_xmlSize = 4626;

    extern const char*   RollerCoaster_xml;
    const int            RollerCoaster_xmlSize = 5217;

    extern const char*   ScaryHall_xml;
    const int            ScaryHall_xmlSize = 4856;

    extern const char*   SpaceyDesert_xml;
    const int            SpaceyDesert_xmlSize = 4952;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 8;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
