uniform sampler2D texture;
uniform sampler2D maskTexture;

void main()
{
    vec4 bitMask = texture2D(maskTexture, gl_TexCoord[0].xy);
    gl_FragColor *= bitMask.a;
}