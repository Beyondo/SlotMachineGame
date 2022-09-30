#pragma once
#include <engine/gfx/api/opengl.h>
#include <engine/gfx/shader.h>
//
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
namespace oct
{
    class gl::shader : public gfx::shader
    {
    public:
        virtual void bind() const override
        {
            glUseProgram(m_id);
        }
        virtual void set_bool(const std::string& name, bool value) const override
        {
            glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
        }
        virtual void set_int(const std::string& name, int value) const override
        {
            glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
        }
        virtual void set_float(const std::string& name, float value) const override
        {
            glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
        }
        virtual void set_vec2(const std::string& name, const glm::vec2& vec) const
        {
            glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec[0]);
        }
        virtual void set_vec3(const std::string& name, const glm::vec3& vec) const
        {   
            glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec[0]);
        }
        virtual void set_vec4(const std::string& name, const glm::vec4& vec) const
        {
            glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &vec[0]);
        }
        virtual void set_mat2(const std::string& name, const glm::mat2& mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        virtual void set_mat3(const std::string& name, const glm::mat3& mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        virtual void set_mat4(const std::string& name, const glm::mat4& mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
    private:
        gl::shader(unsigned id) : m_id(id) {}
        unsigned int m_id;
        friend class gl;
    };

}