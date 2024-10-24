/*******************************************************************************
 * EasyCppOGL:   Copyright (C) 2019,                                            *
 * Sylvain Thery, IGG Group, ICube, University of Strasbourg, France            *
 *                                                                              *
 * This library is free software; you can redistribute it and/or modify it      *
 * under the terms of the GNU Lesser General Public License as published by the *
 * Free Software Foundation; either version 2.1 of the License, or (at your     *
 * option) any later version.                                                   *
 *                                                                              *
 * This library is distributed in the hope that it will be useful, but WITHOUT  *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
 * for more details.                                                            *
 *                                                                              *
 * You should have received a copy of the GNU Lesser General Public License     *
 * along with this library; if not, write to the Free Software Foundation,      *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
 *                                                                              *
 * Contact information: thery@unistra.fr                                        *
 *******************************************************************************/

#include <iostream>
#include "shader_program.h"
#include "gl_viewer.h"
#include "fbo.h"
#include "mesh.h"

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define DATA_PATH std::string(macro_xstr(DEF_DATA_PATH))
#define SHADERS_PATH std::string(macro_xstr(DEF_SHADERS_PATH))

// using namespace EZCOGL;

float getRandomMinMax(float min, float max);
EZCOGL::VBO::SP update_cubesPos(uint nbCubesPerLine);

class Viewer : public EZCOGL::GLViewer
{
	// Shader programs
	EZCOGL::ShaderProgram::UP shaderProgram;
	EZCOGL::ShaderProgram::UP shaderProgram2;

	// FBO
	EZCOGL::FBO_Depth::SP fbo;

	// Renderers
	EZCOGL::InstancedMeshRenderer::UP cube_rend;

	// Paramters
	std::vector<EZCOGL::GLVec3> lightsPos;
	std::vector<EZCOGL::GLVec3> lightsColor;
	int nbLights;
	uint nbLightsMax;
	int nbCubesPerLine;
	float lightsIntensity;

public:
	Viewer();
	void init_ogl() override;
	void draw_ogl() override;
	void interface_ogl() override;
	void resize_ogl(int32_t w, int32_t h) override;
};

int main(int, char **)
{
	Viewer v;
	return v.launch3d();
}

Viewer::Viewer() : nbLights(10),
				   nbLightsMax(100),
				   nbCubesPerLine(10),
				   lightsIntensity(1.f)

{
}

void Viewer::init_ogl()
{
	srand(static_cast<unsigned>(time(NULL)));

	// Init Shader Program
	shaderProgram = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP6_forwardShading.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP6_1.fs")}}, "shader");
	shaderProgram2 = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP5Full.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP6_forwardShading.fs")}}, "shader");

	// Create geometry : mesh cube
	auto meshCube = EZCOGL::Mesh::Cube();
	// Get a VBO containing the centers of all the cubes to draw
	EZCOGL::VBO::SP vbo_p = update_cubesPos(nbCubesPerLine);
	// get the associated instanced renderer with positions(1) and normals(2) VBO + the vbo containing the centers of the cubes(3)
	cube_rend = meshCube->instanced_renderer({{3, vbo_p, 1}}, 1, 2, -1, -1, -1);

	// Set the view frustrum
	set_scene_center(meshCube->BB()->center());
	set_scene_radius(meshCube->BB()->radius() + 1);

	auto tex_positions = EZCOGL::Texture2D::create({GL_NEAREST, GL_REPEAT});
	tex_positions->init(GL_RGB16F);
	auto tex_normals = EZCOGL::Texture2D::create({GL_NEAREST, GL_REPEAT});
	tex_normals->init(GL_RGB16F);
	auto tex_albedo = EZCOGL::Texture2D::create({GL_NEAREST, GL_REPEAT});
	tex_albedo->init(GL_RGB16F);
	auto tex_ks = EZCOGL::Texture2D::create({GL_NEAREST, GL_REPEAT});
	tex_ks->init(GL_RGB16F);

	fbo = EZCOGL::FBO_Depth::create({tex_positions, tex_normals, tex_albedo, tex_ks});

	// Set the lights positions and colors
	lightsPos.reserve(nbLightsMax);
	lightsColor.reserve(nbLightsMax);
	for (uint i = 0; i < nbLightsMax; ++i)
	{
		lightsPos.emplace_back(EZCOGL::GLVec3(getRandomMinMax(-10.f, 10.f), getRandomMinMax(-10.f, 10.f), getRandomMinMax(-10.f, 10.f)));
		lightsColor.emplace_back(EZCOGL::GLVec3(getRandomMinMax(0.f, 1.f), getRandomMinMax(0.f, 1.f), getRandomMinMax(0.f, 1.f)));
	}

	// Define the color to use when refreshing screen
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

EZCOGL::VBO::SP update_cubesPos(uint nbCubesPerLine)
{
	// Compute a VBO to send the center of cubes (one position vec3 for each cube)

	uint nbCubes = nbCubesPerLine * nbCubesPerLine * nbCubesPerLine; // total cubes
	std::vector<EZCOGL::GLVec3> cubes_centers;
	cubes_centers.reserve(nbCubes);
	// Determine the position of all cubes with their center point
	for (uint i = 0; i < nbCubesPerLine; ++i)
	{
		for (uint j = 0; j < nbCubesPerLine; ++j)
		{
			for (uint k = 0; k < nbCubesPerLine; ++k)
			{
				float x = (static_cast<float>(k)) / static_cast<float>(nbCubesPerLine - 1);
				float y = (static_cast<float>(j)) / static_cast<float>(nbCubesPerLine - 1);
				float z = (static_cast<float>(i)) / static_cast<float>(nbCubesPerLine - 1);
				cubes_centers.emplace_back(EZCOGL::GLVec3(x * 2.f - 1.f, y * 2.f - 1.f, z * 2.f - 1.f));
			}
		}
	}
	// Create a VBO containing the 3D postions of the centers of the cubes
	auto vbo_p = EZCOGL::VBO::create(cubes_centers);

	return vbo_p;
}

float getRandomMinMax(float min, float max)
{
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void update_lights_pos(uint nbLights, std::vector<EZCOGL::GLVec3> &lightsPos)
{
	for (uint i = 0; i < nbLights; ++i)
		lightsPos[i] = EZCOGL::GLVec3(getRandomMinMax(-10.f, 10.f), getRandomMinMax(-10.f, 10.f), getRandomMinMax(-10.f, 10.f));
}

void update_lights_color(uint nbLights, std::vector<EZCOGL::GLVec3> &lightsColor)
{
	for (uint i = 0; i < nbLights; ++i)
		lightsColor[i] = EZCOGL::GLVec3(getRandomMinMax(0.f, 1.f), getRandomMinMax(0.f, 1.f), getRandomMinMax(0.f, 1.f));
}

void Viewer::draw_ogl()
{
	// Clear the GL "color" and "depth" framebuffers
	EZCOGL::FBO::push();
	fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// Set "current" shader program
	shaderProgram->bind();

	// Get the view and projection matrix
	const EZCOGL::GLMat4 &view = this->get_view_matrix();
	const EZCOGL::GLMat4 &proj = this->get_projection_matrix();

	// Set uniforms
	// Matrices
	EZCOGL::set_uniform_value(1, view);
	EZCOGL::set_uniform_value(2, proj);
	EZCOGL::set_uniform_value(3, EZCOGL::Transfo::inverse_transpose(view));
	// Material color (albedo) : white - same for all cubes send by uniform
	EZCOGL::set_uniform_value(4, EZCOGL::GLVec3(1.f, 1.f, 1.f));
	// LIGHTS

	// render cubes
	int nbCubes = nbCubesPerLine * nbCubesPerLine * nbCubesPerLine;
	cube_rend->draw(GL_TRIANGLES, nbCubes);

	EZCOGL::FBO::pop();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	shaderProgram2->bind();
	EZCOGL::set_uniform_value(5, lightsIntensity);
	EZCOGL::set_uniform_value(6, nbLights);
	for (uint i = 0; i < nbLights; ++i)
		EZCOGL::Transfo::apply(view, lightsPos[i]); // Get the positions in the view space
	EZCOGL::set_uniform_value("pos_lum", lightsPos);
	EZCOGL::set_uniform_value("col_lum", lightsColor);

	for (int i = 0; i < 3; i++)
		fbo->texture(i)->bind(i);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 1.5f;
	ImGui::Begin("Params", nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0, 0});

	ImGui::Text("FPS :(%2.2lf)", fps_);

	if (ImGui::SliderInt("# Cubes", &nbCubesPerLine, 1, 30))
	{
		auto meshCube = EZCOGL::Mesh::Cube();
		EZCOGL::VBO::SP vbo_p = update_cubesPos(nbCubesPerLine);
		cube_rend = meshCube->instanced_renderer({{3, vbo_p, 1}}, 1, 2, -1, -1, -1);
	}
	ImGui::SliderInt("# Lights", &nbLights, 1, nbLightsMax);
	ImGui::SliderFloat("Light intensity", &lightsIntensity, 0.1f, 10.f);
	if (ImGui::Button("Change lights colors"))
		update_lights_color(nbLights, lightsColor);
	if (ImGui::Button("Change lights positions"))
		update_lights_pos(nbLights, lightsPos);
	if (ImGui::CollapsingHeader("Texture content"))
		ImGui::Image(reinterpret_cast<ImTextureID>(fbo->texture(0)->id()), ImVec2(400, 400), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::SameLine();
		ImGui::Image(reinterpret_cast<ImTextureID>(fbo->texture(1)->id()), ImVec2(400, 400), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::SameLine();
		ImGui::Image(reinterpret_cast<ImTextureID>(fbo->texture(2)->id()), ImVec2(400, 400), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::SameLine();
		ImGui::Image(reinterpret_cast<ImTextureID>(fbo->texture(3)->id()), ImVec2(400, 400), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void Viewer::resize_ogl(int32_t w, int32_t h)
{
	fbo->resize(w, h);
}
