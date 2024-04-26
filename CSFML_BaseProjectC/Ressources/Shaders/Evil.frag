uniform float u_Time;


vec3 blendNormal(vec3 base, vec3 blend, float opacity) {
    return (blend * opacity + base * (1.0 - opacity));
}


void main()
{
    
    vec3 color = vec3(0.0,cos(u_Time * 2.5)*0.5+0.5,0.0);

    gl_FragColor = vec4(color,0.8);
}