#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_Uv;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec4 Color;
out vec2 UV;
void main()
{
	Color = a_Color;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1);
	UV = a_Uv;
}		



#type fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec4 Color;
in vec2 UV;
uniform vec3 u_Color;
uniform sampler2D u_Texture;
void main()
{
	color = texture(u_Texture, UV);

	//color = vec4(UV,0,1);
	//color = vec4(u_Color, 1);
	//color = vec4(0.8,0.2,0.3,1);
}		