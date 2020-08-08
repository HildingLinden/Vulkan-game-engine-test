#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) readonly buffer StorageBufferObject {
	mat4 modelMatrix;
} sbo;

layout(push_constant) uniform PushConstant {
	mat4 projview;
} pushConstant;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 outTexCoord;

void main() {
	gl_Position = pushConstant.projview * sbo.modelMatrix * vec4(inPosition, 0.0, 1.0);
	outColor = inColor;
	outTexCoord = inTexCoord;
}