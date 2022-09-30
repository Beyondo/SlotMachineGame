#pragma once
#include <cstdint>
namespace oct
{
	class gfx
	{
	public:
		gfx(const gfx&) = delete;
		class context;
		class shader;
		class index_buffer;
		class buffer_layout;
		class vertex_buffer;
		class vertex_array;
		class object;
		class shape;
		class rectangle;
		class texture2d;
		//
		struct buffer_element;
		struct vertex;
		//
		enum class shader_datatype
		{
			none = 0, float1, float2, float3, float4, mat3, mat4, int1, int2, int3, int4, boolean
		};
		//
	private:
		constexpr static uint32_t datatype_sizes_lookup_table[12] =
		{
			/* none    */ 0,
			/* float1  */ 4,
			/* float2  */ 4 * 2,
			/* float3  */ 4 * 3,
			/* float4  */ 4 * 4,
			/* mat3    */ 4 * 3 * 3,
			/* mat4    */ 4 * 4 * 4,
			/* int1    */ 4,
			/* int2    */ 4 * 2,
			/* int3    */ 4 * 3,
			/* int4    */ 4 * 4,
			/* boolean */ 1
		};
		constexpr static uint32_t datatype_components_lookup_table[12] =
		{
			/* none    */ 0,
			/* float1  */ 1,
			/* float2  */ 2,
			/* float3  */ 3,
			/* float4  */ 4,
			/* mat3    */ 3, // 3x float3 (3 * vec3)
			/* mat4    */ 4, // 4x float4 (4 * vec4)
			/* int1    */ 1,
			/* int2    */ 2,
			/* int3    */ 3,
			/* int4    */ 4,
			/* boolean */ 1
		};
		constexpr static uint32_t get_datatype_size(const gfx::shader_datatype type)
		{
			return gfx::datatype_sizes_lookup_table[static_cast<uint32_t>(type)];
		}
		constexpr static uint32_t get_component_count(const gfx::shader_datatype type)
		{
			return gfx::datatype_components_lookup_table[static_cast<uint32_t>(type)];
		}
	};
}