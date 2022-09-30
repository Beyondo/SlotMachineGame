#pragma once
#include <engine/gfx/api/opengl.h>
#include <engine/gfx/texture.h>
#include <engine/gfx/context.h>
#include <engine/gfx/buffer.h>
#include <engine/gfx/vertex_array.h>
#include <engine/gfx/shader.h>
//
#include <engine/window.h>
#include <fstream>
#include <sstream>
#include <iostream>
namespace oct
{
	class gl::context : public gfx::context
	{
	public:
		context(const window* win) : m_window(win)
		{
            glEnable(GL_STENCIL_TEST);
            glEnable(GL_SCISSOR_TEST);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
        virtual void draw_indexed(const gfx::vertex_array* VAO, uint32_t indexCount) const override
        {
            VAO->bind();
            VAO->index_buffer().bind();
            uint32_t count = indexCount ? indexCount : VAO->index_buffer().count();
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
        virtual void set_clear_color(float r, float g, float b, float a) const override
        {
            glClearColor(r, g, b, a);
        }
        virtual void set_clear_color(const glm::vec4& color) const override
        {
            glClearColor(color.r, color.g, color.b, color.a);
        }
        virtual void clear() const override
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        }
		virtual auto create_shader_from_files(const char* vertexShaderSourceFile, const char* fragmentShaderSourceFile) const->gfx::shader* override
		{
            unsigned id = 0;
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                vShaderFile.open(vertexShaderSourceFile);
                fShaderFile.open(fragmentShaderSourceFile);
                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                vShaderFile.close();
                fShaderFile.close();
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure& e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            }
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();
            unsigned int vertex, fragment;
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            check_compile_errors(vertex, shader_compile_error::vertex);
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            check_compile_errors(fragment, shader_compile_error::fragment);
            id = glCreateProgram();
            glAttachShader(id, vertex);
            glAttachShader(id, fragment);
            glLinkProgram(id);
            check_compile_errors(id, shader_compile_error::program);
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return new gl::shader(id);
		}
        virtual auto create_vertex_array() const->gfx::vertex_array* override
        {
            return new gl::vertex_array();
        }
        virtual auto create_buffer(const void* vertices, uint32_t size) const->gfx::vertex_buffer* override
        {
            return new gl::vertex_buffer(vertices, size);
        }
        virtual auto create_index_buffer(uint32_t* indices, uint32_t size) const->gfx::index_buffer* override
        {
            return new gl::index_buffer(indices, size);
        }
        virtual auto create_texture2d(void* texture_data, uint32_t x, uint32_t y, uint32_t channels) const -> texture2d* override
        {
            return new gl::texture2d(texture_data, x, y, channels);
        }
		virtual void bind_shader(const gfx::shader* shader) const override
		{

		}
		virtual void draw_triangles(const gfx::vertex_array& VAO, std::uint32_t offset, std::uint32_t count) const override
		{
            glBindVertexArray(reinterpret_cast<const gl::vertex_array&>(VAO).m_id);
            glDrawArrays(GL_TRIANGLES, offset, count);
		}
		virtual void set_viewport(float x, float y, float width, float height) const override
		{
			glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
		}
		virtual void swap_buffers() const override
		{
			m_window->swap_buffers(); // Кажется излишним, но разные API имеют разные способы замены буферами.
		}
	private:
        enum class shader_compile_error
        {
            program, fragment, vertex
        };
        void check_compile_errors(unsigned int shader, shader_compile_error type) const
        {
            int success;
            char infoLog[1024];
            switch (type)
            {
            case shader_compile_error::program:
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ENGINE::ERROR::PROGRAM_LINKING: " << infoLog << "-----------" << std::endl;
                }
                break;
            case shader_compile_error::vertex:
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ENGINE::ERROR::VERTEX_SHADER_COMPILATION: " << infoLog << "-----------" << std::endl;
                }
                break;
            case shader_compile_error::fragment:
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ENGINE::ERROR::FRAGMENT_SHADER_COMPILATION: " << infoLog << "-----------" << std::endl;
                }
                break;
            }
        }
		const window* m_window;
	};
}