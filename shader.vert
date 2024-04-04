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

if( abs(ray.x) > 0.5)
        uv.x = ray.z;
    else if( abs(ray.y) > 0.5)
        uv.y = ray.z;

    float brightness = value( uv*3., 100.); //(poor quality) "stars" created from value noise
    float color = value( uv*2., 20.); 
    brightness = pow(brightness, 256.);

    brightness = brightness*100.;
    brightness = clamp(brightness, 0., 1.);

    vec3 stars = brightness * mix(vec3(1., .6, .2), vec3(.2, .6, 1), color);

    vec4 nebulae = texture(iChannel0, (uv*1.5 ));
    nebulae.xyz += nebulae.xxx + nebulae.yyy + nebulae.zzz; //average color
    nebulae.xyz *= 0.25;

    nebulae*= nebulae;
    nebulae*= nebulae;
    nebulae*= nebulae;
    nebulae*= nebulae;
//adding for nebulae refernce pointers.

nebulae.xyz += stars;
	return nebulae;
}
vec4 raymarchDisk(vec3 ray, vec3 zeroPos)
{
//return vec4(1.,1.,1.,0.); //no disk
vec3 position = zeroPos; // starting the position at null for future lengths of xz
float lengthPos = length(position.xz);
    float dist = min(1., lengthPos*(1./_Size) *0.5) * _Size * 0.4 *(1./_Steps) /( abs(ray.y) );

position += dist*_Steps*ray*0.5;   

vec2 deltaPos;
deltaPos.x = -zeroPos.z*0.01 + zeroPos.x;
deltaPos.y = zeroPos.x*0.01 + zeroPos.z;
deltaPos = normalize(deltaPos - zeroPos.xz);
//entire delta position is normalized. 

float parallel = dot(ray.xz, deltaPos);
parallel /= sqrt(lengthPos);
parallel *= 0.5; // reduce the value to half
float redShift = parallel +0.3; //initialize it & modify the value of parallel like before

redShift *= redShift; //yessir

vec4 o = vec4(0.); //parameter at 0.

}
