#version 440

// Spot light data
struct spot_light {
  vec4 light_colour;
  vec3 position;
  vec3 direction;
  float constant;
  float linear;
  float quadratic;
  float power;
};

// Material data
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Spot light being used in the scene
uniform spot_light spot;
// Material of the object being rendered
uniform material mat;
// Position of the eye (camera)
uniform vec3 eye_pos;
// Texture to sample from
uniform sampler2D tex;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {
  // *********************************
  // Calculate direction to the light
  vec3 light_dir = spot.position*normal;
  // Calculate distance to light
  float dist = distance(spot.position, position);
  // Calculate attenuation value
  float att_factor = 1/(spot.constant + spot.linear * (dist) + (spot.quadratic*(dist*dist)));
  // Calculate spot light intensity
  float light_intensity = pow(max(dot((-spot.direction),light_dir),0.0),spot.power);
  // Calculate light colour
  vec4 light_colour = light_intensity * att_factor * spot.light_colour; 
  // Calculate view direction
  //vec3 view_dir = spot.direction*normal;
  // Now use standard phong shading but using calculated light colour and direction
  // - note no ambient
   vec4 diff_comp = max(dot(normal, light_dir),0.0) * mat.diffuse_reflection * spot.light_colour;
  // Calculate view direction
  vec3 view_dir = eye_pos - normalize(position);
  // Calculate half vector
  vec3 half_vec = normalize(view_dir + light_dir);
  // Calculate specular component
  vec4 spec_comp = pow(max(dot(normal, half_vec),0.0), mat.shininess) * mat.specular_reflection * spot.light_colour;
  // Sample texture
  vec4 tex_colour = texture(tex,tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diff_comp;
  primary.a = 1.0;
  // Calculate final colour - remember alpha
  colour = primary * tex_colour + spec_comp;
  colour.a = 1.0;
  // *********************************
}