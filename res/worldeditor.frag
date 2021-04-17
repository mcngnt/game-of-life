uniform sampler2D texture;
uniform vec2 mousePos;
uniform bool mouseLPressed;
uniform bool mouseRPressed;
uniform vec2 screenSize;
uniform vec2 texPosTL;
uniform vec2 texPosBR;
uniform vec2 texSize;
uniform vec4 emptyCellColor;

/// CONSTS ///

#define PI 3.14
#define POS_INF 1.0/0.0

float dist(vec2 a, vec2 b)
{
	return sqrt(  (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)  );
}

bool is_in_box(vec2 v, vec2 tl, vec2 br)
{
	return (v.x < br.x && v.x > tl.x && v.y > br.y && v.y < tl.y);
}

void main()
{
	vec2 uvPos = gl_TexCoord[0].xy;
    vec4 pixel = texture2D(texture, uvPos);
    vec2 texPos = uvPos * texSize;
    vec2 mouseTexPos = vec2(mousePos.x - texPosTL.x, mousePos.y - texPosTL.y)/vec2(texPosBR.x - texPosTL.x, texPosBR.y - texPosTL.y) * texSize;

    if (mouseLPressed && dist(texPos, mouseTexPos) < texSize.x/100.f)
    {
    	pixel = vec4(1.0);
    }

    if (mouseRPressed && dist(texPos, mouseTexPos) < texSize.x/100.f)
    {
        pixel = emptyCellColor;
    }

    gl_FragColor = gl_Color * pixel;
}