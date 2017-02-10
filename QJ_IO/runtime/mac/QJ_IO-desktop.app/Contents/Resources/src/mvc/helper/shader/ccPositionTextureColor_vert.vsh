//”√”⁄¡¡∂»
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
								
void main()	
{							
    gl_Position = CC_PMatrix * a_position;
	v_fragmentColor.r = a_color.r;
	v_fragmentColor.g = a_color.g;
	v_fragmentColor.b = a_color.b;
	v_fragmentColor.a = a_color.a;
	v_texCoord = a_texCoord;
}