#version 440
#pragma shader_stage(vertex)

#extension GL_KHR_vulkan_glsl : enable

layout(push_constant) uniform pc {
    mat4 view;
    mat4 proj;
};

struct Instance {
	mat4 model;
	uvec2 tex_handle;
};

layout(set = 0, binding = 0) readonly buffer InstanceBuffer {
    Instance data[32768];
} u_InstanceBuffer;

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

layout(location = 0) out vec2 v_TexCoord;
layout(location = 1) out flat uvec2 v_TexHandle;

void main(void)
{
	gl_Position = 
		proj *
		view *
		u_InstanceBuffer.data[gl_InstanceIndex].model *
		vec4(a_Position, 0.0, 1.0);

	v_TexCoord = a_TexCoord;
	v_TexHandle = u_InstanceBuffer.data[gl_InstanceIndex].tex_handle;
}
