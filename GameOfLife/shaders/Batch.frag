#version 330 core

out vec4 colour;

in DATA
{
	vec4 color;
} vsIn;

void main()
{
	
	vec4 finalColour = vsIn.color;

	//works when forced use texture at index!!!!!
	//finalColour = vsIn.color * texture2D(textures[3], vsIn.texCoords);
	//finalColour = vec4(vsIn.texId, 0.0, 0.0, 1.0);

	colour = finalColour;
}