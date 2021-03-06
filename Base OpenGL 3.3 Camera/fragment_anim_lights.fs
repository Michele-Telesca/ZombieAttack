#version 330 core

out vec4 fragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 fragTexCoords;
in vec3 FragPos;  
in vec3 Normal;

uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular2;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() { 
	
	// ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.position); //direzionale
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
 
    vec3 result = ambient + diffuse + specular;
	fragColor = texture(textureDiffuse, fragTexCoords) * vec4(result, 1.0);
    //fragColor = mix(texture(textureDiffuse, fragTexCoords), texture(textureSpecular2, fragTexCoords), 0.6) * vec4(result, 1.0);
	//fragColor = mix(texture(textureDiffuse, fragTexCoords), texture(textureDiffuse, fragTexCoords), 0.6) * vec4(result, 1.0); //direizonale
}
