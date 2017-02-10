varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;	



void main()			
{
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	float gray = dot(v_orColor.rgb, vec3(0.299, 0.587, 0.114));
	v_orColor.r=gray;
	v_orColor.g=gray;
	v_orColor.b=gray;
	gl_FragColor =  v_orColor;
}				
