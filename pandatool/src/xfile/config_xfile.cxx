// Filename: config_xfile.cxx
// Created by:  drose (24Aug00)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) 2001 - 2004, Disney Enterprises, Inc.  All rights reserved
//
// All use of this software is subject to the terms of the Panda 3d
// Software license.  You should have received a copy of this license
// along with this source code; you will also find a current copy of
// the license at http://etc.cmu.edu/panda3d/docs/license/ .
//
// To contact the maintainers of this program write to
// panda3d-general@lists.sourceforge.net .
//
////////////////////////////////////////////////////////////////////

#include "config_xfile.h"

#include "dconfig.h"

Configure(config_xfile);
NotifyCategoryDef(xfile, "");

// This is set true, typically by the user's command-line options, to
// indicate that when a X file is generated it should include all
// geometry in one big mesh, instead of preserving the hierarchy
// from the source egg file.
bool xfile_one_mesh = false;

ConfigureFn(config_xfile) {
  init_libxfile();
}

////////////////////////////////////////////////////////////////////
//     Function: init_libxfile
//  Description: Initializes the library.  This must be called at
//               least once before any of the functions or classes in
//               this library can be used.  Normally it will be
//               called by the static initializers and need not be
//               called explicitly, but special cases exist.
////////////////////////////////////////////////////////////////////
void
init_libxfile() {
  static bool initialized = false;
  if (initialized) {
    return;
  }
  initialized = true;
}

