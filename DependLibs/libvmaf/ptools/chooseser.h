#ifndef CHOOSESER_H_

// Convenience routines for reading/writing Vals to/from Arrays and
// files using the different serializations supported by PTOOLS.
// Their usage is very simple.  These routines are used by the
// MidasServer family to do serialization.
//
// ============For example, to write a pickled file that Python can read:
//
// // C++ side: Write a Value
//  Val v = .. something ..
//  DumpValToFile(v, "state.p0", SERIALIZE_P0);
//
// # Python side: read the same value
//  import cPickle
//  result = cPickle.load( file('state.p0') ) # load figures out the protocol
//
//
// ==========Another example: have C++ read a file that Python created
// 
// # Python side: write a file
//  v = ... something ...
//  import cPickle
//  cPickle.dump( v, file('state.p2'), 2) # Use Pickling Protocol 2
// 
// // C++ side: read the same file
//  Val result;
//  LoadValFromFile("state.p2", result, SERIALIZE_P2); 
//  /// .. and we have the same value from Python!
//
//
// ==========Another example: have C++ create an Array 
//  // C++: Creating an array of pickled data I can use
//  Val v = .. something ...
//  Array<char> buff;
//  LoadValFromArray(v, buff, SERIALIZE_OC);  // Faster of the protocols
//  cout << "serialized data:" << buff.data() << " length:" << buff.length();

#include "config_libvmaf.h"

#define MIDAS_COMPILER_TEMPLATES
#include "valpython.h"

#include "valprotocol2.h"
#include "m2ser.h"
#include "libvmaf/ptools/opencontainers_1_8_4/include/ocserialize.h"
#include "pickleloader.h"
#include "libvmaf/ptools/opencontainers_1_8_4/include/ocvalreader.h"
#include "xmltools.h"
#include "opalutils.h"
#include "serialization.h"

PTOOLS_BEGIN_NAMESPACE

////////////////////////////////// ArrayDisposition_e ////////////////
// Different kinds of POD (Plain Old Data: int_1, int_2, real_4, etc.) arrays: 
// there are essentially 3 different types of POD arrays that might be moving 
// around: 
//
// (1) a = [1,2,3]  
//     Python styles lists (which are inefficient for storing 
//     homogeneous data)
//
// (2) import array; a = array.array('i',[1,2,3])
//     the arrays from the Python module array 
//
// (3) import Numeric: a = Numeric.array([1,2,3], 'i')
//     the Numeric arrays which are built in to XMPY,
//     but most standard Pythons do not have it installed.
//
// In C++, POD arrays are handled as Array<T>, thus (2) & (3)
// are handled with the same:  (1) is handled as the C++ Arr.  
// These distinctions are more important if you are in Python, or talking 
// to a Python system, as you have to specify how a C++ Array
// converts to a Python POD array.
//
// These 4 distinctions are made because Python doesn't deal
// well with POD (plain old data) arrays well:  This option allows
// you to choose what you want when dealing with POD when you
// convert between systems.  Consider:
// (1) Python style lists work, but are horribly inefficient for
//     large arrays of just plain numbers, both from a storage
//     perspective or accessing.  Also, you "lose" the fact 
//     that this is true POD array if you go back to C++.
// (2) Numeric is old, but handles all the different types well,
//     including complex (although Numeric doesn't deal with int_8s!).
//     It is also NOT a default-installed package: you may have to find
//     the proper RPM for this to work.
// (3) Python array from the array module are default but have issues:
//     (a) can't do complex data 
//     (b) may or may not support int_8
//     (c) pickling changes at 2.3.4 and 2.6, so if you are
//         pickling with protocol 2, you may have issues.
// (4) Python array from the numpy module: major drawback is that it's
//     not built-in
//     
// None of these solutions is perfect, but going to NumPy is
// probably your best choice for the future, although Numeric
// may be your choice if you are stuck on an older Python.
/////////////////////////////////////////////////////////////////////



// This is a convenience function for dumping a Val as an of several
// serializations.  Dump the given Val to the given array of chars: it
// serializes via the given serialization: ArrayDisposition only makes
// sense for SERIALIZE_P0/P2 (see above).
//
// Expert Parameter: perform_conversion_of_OTabTupBigInt_to_TabArrStr
// Some legacy systems may not support OTab, Tup or int_un/int_n, in
// which case we have the OPTION to convert those to something the
// legacy systems can understand: Tab, Arr and Str.  
void DumpValToArray (const Val& given, Array<char>& dump,
			    Serialization_e ser=SERIALIZE_P0,
			    ArrayDisposition_e arrdisp=AS_LIST,
			    bool perform_conversion_of_OTabTupBigInt_to_TabArrStr = false,
			    MachineRep_e endian=MachineRep_EEEI);

// Load a Val from an array containing serialized data. 
void LoadValFromArray (const Array<char>& dump, Val& result,
			      Serialization_e ser=SERIALIZE_P0,
			      ArrayDisposition_e array_disposition=AS_LIST,
			      bool perform_conversion_of_OTabTupBigInt_to_TabArrStr = false,
			      MachineRep_e endian=MachineRep_EEEI);

// A convenience function for dumping a Val to a file: if you want
// finer control over a dump, use the particular serialization by
// itself.  Dump a val to a file, using one of the serializations
// given: ArrayDisposition only matters for SERIALIZE_P0, SERIALIZE_P2
// (See top of file for full discussion).  Note that SERIALIZE_P0 and
// SERIALIZE_P2 should be readable with Python's cPickle.load(file)
void DumpValToFile (const Val& v, const string& filename, 
			   Serialization_e ser=SERIALIZE_P0,
			   ArrayDisposition_e arrdisp=AS_LIST,
			   bool perform_conversion_of_OTabTupBigInt_to_TabArrStr = false,
			   MachineRep_e endian=MachineRep_EEEI);

// Load a Val from a file.
void LoadValFromFile (const string& filename, Val& result, 
			     Serialization_e ser=SERIALIZE_P0,
			     ArrayDisposition_e arrdisp=AS_LIST,
			     bool perform_conversion_of_OTabTupBigInt_to_TabArrStr = false,
			     MachineRep_e endian=MachineRep_EEEI);

PTOOLS_END_NAMESPACE

#define CHOOSESER_H_
#endif // CHOOSESER_H_
