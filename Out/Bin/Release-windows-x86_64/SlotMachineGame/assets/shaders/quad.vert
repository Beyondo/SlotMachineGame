#version 460 core
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
uniform vec4 u_color;
uniform mat4 u_transform;
struct vertex
{
	vec4 color;
	vec2 texCoord;
};
layout (location = 0) out vertex vert;
void main()
{
	gl_Position = u_transform * vec4(a_Position, 1.0);
    vert.color = vec4(a_Color, 1.0f) * u_color;
    vert.texCoord = a_TexCoord;
}  