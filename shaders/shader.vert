#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
	mat4 mvpMatrix;
} ubo;

layout(binding = 1) readonly buffer StorageBufferObject {
	mat4 mvpMatrix;
} sbo;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 outColor;

void main() {
	gl_Position = sbo.mvpMatrix * vec4(inPosition, 0.0, 1.0);
	outColor = inColor;
}