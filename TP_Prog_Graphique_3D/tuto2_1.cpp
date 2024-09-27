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
#include "ebo.h"

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
	shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO2_1.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO2_1.fs")}}, "VBOs");

	// CREATE A TORUS :

	// ***********************************
	// Geometry
	// ***********************************
    int na = 32;		// #part on the large radius
    int nb = 16;		// #part on the small radius
    float lr = 1.5f;	// large radius
    float sr = 0.5f;    // samll radius

    std::vector<EZCOGL::GLVec3> positions;
	std::vector<EZCOGL::GLVec3> colors;
    positions.reserve((na + 1)*(nb + 1));
    
    for (int i = 0; i <= na; ++i)
    {
        float alpha = (float)i * 2.f * M_PI / (float)na;
        
        for (int j = 0; j <= nb; ++j)
        {
            float beta = (float)j * 2.f * M_PI / (float)nb;
            
            EZCOGL::GLVec3 position((sr * cos(beta) + lr) * cos(alpha)/*x*/,
                                    (sr * cos(beta) + lr) * sin(alpha)/*y*/,
                                    sr * sin(beta)/*z*/);

			positions.emplace_back(position);
			colors.emplace_back(EZCOGL::GLVec3(position[0] * 1.f + 0.2f/*R*/,
											   position[1] * 0.5f + 0.2f/*G*/,
					                           position[2] * 0.1f + 0.2f/*B*/));
        }
    }
    
    // Create and fill a VBO with positions
	EZCOGL::VBO::SP vbo_p = EZCOGL::VBO::create(positions);
	EZCOGL::VBO::SP vbo_c = EZCOGL::VBO::create(colors);

    // Create the VAO and associate the VBO to it
	vao = EZCOGL::VAO::create({{1, vbo_p},{2, vbo_c}}); // 1 is the "location index". We use this ID in the vertex shader to get this VBO with a "in" variable
    
    // ***********************************
	// Topology
	// ***********************************
    // Indices
    std::vector<GLuint> indices;
	indices.reserve(na*nb * 2 * 3);

    for (int i = 0; i < na; ++i)
    {
        for (int j = 0; j < nb; ++j)
        {
            indices.emplace_back(i*(nb + 1) + j);
            indices.emplace_back((i + 1)*(nb + 1) + j);
            indices.emplace_back(i*(nb + 1) + j + 1);

            indices.emplace_back((i + 1)*(nb + 1) + j);
            indices.emplace_back(i*(nb + 1) + j + 1);
            indices.emplace_back((i + 1)*(nb + 1) + j + 1);
        }
    }

	// Create and fill a EBO with indices
    ebo = EZCOGL::EBO::create(indices);

	// ===================================
	// INIT some OpenGL params

	// set scene center and radius for the init of matrix view/proj
	set_scene_center(EZCOGL::GLVec3(0.f, 0.f, 0.f));
	set_scene_radius(10.f);

	// Define the color to use when refreshing screen
    glClearColor(0.1, 0.1, 0.1, 1.0);
}

void Viewer::draw_ogl()
{
	// Clear the buffer before to draw the next frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get the view and projection matrix
	const EZCOGL::GLMat4& view = this->get_view_matrix();
	const EZCOGL::GLMat4& proj = this->get_projection_matrix();
    
    // Construct a model matrix
    const EZCOGL::GLMat4& modelTore = EZCOGL::Transfo::rotateX(-60.f);
    const EZCOGL::GLMat4& modelTore2 = EZCOGL::Transfo::translate(EZCOGL::GLVec3(5.f, 5.f, 0.f))*EZCOGL::Transfo::rotateX(-60.f)*EZCOGL::Transfo::rotateY(-60.f);

	// ***********************************
	// Rendering
	// ***********************************
	vao->bind();
	ebo->bind();
	shaderPrg->bind();
	// Uniforms variables send to the GPU
	EZCOGL::set_uniform_value(0, modelTore);
	EZCOGL::set_uniform_value(1, view);
	EZCOGL::set_uniform_value(2, proj);

    // Activate Z-buffer
	glEnable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, ebo->length(), GL_UNSIGNED_INT, nullptr);
	EZCOGL::set_uniform_value(0, modelTore2);
	glDrawElements(GL_TRIANGLES, ebo->length(), GL_UNSIGNED_INT, nullptr);

}

void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 3.0f;
	ImGui::Begin("Tuto 2", nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0,0});

	ImGui::Text("FPS :(%2.2lf)", fps_);
	if (ImGui::Button("Reload shaders"))
		shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO2_1.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO2_1.fs")}}, "VBOs");

	ImGui::End();
}
