#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;
uniform sampler2D maskTexture;

void main()
{
    vec4 bitMask = texture2D(maskTexture, gl_TexCoord[0].xy);
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);
    float alpha = color.a - bitMask.a;

    gl_FragColor = vec4(color.rgb, bitMask.a);
}

