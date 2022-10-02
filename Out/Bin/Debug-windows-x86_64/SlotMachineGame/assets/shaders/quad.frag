#version 460 core
out vec4 f;
struct vertex
{
	vec4 color;
	vec2 texCoord;
};
in vertex vert;
uniform bool u_colorMode;
uniform float u_time;
uniform float u_speed = 0.0f;
uniform sampler2D u_texID;
float map(float s, float a1, float a2, float b1, float b2)
{
	return b1 + (s - a1) * (b2 - b1) / (a2 - a1);
}
void main()
{

	vec4 texColor = texture(u_texID, vert.texCoord);
	f = u_colorMode ? vert.color : texColor;
    if (f.a == 0.0) {
        discard;
    }
	else if(f.a < 0.71 && f.r == 1.0 && f.b == 0.2)
	{
		// Our switch button
		if(u_speed == 0)
			f.a = 1.0f;
		else
			f.a =  map(sin(u_speed * u_time), -1, 1, 0.6, 1);
	}
}