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

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define DATA_PATH std::string(macro_xstr(DEF_DATA_PATH))
#define SHADERS_PATH std::string(macro_xstr(DEF_SHADERS_PATH))

// using namespace EZCOGL;

class Viewer: public EZCOGL::GLViewer
{
	EZCOGL::ShaderProgram::UP shaderPrg;
	EZCOGL::VAO::UP vao;
	EZCOGL::GLVec3 color;

public:
	Viewer();
	void init_ogl() override;
	void draw_ogl() override;
	void interface_ogl() override;
};

int main(int, char**)
{
	Viewer v;
	return v.launch3d();
}

Viewer::Viewer()
{}

void Viewer::init_ogl()
{
	shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP1.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP1.fs")}}, "Square");
	
	// ***********************************
	// Geometry
	// ***********************************

	// create a VBO with the position of 4 2D vertices (for point and line loop draw)
	EZCOGL::VBO::SP vbo_p = EZCOGL::VBO::create(EZCOGL::GLVVec2{{-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, 0.5f}, {0.5f,-0.5f} , {-0.5f, -0.5f}});
	
	// create the VAO and associate the VBO to it
	vao = EZCOGL::VAO::create({{1, vbo_p}}); // 1 is the "location index". We use this ID in the vertex shader to get this VBO with a "in" variable
	color = EZCOGL::GLVec3(1.f,0.f, 1.f);

	// Define the color to use when refreshing screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
}

void Viewer::draw_ogl()
{
	// Clear the buffer before to draw the next frame
	glClear(GL_COLOR_BUFFER_BIT);
	// enable the use of gl_PointSize in the shader to define the size of a point on the screen when using GL_POINTS
	glEnable(GL_PROGRAM_POINT_SIZE);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	// ***********************************
	// Rendering
	// ***********************************
	// Bind the shader program (EZCOGL wrapper)
	shaderPrg->bind();
	// Bind the VAO (EZCOGL wrapper)
	vao->bind();
	float size = EZCOGL::current_time();
	const EZCOGL::GLMat4& model = EZCOGL::Transfo::rotateZ(45.f) * EZCOGL::Transfo::translate(0.5f, 0.2f, 0.f) * EZCOGL::Transfo::scale(0.5f);
	EZCOGL::set_uniform_value(3,model);
	EZCOGL::set_uniform_value(2, size);
	EZCOGL::set_uniform_value(1, color);

	// 1st pass : Draw Points
	glDrawArrays(GL_POINTS, 0, 6);
	// 2nd pass : Draw Lines
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 1.0f;
	ImGui::Begin("TP1 Introduction",nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0,0});

	ImGui::Text("FPS :(%2.2lf)", fps_);
	ImGui::SliderFloat("Red",&color[0], 0.f, 1.f);
	ImGui::SliderFloat("Green",&color[1], 0.f, 1.f);
	ImGui::SliderFloat("Blue",&color[2], 0.f, 1.f);
	if (ImGui::Button("Reload shaders"))
		shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP1.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP1.fs")}}, "Square");

	ImGui::End();
}
