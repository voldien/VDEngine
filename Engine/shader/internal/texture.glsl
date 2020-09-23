#line 1
/**
    VDEngine common built-in shader functions.
    Copyright (C) 2015  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 *	
 */
struct Texture2D{
	sampler2D tex;
	vec2 scale;
	vec2 offset;
};

/*
 *	
 */
struct Texture3D{
	sampler3D tex;
	vec3 scale;
	vec3 offset;
};


/*
 *	
 */
vec4 getTextureSample(const in Texture2D tex, vec2 uv){
	return texture(tex.tex, uv * tex.scale).rgba;
}

/*
 *	
 */
vec4 getTextureSample(const in Texture3D tex, vec3 uv){
	return texture(tex.tex, uv * tex.scale).rgba;
}


/*
#if __VERSION__ >= 400
vec4 getTextureSampler(Texture2DSampler sampler, const in vec2 uv){
	return texture2D(sampler.texture, (uv * sampler.textureTile) + sampler.textureOffset).rgba;
}
#else
vec4 getTextureSampler(Texture2DSampler sampler, const in vec2 uv){
	return texture2D(sampler.texture, (uv * sampler.textureTile) + sampler.textureOffset).rgba;
}
#endif 

*/
