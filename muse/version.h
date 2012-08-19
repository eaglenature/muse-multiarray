/*! \file version.h
 *  \brief Compile-time macros encoding MuSE release version
 *
 *         <muse/version.h> is the only MuSE header that is guaranteed to
 *         change with every MuSE release.
 */
#pragma once


#define MUSE_VERSION           100100
#define MUSE_MAJOR_VERSION     (MUSE_VERSION / 100000)
#define MUSE_MINOR_VERSION     (MUSE_VERSION / 100 % 1000)
#define MUSE_SUBMINOR_VERSION  (MUSE_VERSION % 100)



// Declare these namespaces here for the purpose of Doxygenating them

/*! \namespace muse
 *  \brief \p muse is the top-level namespace which contains all MuSE
 *         functions and types.
 */
namespace muse
{
}
