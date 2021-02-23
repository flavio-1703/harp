#version 400

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseTex;
    sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in v3c3 vs_normal;

out vec4 fs_color;

uniform Material material;

uniform vec3 lightPos;
uniform vec3 cameraPos;

//
vec3 calcAmbient(Material material)
{
    return material.ambient;
}

vec3 calcDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos)
{
    vec3 posToLightVec = normalize(lightPos - vs_position);
    float diffuse = clamp(dot(posToLightVec, vs_normal), 0, 1);
    vec3 diffuseFinal = material.diffuse * diffuse;

    return diffuseFinal;
}

vec3 calcSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos, vec3 cameraPos)
{
    vec3 lightToPosDirVec = normalize(vs_position - lightPos);
    vec3 reflectDirectVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
    vec3 posToViewDirVec = normalize(cameraPos - vs_position);
    float specularConstant = pow(max(dot(posToViewDirVec, reflectDirectVec), 0), 35);
    vec3 specularFinal = material.specular * specularConstant;

    return specularFinal;
}

void main()
{
    fs_color = vec4(vs_color, 1.f);
    
    //ambient light
    vec3 ambientFinal = calcAmbient(material.ambient);

    //diffuse light
    vec3 diffuseFinal = calcDiffuse(material, vs_position, vs_normal, lightPos);

    //specular light
    vec3 specularFinal = calcSpecular(material, vs_position, vs_normal, lightPos, cameraPos);

    //final ight
    fs_color = texture(material.diffuseTex, vs_texcoord) * vec4(vs_color, 1.f) * (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

}