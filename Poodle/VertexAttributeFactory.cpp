#include "VertexAttributeFactory.h"
#include "VertexAttributeDataStructureFactory.h"
#include <exception>

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	VertexAttribute VertexAttributeFactory::get(const VertexAttributeFlag flag)
	{
		/*
			vbo의 attribute가 하나만 쓰일 경우 암묵적으로 stride가 계산된다.
		*/
		static const unordered_map<VertexAttributeFlag, VertexAttribute> flag2attribMap
		{
			{ 
				VertexAttributeFlag::POSITION, 
				{ 
					Constant::AttribLocation::position,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3),
					0, 0
				} 
			}, 
			{
				VertexAttributeFlag::NORMAL,
				{
					Constant::AttribLocation::normal,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3),
					0, 0
				}
			},
			{
				VertexAttributeFlag::TANGENT,
				{
					Constant::AttribLocation::tangent,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4),
					0, 0
				}
			},
			{
				VertexAttributeFlag::TEXCOORD,
				{
					Constant::AttribLocation::texcoord,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC2),
					0, 0
				}
			},
			{
				VertexAttributeFlag::COLOR,
				{
					Constant::AttribLocation::color,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4),
					0, 0
				}
			},
			{
				VertexAttributeFlag::JOINTS,
				{
					Constant::AttribLocation::joints,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4),
					0, 0
				}
			},
			{
				VertexAttributeFlag::WEIGHTS,
				{
					Constant::AttribLocation::weights,
					VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4),
					0, 0
				}
			}
		}; 

		if (flag & VertexAttributeFlag::POSITION)
			return flag2attribMap.at(VertexAttributeFlag::POSITION); 

		if (flag & VertexAttributeFlag::NORMAL)
			return flag2attribMap.at(VertexAttributeFlag::NORMAL);

		if (flag & VertexAttributeFlag::TANGENT)
			return flag2attribMap.at(VertexAttributeFlag::TANGENT);

		if (flag & VertexAttributeFlag::TEXCOORD)
			return flag2attribMap.at(VertexAttributeFlag::TEXCOORD);

		if (flag & VertexAttributeFlag::COLOR)
			return flag2attribMap.at(VertexAttributeFlag::COLOR);

		if (flag & VertexAttributeFlag::JOINTS)
			return flag2attribMap.at(VertexAttributeFlag::JOINTS);

		if (flag & VertexAttributeFlag::WEIGHTS)
			return flag2attribMap.at(VertexAttributeFlag::WEIGHTS);

		throw std::exception{ "invalid attribute flag." };
	}
}