#define AA 2  //change to 1 to increase performance

#define _Speed 3.0  //disk rotation speed

#define _Steps  12. //disk texture layers
#define _Size 0.3 //size of BH

float hash(float x){ return fract(sin(x)*152754.742);}
float hash(vec2 x){ return hash(x.x + hash(x.y));}

float value(vec2 p, float f) //value noise
{
    float bl = hash(floor(p*f + vec2(0.,0.)));
    float br = hash(floor(p*f + vec2(1.,0.)));
    float tl = hash(floor(p*f + vec2(0.,1.)));
    float tr = hash(floor(p*f + vec2(1.,1.)));
    
    vec2 fr = fract(p*f);    
    fr = (3. - 2.*fr)*fr*fr;	
    float b = mix(bl, br, fr.x);	
    float t = mix(tl, tr, fr.x);
    return  mix(b,t, fr.y);
}

vec4 background(vec3 ray)
{
    vec2 uv = ray.xy;
}

if( abs(ray.x) > 0.5)
        uv.x = ray.z;
    else if( abs(ray.y) > 0.5)
        uv.y = ray.z;
