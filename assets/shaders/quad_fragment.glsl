#version 440
#pragma shader_stage(fragment)

#extension GL_KHR_vulkan_glsl : enable
#extension GL_EXT_nonuniform_qualifier : enable

layout(set = 1, binding = 0) uniform sampler2DArray u_Textures[];

layout(location = 0) in vec2 v_TexCoord;
layout(location = 1) in flat uvec2 v_TexHandle;

layout(location = 0) out vec4 o_ScreenColor;

void main(void)
{
	o_ScreenColor = texture(
		u_Textures[v_TexHandle.x],
		vec3(v_TexCoord, v_TexHandle.y)
	);
}
