#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
texture tex;
target_camera cam;
directional_light light;
vector<point_light> points(4);
vector<spot_light> spots(5);
map<string, material> materials;

bool load_content() {
	// Create plane mesh
	meshes["plane"] = mesh(geometry_builder::create_plane());

	// Create scene
	meshes["box"] = mesh(geometry_builder::create_box());
	meshes["tetra"] = mesh(geometry_builder::create_tetrahedron());
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["disk"] = mesh(geometry_builder::create_disk(20));
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder(20, 20));
	meshes["sphere"] = mesh(geometry_builder::create_sphere(20, 20));
	meshes["torus"] = mesh(geometry_builder::create_torus(20, 20, 1.0f, 5.0f));

	// Transform objects
	meshes["box"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["box"].get_transform().translate(vec3(-10.0f, 2.5f, -30.0f));
	meshes["tetra"].get_transform().scale = vec3(4.0f, 4.0f, 4.0f);
	meshes["tetra"].get_transform().translate(vec3(-30.0f, 10.0f, -10.0f));
	meshes["pyramid"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["pyramid"].get_transform().translate(vec3(-10.0f, 7.5f, -30.0f));
	meshes["disk"].get_transform().scale = vec3(3.0f, 1.0f, 3.0f);
	meshes["disk"].get_transform().translate(vec3(-10.0f, 11.5f, -30.0f));
	meshes["disk"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f));
	meshes["cylinder"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["cylinder"].get_transform().translate(vec3(-25.0f, 2.5f, -25.0f));
	meshes["sphere"].get_transform().scale = vec3(2.5f, 2.5f, 2.5f);
	meshes["sphere"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f));

	// *********************************
	// Set materials
	// - all emissive is black
	// - all specular is white
	// - all shininess is 25
	// Red box
	materials["box"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["box"].set_diffuse(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	materials["box"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["box"].set_shininess(25.0f);

	// Green tetra

	materials["tetra"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["tetra"].set_diffuse(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	materials["tetra"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["tetra"].set_shininess(25.0f);


	// Blue pyramid

	materials["pyramid"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["pyramid"].set_diffuse(vec4(0.0f, 0.0f, 1.0f, 1.0f));
	materials["pyramid"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["pyramid"].set_shininess(25.0f);


	// Yellow disk

	materials["disk"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["disk"].set_diffuse(vec4(0.0f, 1.0f, 1.0f, 1.0f));
	materials["disk"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["disk"].set_shininess(25.0f);


	// Magenta cylinder

	materials["cylinder"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["cylinder"].set_diffuse(vec4(1.0f, 0.0f, 1.0f, 1.0f));
	materials["cylinder"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["cylinder"].set_shininess(25.0f);


	// Cyan sphere

	materials["sphere"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["sphere"].set_diffuse(vec4(0.75f, 1.0f, 1.0f, 1.0f));
	materials["sphere"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["sphere"].set_shininess(25.0f);


	// White torus

	materials["torus"].set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	materials["torus"].set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["torus"].set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	materials["torus"].set_shininess(25.0f);


	// *********************************

	// Load texture
	tex = texture("textures/checker2.png");

	// Set lighting values
	// *********************************
	// Point 0, Position (-25, 5, -15)
	// Red, 20 range
	points[0].set_position(vec3(-25, 5, -15));
	points[0].set_light_colour(vec4(1, 0, 0, 1));
	points[0].set_range(20);

	// Point 1, Position (-25, 5, -35)
	// Red,20 range

	points[1].set_position(vec3(-25, 5, -35));
	points[1].set_light_colour(vec4(1, 0, 0, 1));
	points[1].set_range(20);

	// Point 2,Position (-10, 5, -15)
	// Red,20 range

	points[2].set_position(vec3(-10, 5, -15));
	points[2].set_light_colour(vec4(1, 0, 0, 1));
	points[2].set_range(20);

	// Point 3,Position (-10, 5, -35)
	// Red,20 range

	points[3].set_position(vec3(-10, 5, -35));
	points[3].set_light_colour(vec4(1, 0, 0, 1));
	points[3].set_range(20);

	// Spot 0, Position (-25, 10, -15)
	// Green, Direction (1, -1, -1) normalized
	// 20 range,0.5 power

	spots[0].set_position(vec3(-25, 10, -15));
	spots[0].set_light_colour(vec4(0, 1, 0, 1));
	spots[0].set_range(20);
	spots[0].set_power(0.5f);
	spots[0].set_direction(normalize(vec3(1, -1, -1)));

	// Spot 1,Position (-25, 10, -35)
	// Green,Direction (1, -1, 1) normalized
	// 20 range,0.5 power

	spots[1].set_position(vec3(-25, 10, -15));
	spots[1].set_light_colour(vec4(0, 1, 0, 1));
	spots[1].set_range(20);
	spots[1].set_power(0.5f);
	spots[1].set_direction(normalize(vec3(1, -1, 1)));

	// Spot 2,Position (-10, 10, -15)
	// Green,Direction (-1, -1, -1) normalized
	// 20 range,0.5 power

	spots[2].set_position(vec3(-25, 10, -15));
	spots[2].set_light_colour(vec4(0, 1, 0, 1));
	spots[2].set_range(20);
	spots[2].set_power(0.5f);
	spots[2].set_direction(normalize(vec3(-1, -1, -1)));

	// Spot 3,Position (-10, 10, -35)
	// Green,Direction (-1, -1, 1) normalized
	// 20 range,0.5 power

	spots[3].set_position(vec3(-25, 10, -15));
	spots[3].set_light_colour(vec4(0, 1, 0, 1));
	spots[3].set_range(20);
	spots[3].set_power(0.5f);
	spots[3].set_direction(normalize(vec3(-1, -1, -1)));

	// Spot 4,Position (-17.5, 15, -25)
	// Blue,Direction (0, -1, 0)
	// 30 range,1.0 power

	spots[4].set_position(vec3(-25, 10, -15));
	spots[4].set_light_colour(vec4(0, 0, 1, 1));
	spots[4].set_range(20);
	spots[4].set_power(1.0f);
	spots[4].set_direction(normalize(vec3(0, -1, 0)));

	// Set lighting values
	light.set_ambient_intensity(vec4(0.3f, 0.3f, 0.3f, 1.0f));
	light.set_direction(vec3(1.0f, 1.0f, -1.0f));
	light.set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));


	// Load in shaders
	eff.add_shader("52_Multifile_Shaders/shader.vert", GL_VERTEX_SHADER);
	// Name of fragment shaders required
	vector<string> frag_shaders{ "52_Multifile_Shaders/shader.frag", "shaders/part_direction.frag",
		"shaders/part_point.frag", "shaders/part_spot.frag" };
	eff.add_shader(frag_shaders, GL_FRAGMENT_SHADER);
	// Build effect
	eff.build();

	// Set camera properties
	cam.set_position(vec3(50.0f, 10.0f, 50.0f));
	cam.set_target(vec3(0.0f, 0.0f, 0.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
	return true;
}

bool update(float delta_time) {
	if (glfwGetKey(renderer::get_window(), '1')) {
		cam.set_position(vec3(50, 10, 50));
	}
	if (glfwGetKey(renderer::get_window(), '2')) {
		cam.set_position(vec3(-50, 10, 50));
	}
	if (glfwGetKey(renderer::get_window(), '3')) {
		cam.set_position(vec3(-50, 10, -50));
	}
	if (glfwGetKey(renderer::get_window(), '4')) {
		cam.set_position(vec3(50, 10, -50));
	}

	// Rotate the sphere
	meshes["sphere"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);

	cam.update(delta_time);

	return true;
}

bool render() {
	// Render meshes
	for (auto &e : meshes) {
		auto m = e.second;
		// Bind effect
		renderer::bind(eff);
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), // Location of uniform
			1,                               // Number of values - 1 mat4
			GL_FALSE,                        // Transpose the matrix?
			value_ptr(MVP));                 // Pointer to matrix data
											 // *********************************
											 // Set M matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));

		// Set N matrix uniform - remember - 3x3 matrix
		auto normal = m.get_transform().get_normal_matrix();
		glUniformMatrix3fv(eff.get_uniform_location("N"),
			1,
			GL_FALSE,
			value_ptr(normal));

		// Bind material
		renderer::bind(materials[e.first], "mat");

		renderer::bind(light, "light");

		// Bind point lights
		renderer::bind(spots, "spots");

		// Bind spot lights
		renderer::bind(points, "points");

		// Bind texture
		renderer::bind(tex, 0);

		// Set tex uniform
		glUniform1i(eff.get_uniform_location("tex"), 0);

		// Set eye position - Get this from active camera
		glUniform3fv(
			eff.get_uniform_location("eye_pos"),
			1,
			value_ptr(cam.get_position())
		);
		// Render mesh
		renderer::render(m);

		// *********************************

		// Render mesh
		renderer::render(m);
	}

	return true;
}

void main() {
	// Create application
	app application("52_Multifile_Shaders");
	// Set load content, update and render methods
	application.set_load_content(load_content);
	application.set_update(update);
	application.set_render(render);
	// Run application
	application.run();
}