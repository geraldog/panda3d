// Filename: camera.cxx
// Created by:  drose (26Feb02)
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

#include "pandabase.h"
#include "camera.h"
#include "lens.h"
#include "throw_event.h"

TypeHandle Camera::_type_handle;

////////////////////////////////////////////////////////////////////
//     Function: Camera::Constructor
//       Access: Published
//  Description:
////////////////////////////////////////////////////////////////////
Camera::
Camera(const string &name) :
  LensNode(name),
  _active(true),
  _camera_mask(DrawMask::all_on())
{
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::Copy Constructor
//       Access: Protected
//  Description:
////////////////////////////////////////////////////////////////////
Camera::
Camera(const Camera &copy) :
  LensNode(copy),
  _active(copy._active),
  _scene(copy._scene),
  _camera_mask(copy._camera_mask)
{
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::Destructor
//       Access: Public, Virtual
//  Description:
////////////////////////////////////////////////////////////////////
Camera::
~Camera() {
  // We don't have to destroy the display region(s) associated with
  // the camera; they're responsible for themselves.  However, they
  // should have removed themselves before we destruct, or something
  // went wrong.
  nassertv(_display_regions.empty());
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::make_copy
//       Access: Public, Virtual
//  Description: Returns a newly-allocated Node that is a shallow copy
//               of this one.  It will be a different Node pointer,
//               but its internal data may or may not be shared with
//               that of the original Node.
////////////////////////////////////////////////////////////////////
PandaNode *Camera::
make_copy() const {
  return new Camera(*this);
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::safe_to_flatten
//       Access: Public, Virtual
//  Description: Returns true if it is generally safe to flatten out
//               this particular kind of Node by duplicating
//               instances, false otherwise (for instance, a Camera
//               cannot be safely flattened, because the Camera
//               pointer itself is meaningful).
////////////////////////////////////////////////////////////////////
bool Camera::
safe_to_flatten() const {
  return false;
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::safe_to_transform
//       Access: Public, Virtual
//  Description: Returns true if it is generally safe to transform
//               this particular kind of Node by calling the xform()
//               method, false otherwise.  For instance, it's usually
//               a bad idea to attempt to xform a Character.
////////////////////////////////////////////////////////////////////
bool Camera::
safe_to_transform() const {
  return false;
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::add_display_region
//       Access: Private
//  Description: Adds the indicated DisplayRegion to the set of
//               DisplayRegions shared by the camera.  This is only
//               intended to be called from the DisplayRegion.
////////////////////////////////////////////////////////////////////
void Camera::
add_display_region(DisplayRegion *display_region) {
  _display_regions.push_back(display_region);
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::remove_display_region
//       Access: Private
//  Description: Removes the indicated DisplayRegion from the set of
//               DisplayRegions shared by the camera.  This is only
//               intended to be called from the DisplayRegion.
////////////////////////////////////////////////////////////////////
void Camera::
remove_display_region(DisplayRegion *display_region) {
  DisplayRegions::iterator dri =
    find(_display_regions.begin(), _display_regions.end(), display_region);
  if (dri != _display_regions.end()) {
    _display_regions.erase(dri);
  }
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::register_with_read_factory
//       Access: Public, Static
//  Description: Tells the BamReader how to create objects of type
//               Camera.
////////////////////////////////////////////////////////////////////
void Camera::
register_with_read_factory() {
  BamReader::get_factory()->register_factory(get_class_type(), make_from_bam);
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::write_datagram
//       Access: Public, Virtual
//  Description: Writes the contents of this object to the datagram
//               for shipping out to a Bam file.
////////////////////////////////////////////////////////////////////
void Camera::
write_datagram(BamWriter *manager, Datagram &dg) {
  LensNode::write_datagram(manager, dg);

  dg.add_bool(_active);
  dg.add_uint32(_camera_mask.get_word());
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::make_from_bam
//       Access: Protected, Static
//  Description: This function is called by the BamReader's factory
//               when a new object of type Camera is encountered
//               in the Bam file.  It should create the Camera
//               and extract its information from the file.
////////////////////////////////////////////////////////////////////
TypedWritable *Camera::
make_from_bam(const FactoryParams &params) {
  Camera *node = new Camera("");
  DatagramIterator scan;
  BamReader *manager;

  parse_params(params, scan, manager);
  node->fillin(scan, manager);

  return node;
}

////////////////////////////////////////////////////////////////////
//     Function: Camera::fillin
//       Access: Protected
//  Description: This internal function is called by make_from_bam to
//               read in all of the relevant data from the BamFile for
//               the new Camera.
////////////////////////////////////////////////////////////////////
void Camera::
fillin(DatagramIterator &scan, BamReader *manager) {
  LensNode::fillin(scan, manager);

  _active = scan.get_bool();
  _camera_mask.set_word(scan.get_uint32());
}
