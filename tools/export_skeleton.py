# Copyright (c) Miika Pelkonen. All rights reserved.
# Licensed under the MIT License.

# This Blender add-on exports skeleton for Mipe3D rendering engine
#
# Installation
# ------------
#
# - go to File/User Preferences
# - select the Add-ons section
# - press Install Add-on from file...
# - find and select this file in the file browser
# - press Install Add-on from file...
#
# Now the add-on will be listed and you can enable it by pressing the checkbox.
# If you want it to be enabled on restart, press Save User Settings.
#
# Usage
# -----
#
# In object mode, select an armature. Then go to Object/Export skeleton and
# select filename for your skeleton file (e.g. "my_model.skel") and finally
# press Export skeleton.

bl_info = {
    "name": "Export skeleton",
    "category": "Object",
}

import bpy
from bpy_extras.io_utils import ImportHelper
from bpy.types import Operator


class ExportSkeleton(Operator, ImportHelper):
    bl_idname = "object.export_skeleton"
    bl_label = "Export skeleton"
    epsilon = 0.0001

    def execute(self, context):
        file = open(self.filepath, 'w')

        bones = bpy.context.object.data.bones

        bone_to_index = {None: 0}

        for i in range(0, len(bones)):
            bone_to_index[bones[i]] = i + 1

        for b in bones:
            parent_index = bone_to_index[b.parent]

            if (b.parent is None):
                pos = b.head_local + bpy.context.object.location
            else:
                pos = b.head_local - b.parent.head_local

            file.write("%f %f %f %d %s\n" % (pos.x, pos.z, -pos.y, parent_index, b.name))

        file.close()

        return {'FINISHED'}


def menu_func(self, context):
    self.layout.operator(ExportSkeleton.bl_idname)


def register():
    bpy.utils.register_class(ExportSkeleton)
    bpy.types.VIEW3D_MT_object.append(menu_func)


def unregister():
    bpy.utils.unregister_class(ExportSkeleton)
    bpy.types.VIEW3D_MT_object.remove(menu_func)