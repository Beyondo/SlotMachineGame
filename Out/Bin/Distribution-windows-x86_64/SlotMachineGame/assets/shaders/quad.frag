#version 460 core
out vec4 fragment_color;
struct vertex
{
	vec4 color;
	vec2 texCoord;
};
in vertex vert;
uniform bool u_colorMode;
uniform sampler2D u_texID;
void main()
{

	vec4 texColor = texture(u_texID, vert.texCoord);
	fragment_color = u_colorMode ? vert.color : texColor;
    if (fragment_color.a == 0.0) {
        discard;
    }
}