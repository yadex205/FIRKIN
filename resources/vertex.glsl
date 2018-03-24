#version 410 core

in  vec2 position;
in  vec2 texCoord;
out vec2 vTexCoord;

void main() {
  vTexCoord = texCoord;
  gl_Position = vec4(position, 0.0, 1.0);
}
