#version 450
#extension GL_ARB_separate_shader_objects : enable

// Uniforms of sampler and array of textures
layout(binding = 1) uniform sampler textureSampler;
layout(binding = 2) uniform texture2D textures[2];

// Push constant of the index of the texture
layout(push_constant) uniform PER_OBJECT {
	layout(offset = 64) int imgIndex;
} pc;

// Color and texture coordinate that is interpolated from the vertex shader
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTextureCoord;

// The resulting color of the fragment
layout(location = 0) out vec4 outColor;

void main() {
	outColor = texture(sampler2D(textures[pc.imgIndex], textureSampler), fragTextureCoord);
}