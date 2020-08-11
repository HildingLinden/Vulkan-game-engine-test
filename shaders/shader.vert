#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(set = 0, binding = 0) uniform sceneConstants {
	mat4 projviewMatrix;
} sc;

layout(set = 2, binding = 0) uniform objectConstants {
	mat4 modelMatrix;
} oc;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 outTexCoord;

void main() {
	gl_Position = sc.projviewMatrix * oc.modelMatrix * vec4(inPosition, 0.0, 1.0);
	outColor = inColor;
	outTexCoord = inTexCoord;
}