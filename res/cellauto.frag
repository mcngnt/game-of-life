uniform sampler2D texture;
uniform float time;
uniform vec2 unitVec;
uniform bool isPaused;
uniform vec4 emptyCellColor;

/// CONSTS ///

#define PI 3.14
#define POS_INF 1.0/0.0

void main()
{
	vec2 uvPos = gl_TexCoord[0].xy;
    vec4 pixel = texture2D(texture, uvPos);
    float unitX = unitVec.x;
    float unitY = unitVec.y;

    vec2 neighboursUVPos[8] = vec2[8](uvPos - vec2(unitX, 0), uvPos - unitVec, uvPos - vec2(0, unitY), uvPos + vec2(unitX, -unitY), uvPos + vec2(unitX, 0), uvPos + unitVec, uvPos + vec2(0, unitY), uvPos + vec2(-unitX, unitY));
    int neighboursAliveNB = 0;
    if (!isPaused)
    {
    	for (int i = 0; i < 8; ++i)
    	{
    		vec4 neighbourPix = texture2D(texture, neighboursUVPos[i]);
    		if (neighbourPix == vec4(1.0))
    		{
    			neighboursAliveNB++;
    		}
    	}
    	
    	if (neighboursAliveNB == 3)
    	{
    		pixel = vec4(1.0);
    	}
    	if (neighboursAliveNB < 2)
    	{
    		pixel = emptyCellColor;
    	}
    	if (neighboursAliveNB > 3)
    	{
    		pixel = emptyCellColor;
    	}
    }
    

    gl_FragColor = gl_Color * pixel;
}