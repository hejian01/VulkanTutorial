
#!/bin/bash

GLSL_FOLDER="/Users/hejian/3_MyLab/1_Vulkan/VulkanTutorial/shaders/glsl"
SPIRV_FOLDER="/Users/hejian/3_MyLab/1_Vulkan/VulkanTutorial/shaders/spv"

for glsl_file in "$GLSL_FOLDER"/*.vert; do
    glsl_filename=$(basename "$glsl_file")
    glsl_filename="${glsl_filename%.*}"
    spirv_filename="$SPIRV_FOLDER/$glsl_filename.vert.spv"
    /Users/hejian/VulkanSDK/1.3.239.0/macOS/bin/glslangValidator -V "$glsl_file" -o "$spirv_filename"
done

for glsl_file in "$GLSL_FOLDER"/*.frag; do
    glsl_filename=$(basename "$glsl_file")
    glsl_filename="${glsl_filename%.*}"
    spirv_filename="$SPIRV_FOLDER/$glsl_filename.frag.spv"
    /Users/hejian/VulkanSDK/1.3.239.0/macOS/bin/glslangValidator -V "$glsl_file" -o "$spirv_filename"
done
