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
#include "mesh.h"
#include <iostream>

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define DATA_PATH std::string(macro_xstr(DEF_DATA_PATH))
#define SHADERS_PATH std::string(macro_xstr(DEF_SHADERS_PATH))

// using namespace EZCOGL;

class Viewer: public EZCOGL::GLViewer
{
	EZCOGL::ShaderProgram::UP shaderPrg;
	EZCOGL::VAO::UP vao;
	EZCOGL::EBO::SP ebo;
	int resolution;
	int scale;
	float terrainElevation;
	EZCOGL::GLVec2 noise;
	EZCOGL::GLVec2 noiseScale;
	float startHeight;
	float weight;
	float mult;
	float noisePower;
	int frequency;
	EZCOGL::GLVec3 lightPos;
	float intensity;

public:
	Viewer();
	void init_ogl() override;
	void draw_ogl() override;
	void interface_ogl() override;
};
 
Viewer::Viewer() : resolution(50), 
	scale(5), 
	terrainElevation(25.f),
	noise(6.f,3.f),
	noiseScale(1.1f,1.1f),
	startHeight(0.f),
	weight(6.f),
	mult(4.7f),
	noisePower(9.8f),
	frequency(5),
	lightPos(-10.f,-15.f,-10.f),
	intensity(7.f)
  {};

int main(int, char**)
{
	Viewer v;
	return v.launch3d();
}

void Viewer::init_ogl()
{
	shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO.fs")}}, "Lighting");
	

	// ***********************************
	// Geometry
	// ***********************************
	int resScale = resolution * scale;
	std::vector<EZCOGL::GLVec3> positions;
	positions.reserve(resScale * resScale);
	for (uint j = 0; j < resScale; ++j)
	{
		for (uint i = 0; i < resScale; ++i)
		{
			// vertex between [-0.5;0.5] * scale
			EZCOGL::GLVec3 position(/*x*/ ((float)i / (float)(resScale - 1) - 0.5f) * scale,
			/*y*/ 0.f,
			/*z*/ ((float)j / (float)(resScale - 1) - 0.5f) * scale);
			positions.emplace_back(position);
		}
	}
	EZCOGL::VBO::SP vbo_p = EZCOGL::VBO::create(positions);
	vao = EZCOGL::VAO::create({{1,vbo_p}});

	std::vector<GLuint> indices;
	indices.reserve((resScale - 1) * (resScale - 1) * 2 * 3);
	for (uint j = 0; j < resScale - 1; ++j)
	{
		for (uint i = 0; i < resScale - 1; ++i)
		{	
			//triangle 1
			indices.emplace_back(i + j * resScale);
			indices.emplace_back((i + 1) + j * resScale);
			indices.emplace_back(i + (j + 1) * resScale);
			// triangle 2
			indices.emplace_back(i + (j + 1) * resScale);
			indices.emplace_back((i + 1) + j * resScale);
			indices.emplace_back((i + 1) + (j + 1) * resScale);
		}
	}
	ebo = EZCOGL::EBO::create(indices);


	// set scene center and radius for the init of matrix view/proj
	set_scene_center(EZCOGL::GLVec3(0.f, 0.f, 0.f));
	set_scene_radius(80.f);

	// Define the color to use when refreshing screen
    glClearColor(0.64, 0.85, 1.f, 1.0);

}

void Viewer::draw_ogl()
{
	// Clear the buffer before to draw the next frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // Enable Depth test
	glEnable(GL_DEPTH_TEST);

    // Get the view and projection matrix
	const EZCOGL::GLMat4& view = this->get_view_matrix();
	const EZCOGL::GLMat4& proj = this->get_projection_matrix();
    // Construct a model matrix
    const EZCOGL::GLMat4& model = EZCOGL::GLMat4::Identity();

	// ***********************************
	// Rendering
	// ***********************************
	shaderPrg->bind();
	vao->bind();
	ebo->bind();
	// Uniforms variables send to the GPU
	EZCOGL::set_uniform_value(2, model);
	EZCOGL::set_uniform_value(3, view);
	EZCOGL::set_uniform_value(4, proj);
	EZCOGL::set_uniform_value(5, terrainElevation);
	EZCOGL::set_uniform_value(6, noise);
	EZCOGL::set_uniform_value(7, noiseScale);
	EZCOGL::set_uniform_value(8, startHeight);
	EZCOGL::set_uniform_value(9, weight);
	EZCOGL::set_uniform_value(10, mult);
	EZCOGL::set_uniform_value(11, noisePower);
	EZCOGL::set_uniform_value(12, frequency);
	EZCOGL::set_uniform_value(13, resolution);
	EZCOGL::set_uniform_value(14, EZCOGL::Transfo::inverse_transpose(view * model));
	EZCOGL::set_uniform_value(15, lightPos);
	EZCOGL::set_uniform_value(16, intensity);
	glDrawElements(GL_TRIANGLES,ebo->length(), GL_UNSIGNED_INT,nullptr);
}



void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 1.0f;
	ImGui::Begin("Tuto 4", nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0,0});

	ImGui::Text("FPS :(%2.2lf)", fps_);
	if (ImGui::Button("Reload shaders"))
		shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO.fs")}}, "Lighting");
	ImGui::Text("Generation");
	ImGui::SliderFloat("Elevation", &terrainElevation, 0.f, 140.f); // terrainElevation : float
	ImGui::SliderFloat2("Noise X - Y", noise.data(), -10.f, 10.f); // noise : EZCOGL::GLVec2
	ImGui::SliderFloat2("Noise scale X - Y", noiseScale.data(), 0.5f, 2.f); // noiseScale : EZCOGL::GLVec2
	ImGui::SliderFloat("StartHeight", &startHeight, 0.01f, 10.f); // startHeight : float
	ImGui::SliderFloat("Weight", &weight, 0.01f, 10.f); // weight : float
	ImGui::SliderFloat("Mult", &mult, 0.01f, 10.f); // mult : float
	ImGui::SliderFloat("Noise power", &noisePower, 1.f, 20.f); // noisePower : float
	ImGui::SliderInt("Frequency", &frequency, 1, 10); 
	ImGui::SliderFloat("Intensity",&intensity,0.f,20.f);
	ImGui::SliderFloat3("LightPos",&lightPos[0],-50.f, 50.f);
	if(ImGui::Button("Reset Light Coord")) {
		lightPos = EZCOGL::GLVec3(0.f,0.f,0.f);
	}

	ImGui::End();
}
