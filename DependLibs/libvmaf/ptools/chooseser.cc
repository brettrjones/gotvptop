
#include "chooseser.h"

PTOOLS_BEGIN_NAMESPACE


void DumpValToArray( const Val& given, Array<char>& dump,
                            Serialization_e ser,
                            ArrayDisposition_e arrdisp,
                            bool perform_conversion_of_OTabTupBigInt_to_TabArrStr,
                            MachineRep_e endian )
{
    static int once = 0;
    if( arrdisp == AS_PYTHON_ARRAY && once == 0 ) {
        once = 1;
        std::cerr << "As of PicklingTools 1.2.0, the array disposition\n"
            << " AS_PYTHON_ARRAY is deprecated.  You will see this warning\n"
            << " only once...." << std::endl;
        std::cerr << "\n"
            "  The whole purpose of adding the ArrayDisposition AS_PYTHON_ARRAY\n"
            "  was because, in Python 2.6, it was a binary dump: dumping arrays\n"
            "  of POD (Plain Old Data, like real_4, int_8, complex_16) was blindingly\n"
            "  fast (as it was basically a memcpy): This was to help Python users who\n"
            "  did not necessarily have the Numeric module installed.  As of Python 2.7,\n"
            "  however, the Pickling of Arrays has changed: it turns each element into a\n"
            "  Python number and INDIVIDUALLY pickles each element(much like the AS_LIST\n"
            "  option).  The new Pickleloader DOES DETECT AND WORK with both 2.6\n"
            "  and 2.7 pickle streams, but we currently only dump as 2.6: this change\n"
            "  in Python 2.7 (and also Python 3.x) defeats the whole purpose of\n"
            "  supporting array .. we wanted a binary protocol for dumping large amounts\n"
            "  of binary data!  As of this release, we deprecate the AS_PYTHON_ARRAY\n"
            "  serialization, but will keep it around for a number of releases. \n"
            << std::endl;
    }
    bool conv = perform_conversion_of_OTabTupBigInt_to_TabArrStr;
    switch( ser ) {
    case SERIALIZE_P0: case SERIALIZE_P0_OLDIMPL: {
        if( arrdisp == AS_PYTHON_ARRAY ) {
            throw runtime_error( "SERIALIZE_P0 doesn't support AS_PYTHON_ARRAY" );
        }
        PythonBufferPickler<Val> pd( dump, arrdisp );
        pd.compatibility( conv );  // Makes it so we don't have to convert at top,
                                 // only as we go.
        pd.dump( given );
        break;
    }
    case SERIALIZE_P2: case SERIALIZE_P2_OLDIMPL: case SERIALIZE_P2_OLD: {
        PicklingIssues_e issues =
            ( ( ser == SERIALIZE_P2_OLD ) ? AS_PYTHON_2_2 : ABOVE_PYTHON_2_2 );
        if( conv ) {
            issues = PicklingIssues_e( int( issues ) | int( CONVERT_OTAB_TUP_ARR__TO__TAB_ARR_STR ) );
        }

        size_t bytes = P2TopLevelBytesToDumpVal( given, arrdisp, issues );
        dump.expandTo( bytes ); // overestimate
        char* mem = dump.data();
        char* rest = P2TopLevelDumpVal( given, mem, arrdisp, issues );
        size_t len = rest - mem;   // exact
        dump.expandTo( len );
        break;
    }
    case SERIALIZE_M2K: {
        // Because there are no Tup, OTab or BigInt in M2k, those
        // data structures HAVE to be converted to OpaList, OpalDict and Str
        // by default ... no extra option needed for it.

        // Unfortunately, there are about 3-4 ways to serialize data
        // in M2k: the way the OpalPythonDaemon and UDP daemon do it is by
        // forcing it to be a table 
        char *mem;
        size_t bytes = 0;
        if( given.tag == 'n' && given.subtype == 'Z' ) {
            bytes = OpalDumpArr( given, mem, endian ); // Tab and Arr closely related
        }
        else if( given.tag == 't' ) {
            bytes = OpalDumpTab( given, mem, endian );
        }
        else if( given.tag == 'o' ) {
            bytes = OpalDumpOTab( given, mem, endian );
        }
        else if( given.tag == 'u' ) {
            bytes = OpalDumpTup( given, mem, endian );
        }
        else {
            // Most sockets expect a table, and they can cause seg faults
            // if they don't get an opalTable on input, so force one
            Tab special;
            special[ "__SPECIAL__" ] = given;
            bytes = OpalDumpTab( special, mem, endian );
        }
        dump.adoptMemory( mem, bytes, 2 ); //adopt as new T[], so delete w/ delete []
        dump.expandTo( bytes );
        break;
    }
    case SERIALIZE_OC: {
        // The OC, if we request conversion, does it in place so its faster
        size_t bytes = BytesToSerialize( given, conv );
        dump.expandTo( bytes ); // overestimate
        char* mem = dump.data();
        char* rest = Serialize( given, mem, conv );
        size_t len = rest - mem;
        dump.expandTo( len );   // exact
        break;
    }
                       //case SERIALIZE_TEXT: {
    case SERIALIZE_OPALTEXT:
    case SERIALIZE_PYTHONTEXT: {
        Val* vp = const_cast< Val* >( &given );
        try {
            if( conv ) {
                vp = new Val( given );
                ConvertAllOTabTupBigIntToTabArrStr( *vp );
            }
            string s;
            if( ser == SERIALIZE_OPALTEXT ) {
                std::ostringstream os;
                prettyPrintOpal( *vp, os, 0, 0, false ); // No pretty print!
                s = os.str();
            }
            else {
                s = Stringize( *vp );
            }
            dump.expandTo( s.length() );
            char* mem = dump.data();
            memcpy( mem, s.data(), s.length() );
        }
        catch( ... ) {
            if( conv ) delete vp;
            throw;
        }
        break;
    }

                               //case SERIALIZE_PRETTY: {
    case SERIALIZE_OPALPRETTY:
    case SERIALIZE_PYTHONPRETTY: {
        Val* vp = const_cast< Val* >( &given );
        try {
            if( conv ) {
                vp = new Val( given );
                ConvertAllOTabTupBigIntToTabArrStr( *vp );
            }
            std::ostringstream os;
            if( ser == SERIALIZE_PYTHONPRETTY ) {
                vp->prettyPrint( os );
            }
            else {
                prettyPrintOpal( *vp, os );
            }
            string s = os.str();
            dump.expandTo( s.length() );
            char* mem = dump.data();
            memcpy( mem, s.data(), s.length() );
        }
        catch( ... ) {
            if( conv ) delete vp;
            throw;
        }
        break;
    }


                                 // This is *slightly* different from Stringize: on the other side,
                                 // this just becomes a string, where text and pretty do an Eval.
                                 // The convert flags has ABSOLUTELY NO EFFECT on this.
    case SERIALIZE_NONE: {
        Str s = given;
        dump.expandTo( s.length() );
        char* mem = dump.data();
        memcpy( mem, s.data(), s.length() );
        break;
    }
    default: throw runtime_error( "Unknown serialization" );
    }

}

// Load a Val from an array containing serialized data. 
void LoadValFromArray( const Array<char>& dump, Val& result,
                              Serialization_e ser,
                              ArrayDisposition_e array_disposition,
                              bool perform_conversion_of_OTabTupBigInt_to_TabArrStr,
                              MachineRep_e endian )
{
    bool conv = perform_conversion_of_OTabTupBigInt_to_TabArrStr;
    char* mem = const_cast< char* >( dump.data() );
    size_t   len = dump.length();
    switch( ser ) {
        // The new loader supports both versions: P0, P2 (and P1 to a certain ex).
    case SERIALIZE_P0: case SERIALIZE_P2: {
        PickleLoader pl( mem, len );
        pl.env()[ "supportsNumeric" ] = ( array_disposition == AS_NUMERIC );
        //cout << pl.env() << endl;
        pl.loads( result );
        if( conv ) ConvertAllOTabTupBigIntToTabArrStr( result );
        break;
    }

                       // The older P0 loader is available for backwards compat.
    case SERIALIZE_P0_OLDIMPL: {
        bool supports_numeric = ( array_disposition == AS_NUMERIC );
        Array<char> c( dump ); // This routine ACTUALLY CHANGES THE INPUT BUFFER
        PythonBufferDepickler<Val> pbd( c.length(), c.data(), supports_numeric );
        result = pbd.load();

        if( conv ) ConvertAllOTabTupBigIntToTabArrStr( result );
        break;
    }

                               // The older P2 loader is available for backwards compat.
    case SERIALIZE_P2_OLDIMPL: case SERIALIZE_P2_OLD: {
        P2TopLevelLoadVal( result, mem );
        if( conv ) ConvertAllOTabTupBigIntToTabArrStr( result );
        break;
    }

                               // There are many ways to serialize in M2k, we do what
                               // the OpalPythonDaemon does: we expect a table
    case SERIALIZE_M2K: {
        Val junk;
        OpalLoadSomeTable( junk, mem, true, endian );
        if( junk.tag == 't' ) {
            Tab& t = junk;
            if( t.entries() == 1 && t.contains( "__SPECIAL__" ) ) {
                Val& value = t( "__SPECIAL__" );
                result.swap( value );
                return;
            }
        }
        result.swap( junk );
        if( conv ) ConvertAllOTabTupBigIntToTabArrStr( result );
        break;
    }

    case SERIALIZE_OC: {
        Deserialize( result, mem, conv );
        break;
    }
                       //case SERIALIZE_TEXT: 
                       //case SERIALIZE_PRETTY: {
    case SERIALIZE_PYTHONTEXT:
    case SERIALIZE_PYTHONPRETTY: {
        result = Eval( mem, len );
        if( conv ) ConvertAllOTabTupBigIntToTabArrStr( result );
        break;
    }

    case SERIALIZE_OPALTEXT:
    case SERIALIZE_OPALPRETTY: {
        OpalReader ora( mem, len );
        ora.expectAnything( result, false );
        break;
    }

    case SERIALIZE_NONE: {
        result = Str( mem, len );
        break;
    }
    default: throw runtime_error( "Unknown serialization" );
    }
}

// A convenience function for dumping a Val to a file: if you want
// finer control over a dump, use the particular serialization by
// itself.  Dump a val to a file, using one of the serializations
// given: ArrayDisposition only matters for SERIALIZE_P0, SERIALIZE_P2
// (See top of file for full discussion).  Note that SERIALIZE_P0 and
// SERIALIZE_P2 should be readable with Python's cPickle.load(file)
void DumpValToFile( const Val& v, const string& filename,
                           Serialization_e ser,
                           ArrayDisposition_e arrdisp,
                           bool perform_conversion_of_OTabTupBigInt_to_TabArrStr,
                           MachineRep_e endian )
{
    Array<char> buff;
    DumpValToArray( v, buff, ser, arrdisp,
                    perform_conversion_of_OTabTupBigInt_to_TabArrStr, endian );
    std::ofstream ofs( filename.c_str(), std::ios::out | std::ios::binary | std::ios::trunc );
    if( ofs.good() ) {
        char* mem = buff.data();
        size_t len = buff.length();
        ofs.write( mem, len );
    }
    else {
        throw runtime_error( "Trouble writing the file:" + filename );
    }
}

// Load a Val from a file.
void LoadValFromFile( const string& filename, Val& result,
                             Serialization_e ser,
                             ArrayDisposition_e arrdisp,
                             bool perform_conversion_of_OTabTupBigInt_to_TabArrStr,
                             MachineRep_e endian )
{
    Array<char> buff;
    std::ifstream ifs( filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate );
    if( ifs.good() ) {
        std::ifstream::pos_type length_of_file = ifs.tellg();
        buff.expandTo( length_of_file );
        char* mem = buff.data();
        ifs.seekg( 0, std::ios::beg );
        ifs.read( mem, length_of_file );
        ifs.close();
    }
    else {
        throw runtime_error( "Trouble reading the file:" + filename );
    }
    LoadValFromArray( buff, result, ser, arrdisp,
                      perform_conversion_of_OTabTupBigInt_to_TabArrStr,
                      endian );
}

PTOOLS_END_NAMESPACE
