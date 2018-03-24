#version 410 core

in  vec2 vTexCoord;
out vec3 fragment;

uniform sampler2D texSampler;

void main() {
  fragment = texture(texSampler, vTexCoord).rgb;
}
