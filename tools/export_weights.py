# Copyright (c) Miika Pelkonen. All rights reserved.
# Licensed under the MIT License.

# This Blender add-on exports model weights for Mipe3D rendering engine
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
# In object mode, select an object, whose weights you want to export.
# Then go to Object/Extract weights and select filename for your 
# weights file (e.g. "my_model.weights") and finally press Export weights.

bl_info = {
    "name": "Export weights",
    "category": "Object",
}

import bpy
from bpy_extras.io_utils import ImportHelper
from bpy.types import Operator

class ExportWeights(Operator, ImportHelper):
    bl_idname = "object.export_weights"
    bl_label = "Export weights"
    epsilon = 0.0001

    def execute(self, context):
        file = open(self.filepath, 'w')
        obj = bpy.context.object

        weights = [0.0] * len(obj.vertex_groups);

        for v in obj.data.vertices:
            sum = 0.0
            
            for i in range(0, len(obj.vertex_groups)):
                group = next((x for x in v.groups if x.group == i), None)    
                
                weights[i] = 0.0 if group is None else group.weight
                sum += weights[i]        
                
            if sum < self.epsilon:
                sum += 1.0
                weights[0] = 1.0
                
            file.write(str(weights[0] / sum))
            for w in weights[1:]:
                file.write(' ')
                file.write(str(w / sum))
            
            file.write('\n')

        file.close()
        
        return {'FINISHED'}

def menu_func(self, context):
    self.layout.operator(ExportWeights.bl_idname)

def register():
    bpy.utils.register_class(ExportWeights)
    bpy.types.VIEW3D_MT_object.append(menu_func)

def unregister():
    bpy.utils.unregister_class(ExportWeights)
    bpy.types.VIEW3D_MT_object.remove(menu_func)