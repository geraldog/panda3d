// Filename: test_prog.cxx
// Created by:  drose (14Feb00)
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

#include "programBase.h"

#include "notify.h"

class TestProgram : public ProgramBase {
public:
  TestProgram();

  bool _bool_a;
  int _count_b;
  int _int_c;
};

TestProgram::
TestProgram() {
  set_program_description
    ("This is a simple test program to verify the effectiveness of the "
     "ProgramBase base class as a base class for simple programs.  It "
     "includes some simple options and some description strings that are "
     "long enough to require word-wrapping.\r"
     "Don't expect anything fancy, though.");
  add_runline("[opts]");

  add_option
    ("bog", "", 90,
     "This is test option 'bog'.  It is a simple boolean toggle; if it appears "
     "at all, it sets a boolean flag to indicate that.  If it does not "
     "appear, it leaves the boolean flag alone.\r"
     "There's not a whole lot of point to this option, when you come down "
     "to it.",
     &TestProgram::dispatch_none, &_bool_a);

  add_option
    ("b", "", 90, "Test option b",
     &TestProgram::dispatch_count, NULL, &_count_b);
  _count_b = 0;

  add_option
    ("c", "integer_parameter", 90,
     "This is test option 'c'.  It takes an integer parameter.",
     &TestProgram::dispatch_int, NULL, &_int_c);
  _int_c = 0;
}


int main(int argc, char *argv[]) {
  TestProgram t;
  t.parse_command_line(argc, argv);

  nout << "Executed successfully.\n"
       << "  _bool_a = " << t._bool_a << "\n"
       << "  _count_b = " << t._count_b << "\n"
       << "  _int_c = " << t._int_c << "\n";
  return 0;
}
